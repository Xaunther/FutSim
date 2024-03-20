#include "ITest.h"

#include "football/CTeamStrategy.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTeamStrategy )

void TTeamStrategy::TestExceptions() const
{
	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeamStrategy>( R"( {
			"Team strategy": {}
		} )" ); }, "key 'Tactic' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeamStrategy>( R"( {
			"Team strategy": {
				"Tactic": "A"
			}
		} )" ); }, "key 'Lineup' not found" );
}

std::vector<std::string> TTeamStrategy::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& teamStrategy : std::initializer_list<CTeamStrategy>{
		CTeamStrategy{ "A", CLineup{ CLineupTypes::position_names{ CLineupTypes::names{ "Ter Stegen" } } } },
		futsim::ValueFromJSONKeyString<CTeamStrategy>( R"( {
			"Team strategy": {
				"Tactic": "A",
				"Lineup": {
					"GK": [ "Ter Stegen" ]
				}
			}
		} )" ) } )
	{
		result.push_back( std::string{ CTeamStrategy::JSON_TACTIC } + ": " + std::string{ teamStrategy.GetTacticID() } );
		result.push_back( std::string{ CLineup::JSON_KEY } + ": " + teamStrategy.GetLineup().GetPlayers( E_PLAYER_POSITION::GK ).front() );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, teamStrategy );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TTeamStrategy::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Tactic: A",
		"Lineup: Ter Stegen",
		"{\n"
		"	\"Team strategy\": {\n"
		"		\"Tactic\": \"A\",\n"
		"		\"Lineup\": {\n"
		"			\"GK\": [\n"
		"				\"Ter Stegen\"\n"
		"			]\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
