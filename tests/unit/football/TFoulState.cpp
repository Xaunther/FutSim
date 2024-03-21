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
	if( CFoulState{ CMatchConfiguration{}, CTeamStrategy{ "A", CLineup{ "Ter Stegen", {}, {}, {}, {}, {}, {} } }, rng }.GetCommitter() != "Ter Stegen" )
		throw std::invalid_argument{ "The foul committer must be Ter Stegen." };
}

std::vector<std::string> TFoulState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	std::mt19937 rng{ 1234 };

	for( const auto& foulState : std::initializer_list{
		CFoulState{ CMatchConfiguration{}, CTeamStrategy{ "A", CLineup{ "Ter Stegen", {}, {}, {}, {}, {}, {} } }, rng } } )
	{
		result.push_back( std::string{ CFoulState::JSON_COMMIITER } + ": " + std::string{ foulState.GetCommitter() } );
		result.push_back( std::string{ CFoulState::JSON_OUTCOME } + ": " + std::string{ ToString( foulState.GetOutcome() ) } );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, foulState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TFoulState::ExpectedResults() const noexcept
{
	return std::vector<std::string>{
		"Committer: Ter Stegen",
			"Outcome: No card",
			"{\n"
			"	\"Foul state\": {\n"
			"		\"Committer\": \"Ter Stegen\",\n"
			"		\"Outcome\": \"No card\"\n"
			"	}\n"
			"}"
	};
}
