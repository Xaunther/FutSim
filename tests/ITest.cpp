#include "ITest.h"

#include <iostream>
#include <sstream>

void ITest::Run() const
{
	this->TestExceptions();
}

void ITest::CheckException( const std::function<void()>& aFunction, const std::string_view aExpectedErrorMsg )
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
		else
			return;
	}
	std::stringstream ss;
	ss << "No exception was thrown when the following exception message was expected:\n"
		<< aExpectedErrorMsg << "\n";
	throw std::invalid_argument{ ss.str() };
}

void ITest::CheckResults( const std::vector<std::string>& aObtained, const std::vector<std::string>& aExpected )
{
	if( aObtained != aExpected )
	{
		std::stringstream ss;
		ss << "The obtained results do not match the expected results.\n"
			<< "Expected\n"
			<< "-----------------------------------------\n";
		std::ranges::for_each( aExpected, [ &ss ]( const auto& aResult ) { ss << aResult << "\n"; } );
		ss << "Obtained\n"
			<< "-----------------------------------------\n";
		std::ranges::for_each( aObtained, [ &ss ]( const auto& aResult ) { ss << aResult << "\n"; } );
		throw std::invalid_argument{ ss.str() };
	}
}