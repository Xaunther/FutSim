#include "ITest.h"

#include "football/CMatchConfiguration.h"
#include "football/CTeamStrategy.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TMatchConfiguration )

void TMatchConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []()
	{
		CMatchConfiguration{ CPlayTime{}, CLineupConfiguration{}, true, CTacticsConfiguration{}, CTieCondition{}, {}, {} };
	},
		"There cannot be a tie condition without a penalty shootout configuration" );
	CheckException( []()
	{
		CMatchConfiguration{ CPlayTime{}, CLineupConfiguration{}, true, CTacticsConfiguration{}, {}, CExtraTime{}, {} };
	},
		"There cannot be extra time without a tie condition." );
	CheckException( []()
	{
		CMatchConfiguration{ CPlayTime{}, CLineupConfiguration{}, true, CTacticsConfiguration{}, {}, {}, CPenaltyShootoutConfiguration{} };
	},
		"There cannot be a penalty shootout without a tie condition." );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Tie condition": {
					"Home team lead": 1,
					"Home team goals": 3
				}
			}
		} )" );
	}, "There cannot be a tie condition without a penalty shootout configuration" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Extra time": {}
			}
		} )" );
	}, "There cannot be extra time without a tie condition." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Penalty shootout configuration": {}
			}
		} )" );
	}, "There cannot be a penalty shootout without a tie condition." );

	// Test CheckTeamStrategy
	{
		const CMatchConfiguration matchConfiguration;
		const CLineup lineup{ "Kelleher", types::CLineup::names{ "Bradley" }, {}, {}, {}, {}, {} };
		CheckException( [ &matchConfiguration, &lineup ]()
		{
			matchConfiguration.CheckTeamStrategy( CTeamStrategy{ "FF", lineup } );
		},
			"The tactic 'FF' has not been configured." );
		CheckException( [ &matchConfiguration, &lineup ]()
		{
			matchConfiguration.CheckTeamStrategy( CTeamStrategy{ "A", lineup } );
		},
			"Error checking the lineup against the configuration." );
	}
}

