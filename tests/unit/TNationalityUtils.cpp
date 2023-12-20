#include "ITest.h"

#include "NationalityUtils.h"

#include <iostream>

using namespace futsim;

INITIALIZE_TEST( TPlayerSkills )

void TPlayerSkills::TestExceptions() const
{
	//! Test ToNationality exception
	CheckException( []() { ToNationality( "AAA" ); }, "No nationality matching the code 'AAA'." );
}

std::vector<std::string> TPlayerSkills::ObtainedResults() const noexcept
{
	std::vector<std::string> result{
		ToString( E_NATIONALITY::AGO ),
		ToString( E_NATIONALITY::CAF ),
		ToString( E_NATIONALITY::ESP ),
		ToString( ToNationality( "AGO" ) ),
		ToString( ToNationality( "CAF" ) ),
		ToString( ToNationality( "ESP" ) ),
	};
	return result;
}

std::vector<std::string> TPlayerSkills::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"AGO",
		"CAF",
		"ESP"
	};
	result.reserve( result.size() * 2 );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
