#include "ITest.h"

#include "football/CFoulState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TFoulState )

void TFoulState::TestExceptions() const
{
	std::mt19937 rng{ 1234 };
	// Test constructor
	if( CFoulState{ CMatchConfiguration{}, CTeamStrategy{ "A", CLineup{ CLineupTypes::position_names{ CLineupTypes::names{ "Ter Stegen" } } } }, rng }.GetCommitter() != "Ter Stegen" )
		throw std::invalid_argument{ "The foul committer must be Ter Stegen." };
}

std::vector<std::string> TFoulState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TFoulState::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
