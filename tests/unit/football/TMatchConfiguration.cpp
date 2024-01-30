#include "ITest.h"

#include "football/CMatchConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TMatchConfiguration )

void TMatchConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CMatchConfiguration{ CPlayTime{}, {}, true, CTieCondition{}, {}, {} }; },
		"There cannot be a tie condition without a penalty shootout configuration" );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Play time": {
					"Period count": 2,
					"Period time": 45,
					"Available subs": 5
				}
			}
		} )" ); }, "key 'Apply ambient factor' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Play time": {
					"Period count": 2,
					"Period time": 45,
					"Available subs": 5
				},
				"Apply ambient factor": true,
				"Tie condition": {
					"Home team lead": 1,
					"Home team goals": 3
				}
			}
		} )" ); }, "There cannot be a tie condition without a penalty shootout configuration" );
}

std::vector<std::string> TMatchConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& matchConfiguration : {
		CMatchConfiguration{},
		CMatchConfiguration{ CPlayTime{}, {}, false, CTieCondition{}, CExtraTime{}, CPenaltyShootoutConfiguration{} },
		futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Play time": {
					"Period count": 2,
					"Period time": 45,
					"Available subs": 5
				},
				"Benched players": 9,
				"Apply ambient factor": true
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Play time": {
					"Period count": 2,
					"Period time": 45,
					"Available subs": 5
				},
				"Apply ambient factor": false,
				"Tie condition": {
					"Home team lead": 0
				},
				"Extra time": {
					"Period count": 2,
					"Period time": 15,
					"Available subs": 1
				},
				"Penalty shootout configuration": {
					"Sequence": "AB",
					"Min penalty count": 5
				}
			}
		} )" ) } )
	{
		result.push_back( matchConfiguration.GetPlayTime().JSON_KEY.data() );
		if( matchConfiguration.GetBenchedPlayersCount() )
			result.push_back( std::string{ CMatchConfiguration::JSON_BENCHED_PLAYERS } + ": " + std::to_string( *matchConfiguration.GetBenchedPlayersCount() ) );
		result.push_back( std::string{ CMatchConfiguration::JSON_APPLY_AMBIENT_FACTOR } + ": " + std::to_string( matchConfiguration.AppliesAmbientFactor() ) );
		if( matchConfiguration.GetTieCondition() )
			result.push_back( ( *matchConfiguration.GetTieCondition() ).JSON_KEY.data() );
		if( matchConfiguration.GetExtraTime() )
			result.push_back( ( *matchConfiguration.GetExtraTime() ).JSON_KEY.data() );
		if( matchConfiguration.GetPenaltyShootoutConfiguration() )
			result.push_back( ( *matchConfiguration.GetPenaltyShootoutConfiguration() ).JSON_KEY.data() );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, matchConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TMatchConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Play time",
		"Benched players: 9",
		"Apply ambient factor: 1",
		"{\n"
		"	\"Match configuration\": {\n"
		"		\"Play time\": {\n"
		"			\"Period count\": 2,\n"
		"			\"Period time\": 45,\n"
		"			\"Available subs\": 5\n"
		"		},\n"
		"		\"Benched players\": 9,\n"
		"		\"Apply ambient factor\": true\n"
		"	}\n"
		"}",
		"Play time",
		"Apply ambient factor: 0",
		"Tie condition",
		"Extra time",
		"Penalty shootout configuration",
		"{\n"
		"	\"Match configuration\": {\n"
		"		\"Play time\": {\n"
		"			\"Period count\": 2,\n"
		"			\"Period time\": 45,\n"
		"			\"Available subs\": 5\n"
		"		},\n"
		"		\"Apply ambient factor\": false,\n"
		"		\"Tie condition\": {\n"
		"			\"Home team lead\": 0\n"
		"		},\n"
		"		\"Extra time\": {\n"
		"			\"Period count\": 2,\n"
		"			\"Period time\": 15,\n"
		"			\"Available subs\": 1\n"
		"		},\n"
		"		\"Penalty shootout configuration\": {\n"
		"			\"Sequence\": \"AB\",\n"
		"			\"Min penalty count\": 5\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}