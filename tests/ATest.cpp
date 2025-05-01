#include "ATest.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace
{

constexpr std::string_view EXPECTED_FILENAME = "expected.txt";
constexpr std::string_view OBTAINED_FILENAME = "obtained.txt";
constexpr std::string_view REL_PATH = "../Testing/Temporary";

} // anonymous namespace

ATest::ATest( const std::string_view aName ) :
	mName( aName )
{
	mExpectedStream.open( std::filesystem::current_path() / REL_PATH / EXPECTED_FILENAME, std::ios_base::app );
	mObtainedStream.open( std::filesystem::current_path() / REL_PATH / OBTAINED_FILENAME, std::ios_base::app );
}

ATest::~ATest()
{
	mExpectedStream.close();
	mObtainedStream.close();
}

void ATest::Run()
{
	TestExceptions();

	CheckResults( ObtainedResults(), ExpectedResults() );
}

void ATest::CheckException( const std::function<void()>& aFunction, const std::string_view aExpectedErrorMsg )
{
	try
	{
		aFunction();
	}
	catch( const std::exception& e )
	{
		if( std::string_view{ e.what() }.find( aExpectedErrorMsg ) == std::string::npos )
		{
			std::stringstream ss;
			ss << "Expected error string did not match obtained error string:\n"
				<< "Expected\n"
				<< "-----------------------------------------\n"
				<< aExpectedErrorMsg << "\n"
				<< "Obtained\n"
				<< "-----------------------------------------\n"
				<< e.what() << "\n";
			throw std::invalid_argument{ ss.str() };
		}
		return;
	}
	std::stringstream ss;
	ss << "No exception was thrown when the following exception message was expected:\n"
		<< aExpectedErrorMsg << "\n";
	throw std::invalid_argument{ ss.str() };
}

void ATest::CheckResults( const std::vector<std::string>& aObtained, const std::vector<std::string>& aExpected )
{
	if( aObtained != aExpected )
	{
		std::stringstream ss;
		ss << "The obtained results do not match the expected results.\n"
			<< "Expected\n"
			<< "-----------------------------------------\n";
		mExpectedStream << "In test " << mName << ":\n";
		std::ranges::for_each( aExpected, [ &ss, this ]( const auto& aResult )
		{
			ss << aResult << "\n";
			mExpectedStream << aResult << "\n";
		} );
		ss << "Obtained\n"
			<< "-----------------------------------------\n";
		mObtainedStream << "In test " << mName << ":\n";
		std::ranges::for_each( aObtained, [ &ss, this ]( const auto& aResult )
		{
			ss << aResult << "\n";
			mObtainedStream << aResult << "\n";
		} );
		throw std::invalid_argument{ ss.str() };
	}
}
