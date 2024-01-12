#include "ITest.h"

#include "football/PenaltySequenceUtils.h"

#include <iostream>

using namespace futsim::football;

INITIALIZE_TEST( TPenaltySequenceUtils )

void TPenaltySequenceUtils::TestExceptions() const
{
	//! Test ToPenaltySequence exception.
	CheckException( []() { ToPenaltySequence( "AAA" ); }, "No penalty sequence matching the string 'AAA'." );
}

std::vector<std::string> TPenaltySequenceUtils::ObtainedResults() const noexcept
{
	std::vector<std::string> result{
		ToString( E_PENALTY_SEQUENCE::AB ),
		ToString( E_PENALTY_SEQUENCE::ABBA ),
		ToString( ToPenaltySequence( "AB" ) ),
		ToString( ToPenaltySequence( "ABBA" ) ),
	};
	return result;
}

std::vector<std::string> TPenaltySequenceUtils::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"AB",
		"ABBA",
	};
	result.reserve( result.size() * 2 );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
