#include "ITest.h"

#include "football/CMatchStrategy.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TMatchStrategy )

void TMatchStrategy::TestExceptions() const
{
	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatchStrategy>( R"( {
			"Match strategy": {}
		} )" ); }, "key 'Tactic' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatchStrategy>( R"( {
			"Match strategy": {
				"Tactic": "A"
			}
		} )" ); }, "key 'Lineup' not found" );
}

std::vector<std::string> TMatchStrategy::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& matchStrategy : std::initializer_list<CMatchStrategy>{
		CMatchStrategy{ "A", CLineup{ CLineupTypes::position_names{ CLineupTypes::names{ "Ter Stegen" } } } },
		futsim::ValueFromJSONKeyString<CMatchStrategy>( R"( {
			"Match strategy": {
				"Tactic": "A",
				"Lineup": {
					"GK": [ "Ter Stegen" ]
				}
			}
		} )" ) } )
	{
		result.push_back( std::string{ CMatchStrategy::JSON_TACTIC } + ": " + matchStrategy.GetTacticID() );
		result.push_back( std::string{ CLineup::JSON_KEY } + ": " + matchStrategy.GetLineup().GetPlayers( E_PLAYER_POSITION::GK ).front() );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, matchStrategy );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TMatchStrategy::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Tactic: A",
		"Lineup: Ter Stegen",
		"{\n"
		"	\"Match strategy\": {\n"
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