std::vector<std::string> TMatchConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& matchConfiguration : {
		CMatchConfiguration{},
		CMatchConfiguration{ CPlayTime{}, CLineupConfiguration{}, false, CTacticsConfiguration{}, CTieCondition{}, CExtraTime{}, CPenaltyShootoutConfiguration{} },
		futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {}
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
		result.push_back( futsim::json_traits<std::decay_t<decltype( matchConfiguration.GetPlayTime() )>>::KEY.data() );
		result.push_back( futsim::json_traits<std::decay_t<decltype( matchConfiguration.GetLineupConfiguration() )>>::KEY.data() );
		result.push_back( std::string{ futsim::json_traits<CMatchConfiguration>::APPLY_AMBIENT_FACTOR } + ": " + std::to_string( matchConfiguration.AppliesAmbientFactor() ) );
		result.push_back( futsim::json_traits<std::decay_t<decltype( matchConfiguration.GetTacticsConfiguration() )>>::KEY.data() );
		if( matchConfiguration.GetTieCondition() )
			result.push_back( futsim::json_traits<std::decay_t<decltype( *matchConfiguration.GetTieCondition() )>>::KEY.data() );
		if( matchConfiguration.GetExtraTime() )
			result.push_back( futsim::json_traits<std::decay_t<decltype( *matchConfiguration.GetExtraTime() )>>::KEY.data() );
		if( matchConfiguration.GetPenaltyShootoutConfiguration() )
			result.push_back( futsim::json_traits<std::decay_t<decltype( *matchConfiguration.GetPenaltyShootoutConfiguration() )>>::KEY.data() );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, matchConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TMatchConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Play time",
		"Lineup configuration",
		"Apply ambient factor: 1",
		"Tactics configuration",
		"{\n"
		"	\"Match configuration\": {\n"
		"		\"Play time\": {\n"
		"			\"Period count\": 2,\n"
		"			\"Period time\": 45,\n"
		"			\"Available subs\": 5\n"
		"		},\n"
		"		\"Lineup configuration\": {\n"
		"			\"Min DFs\": 3,\n"
		"			\"Max DFs\": 6,\n"
		"			\"Min MFs\": 2,\n"
		"			\"Max MFs\": 6,\n"
		"			\"Min FWs\": 0,\n"
		"			\"Max FWs\": 4,\n"
		"			\"Min players\": 7,\n"
		"			\"Benched players\": 9\n"
		"		},\n"
		"		\"Apply ambient factor\": true,\n"
		"		\"Tactics configuration\": {\n"
		"			\"Tactic configurations\": {\n"
		"				\"A\": {\n"
		"					\"Tk bonus\": -0.5,\n"
		"					\"Ps bonus\": -0.2,\n"
		"					\"Favourable tactics\": [\n"
		"						\"D\",\n"
		"						\"E\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"C\": {\n"
		"					\"Tk bonus\": 0.5,\n"
		"					\"Ps bonus\": -0.8,\n"
		"					\"Favourable tactics\": [\n"
		"						\"A\",\n"
		"						\"P\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"D\": {\n"
		"					\"Tk bonus\": 0.7,\n"
		"					\"Ps bonus\": -0.2,\n"
		"					\"Favourable tactics\": [\n"
		"						\"L\",\n"
		"						\"P\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"E\": {\n"
		"					\"Tk bonus\": -0.3,\n"
		"					\"Ps bonus\": 0.2,\n"
		"					\"Favourable tactics\": [\n"
		"						\"C\",\n"
		"						\"D\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"L\": {\n"
		"					\"Tk bonus\": 0.3,\n"
		"					\"Ps bonus\": -0.6,\n"
		"					\"Favourable tactics\": [\n"
		"						\"C\",\n"
		"						\"N\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"N\": {\n"
		"					\"Tk bonus\": 0.0,\n"
		"					\"Ps bonus\": 0.0,\n"
		"					\"Favourable tactics\": [\n"
		"						\"A\",\n"
		"						\"E\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"P\": {\n"
		"					\"Tk bonus\": -0.2,\n"
		"					\"Ps bonus\": 0.6,\n"
		"					\"Favourable tactics\": [\n"
		"						\"L\",\n"
		"						\"N\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				}\n"
		"			},\n"
		"			\"Favourable tactic skill bonus\": 1.1\n"
		"		},\n"
		"		\"Draw configuration\": {\n"
		"			\"Possession draw configuration\": {\n"
		"				\"Keep possession probability\": 0.6420632665059802\n"
		"			},\n"
		"			\"Foul draw configuration\": {\n"
		"				\"Average fouls\": 21.56578947368421,\n"
		"				\"Average yellow cards\": 3.6184210526315788,\n"
		"				\"Average red cards\": 0.08157894736842106\n"
		"			},\n"
		"			\"Chances draw configuration\": {\n"
		"				\"Average chances\": 25.28684210526316,\n"
		"				\"Average corner kicks\": 10.078947368421053,\n"
		"				\"Average 1 on 1 vs GK chances\": 2.0,\n"
		"				\"Average 1 on 1 vs DF chances\": 2.85,\n"
		"				\"Average near shots\": 3.0,\n"
		"				\"Average set pieces\": 4.065789473684211,\n"
		"				\"Average penalties\": 0.2736842105263158,\n"
		"				\"Average direct free kicks\": 0.7921052631578948\n"
		"			},\n"
		"			\"Goal draw configuration\": {\n"
		"				\"Average goals\": 2.7342105263157896,\n"
		"				\"Average penalty goals\": 0.19473684210526315,\n"
		"				\"Average direct free kick goals\": 0.04473684210526316,\n"
		"				\"Average indirect free kick goals\": 0.1,\n"
		"				\"Average corner goals\": 0.3973684210526316,\n"
		"				\"Average far shot goals\": 0.3421052631578947,\n"
		"				\"1 on 1 vs GK chance goal probability\": 0.35,\n"
		"				\"1 on 1 vs DF chance goal probability\": 0.2,\n"
		"				\"Extra corner probability\": 0.25\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"}",
		"Play time",
		"Lineup configuration",
		"Apply ambient factor: 0",
		"Tactics configuration",
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
		"		\"Lineup configuration\": {\n"
		"			\"Min DFs\": 3,\n"
		"			\"Max DFs\": 6,\n"
		"			\"Min MFs\": 2,\n"
		"			\"Max MFs\": 6,\n"
		"			\"Min FWs\": 0,\n"
		"			\"Max FWs\": 4,\n"
		"			\"Min players\": 7,\n"
		"			\"Benched players\": 9\n"
		"		},\n"
		"		\"Apply ambient factor\": false,\n"
		"		\"Tactics configuration\": {\n"
		"			\"Tactic configurations\": {\n"
		"				\"A\": {\n"
		"					\"Tk bonus\": -0.5,\n"
		"					\"Ps bonus\": -0.2,\n"
		"					\"Favourable tactics\": [\n"
		"						\"D\",\n"
		"						\"E\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"C\": {\n"
		"					\"Tk bonus\": 0.5,\n"
		"					\"Ps bonus\": -0.8,\n"
		"					\"Favourable tactics\": [\n"
		"						\"A\",\n"
		"						\"P\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"D\": {\n"
		"					\"Tk bonus\": 0.7,\n"
		"					\"Ps bonus\": -0.2,\n"
		"					\"Favourable tactics\": [\n"
		"						\"L\",\n"
		"						\"P\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"E\": {\n"
		"					\"Tk bonus\": -0.3,\n"
		"					\"Ps bonus\": 0.2,\n"
		"					\"Favourable tactics\": [\n"
		"						\"C\",\n"
		"						\"D\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"L\": {\n"
		"					\"Tk bonus\": 0.3,\n"
		"					\"Ps bonus\": -0.6,\n"
		"					\"Favourable tactics\": [\n"
		"						\"C\",\n"
		"						\"N\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"N\": {\n"
		"					\"Tk bonus\": 0.0,\n"
		"					\"Ps bonus\": 0.0,\n"
		"					\"Favourable tactics\": [\n"
		"						\"A\",\n"
		"						\"E\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				},\n"
		"				\"P\": {\n"
		"					\"Tk bonus\": -0.2,\n"
		"					\"Ps bonus\": 0.6,\n"
		"					\"Favourable tactics\": [\n"
		"						\"L\",\n"
		"						\"N\"\n"
		"					],\n"
		"					\"Position penalties\": [\n"
		"						0.0,\n"
		"						-0.2,\n"
		"						-0.4\n"
		"					]\n"
		"				}\n"
		"			},\n"
		"			\"Favourable tactic skill bonus\": 1.1\n"
		"		},\n"
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
		"		},\n"
		"		\"Draw configuration\": {\n"
		"			\"Possession draw configuration\": {\n"
		"				\"Keep possession probability\": 0.6420632665059802\n"
		"			},\n"
		"			\"Foul draw configuration\": {\n"
		"				\"Average fouls\": 21.56578947368421,\n"
		"				\"Average yellow cards\": 3.6184210526315788,\n"
		"				\"Average red cards\": 0.08157894736842106\n"
		"			},\n"
		"			\"Chances draw configuration\": {\n"
		"				\"Average chances\": 25.28684210526316,\n"
		"				\"Average corner kicks\": 10.078947368421053,\n"
		"				\"Average 1 on 1 vs GK chances\": 2.0,\n"
		"				\"Average 1 on 1 vs DF chances\": 2.85,\n"
		"				\"Average near shots\": 3.0,\n"
		"				\"Average set pieces\": 4.065789473684211,\n"
		"				\"Average penalties\": 0.2736842105263158,\n"
		"				\"Average direct free kicks\": 0.7921052631578948\n"
		"			},\n"
		"			\"Goal draw configuration\": {\n"
		"				\"Average goals\": 2.7342105263157896,\n"
		"				\"Average penalty goals\": 0.19473684210526315,\n"
		"				\"Average direct free kick goals\": 0.04473684210526316,\n"
		"				\"Average indirect free kick goals\": 0.1,\n"
		"				\"Average corner goals\": 0.3973684210526316,\n"
		"				\"Average far shot goals\": 0.3421052631578947,\n"
		"				\"1 on 1 vs GK chance goal probability\": 0.35,\n"
		"				\"1 on 1 vs DF chance goal probability\": 0.2,\n"
		"				\"Extra corner probability\": 0.25\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
