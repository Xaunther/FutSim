#include "ITest.h"

#include "football/CDrawConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TDrawConfiguration )

void TDrawConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{ 10 }, CChancesDrawConfiguration{ 30, 1, 1, 1, 2, 20 } }; },
		"The probability to get a set piece chance given a foul cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 100 } }; },
		"The probability to get a chance after keeping possession or launching a counter attack cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 15 } }; },
		"The corner probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 4, 11 } }; },
		"The 1 on 1 vs GK probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 4, 2, 11 } }; },
		"The 1 on 1 vs DF probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 4, 2, 1, 11 } }; },
		"The near shot probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 4, 2, 1, 3 } }; },
		"The far shot probability cannot be negative." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 20, 10, 1, 1, 1, 5, 0.01 }, CGoalDrawConfiguration{ 4, 0.5 } }; },
		"The penalty goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 20, 10, 1, 1, 1, 5, 1, 0.01 }, CGoalDrawConfiguration{ 4, 0.05, 0.5 } }; },
		"The direct free kick goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 20, 10, 1, 1, 1, 0.1, 0.01, 0.01 }, CGoalDrawConfiguration{ 4, 0, 0, 2 } }; },
		"The indirect free kick goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{}, CGoalDrawConfiguration{ 50, 0, 0, 0, 25 } }; },
		"The corner goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{}, CGoalDrawConfiguration{ 50, 0, 0, 0, 0, 30 } }; },
		"The far shot goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 20, 10, 1, 1, 1, 5, 1, 1 }, CGoalDrawConfiguration{ 4, 0.05, 0.05, 1 } }; },
		"The near shot goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{ 0.9 }, CFoulDrawConfiguration{ 10 } }; },
		"The joint probability of keeping possession or receiving a foul cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{}, CGoalDrawConfiguration{ 2.73, 0.25 } }; },
		"The joint probability of scoring or getting an extra corner from a penalty cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{}, CGoalDrawConfiguration{ 2.73, 0, 0.6 } }; },
		"The joint probability of scoring or getting an extra corner from a direct free kick cannot be greater than 1." );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Foul draw configuration": {
					"Average fouls": 10
				},
				"Chances draw configuration": {
					"Average chances": 30,
					"Average corner kicks": 1,
					"Average 1 on 1 vs GK chances": 1,
					"Average 1 on 1 vs DF chances": 1,
					"Average near shots": 2,
					"Average set pieces": 20
				}
			}
		} )" ); }, "The probability to get a set piece chance given a foul cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 100
					
				}
			}
		} )" ); }, "The probability to get a chance after keeping possession or launching a counter attack cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 10,
					"Average corner kicks": 15
				}
			}
		} )" ); }, "The corner probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 10,
					"Average corner kicks": 4,
					"Average 1 on 1 vs GK chances": 11
				}
			}
		} )" ); }, "The 1 on 1 vs GK probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 10,
					"Average corner kicks": 4,
					"Average 1 on 1 vs GK chances": 2,
					"Average 1 on 1 vs DF chances": 11
				}
			}
		} )" ); }, "The 1 on 1 vs DF probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 10,
					"Average corner kicks": 4,
					"Average 1 on 1 vs GK chances": 2,
					"Average 1 on 1 vs DF chances": 1,
					"Average near shots": 11
				}
			}
		} )" ); }, "The near shot probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 10,
					"Average corner kicks": 4,
					"Average 1 on 1 vs GK chances": 2,
					"Average 1 on 1 vs DF chances": 1,
					"Average near shots": 3
				}
			}
		} )" ); }, "The far shot probability cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 20,
					"Average corner kicks": 10,
					"Average 1 on 1 vs GK chances": 1,
					"Average 1 on 1 vs DF chances": 1,
					"Average near shots": 1,
					"Average set pieces": 5,
					"Average penalties": 0.01
				},
				"Goal draw configuration": {
					"Average goals": 4,
					"Average penalty goals": 0.5
				}
			}
		} )" ); }, "The penalty goal probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 20,
					"Average corner kicks": 10,
					"Average 1 on 1 vs GK chances": 1,
					"Average 1 on 1 vs DF chances": 1,
					"Average near shots": 1,
					"Average set pieces": 5,
					"Average penalties": 1,
					"Average direct free kicks": 0.01
				},
				"Goal draw configuration": {
					"Average goals": 4,
					"Average penalty goals": 0.05,
					"Average direct free kick goals": 0.5
				}
			}
		} )" ); }, "The direct free kick goal probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 20,
					"Average corner kicks": 10,
					"Average 1 on 1 vs GK chances": 1,
					"Average 1 on 1 vs DF chances": 1,
					"Average near shots": 1,
					"Average set pieces": 0.1,
					"Average penalties": 0.01,
					"Average direct free kicks": 0.01
				},
				"Goal draw configuration": {
					"Average goals": 4,
					"Average penalty goals": 0,
					"Average direct free kick goals": 0,
					"Average indirect free kick goals": 2
				}
			}
		} )" ); }, "The indirect free kick goal probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Goal draw configuration": {
					"Average goals": 50,
					"Average penalty goals": 0,
					"Average direct free kick goals": 0,
					"Average indirect free kick goals": 0,
					"Average corner goals": 25
				}
			}
		} )" ); }, "The corner goal probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Goal draw configuration": {
					"Average goals": 50,
					"Average penalty goals": 0,
					"Average direct free kick goals": 0,
					"Average indirect free kick goals": 0,
					"Average corner goals": 0,
					"Average far shot goals": 30
				}
			}
		} )" ); }, "The far shot goal probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Chances draw configuration": {
					"Average chances": 20,
					"Average corner kicks": 10,
					"Average 1 on 1 vs GK chances": 1,
					"Average 1 on 1 vs DF chances": 1,
					"Average near shots": 1,
					"Average set pieces": 5,
					"Average penalties": 1,
					"Average direct free kicks": 1
				},
				"Goal draw configuration": {
					"Average goals": 4,
					"Average penalty goals": 0.05,
					"Average direct free kick goals": 0.05,
					"Average indirect free kick goals": 1
				}
			}
		} )" ); }, "The near shot goal probability cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Possession draw configuration": {
					"Keep possession probability": 0.9
				},
				"Foul draw configuration": {
					"Average fouls": 10
				}
			}
		} )" ); }, "The joint probability of keeping possession or receiving a foul cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Goal draw configuration": {
					"Average goals": 2.73,
					"Average penalty goals": 0.25
				}
			}
		} )" ); }, "The joint probability of scoring or getting an extra corner from a penalty cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {
				"Goal draw configuration": {
					"Average goals": 2.73,
					"Average penalty goals": 0,
					"Average direct free kick goals": 0.6
				}
			}
		} )" ); }, "The joint probability of scoring or getting an extra corner from a direct free kick cannot be greater than 1." );
}

std::vector<std::string> TDrawConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& drawConfiguration : {
		CDrawConfiguration{},
		futsim::ValueFromJSONKeyString<CDrawConfiguration>( R"( {
			"Draw configuration": {}
		} )" ) } )
	{
		result.push_back( std::string{ drawConfiguration.GetPossessionDrawConfiguration().JSON_KEY } );
		result.push_back( std::string{ drawConfiguration.GetFoulDrawConfiguration().JSON_KEY } );
		result.push_back( std::string{ drawConfiguration.GetChancesDrawConfiguration().JSON_KEY } );
		result.push_back( std::string{ drawConfiguration.GetGoalDrawConfiguration().JSON_KEY } );

		result.push_back( "Possession distribution:" );
		for( const auto& probability : drawConfiguration.CreatePossessionDistribution( 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Possession distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.CreatePossessionDistribution( 1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Foul distribution:" );
		for( const auto& probability : drawConfiguration.CreateFoulDistribution().probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Set piece distribution probability: " + std::to_string( drawConfiguration.CreateSetPieceDistribution().p() ) );
		result.push_back( "Chance distribution probability: " + std::to_string( drawConfiguration.CreateChanceDistribution( 1, 1 ).p() ) );
		result.push_back( "Chance distribution with attacking advantage probability: " + std::to_string( drawConfiguration.CreateChanceDistribution( 1, 1.1 ).p() ) );
		result.push_back( "Set piece type distribution:" );
		for( const auto& probability : drawConfiguration.CreateSetPieceTypeDistribution().probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Chance type distribution:" );
		for( const auto& probability : drawConfiguration.CreateChanceTypeDistribution().probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Penalty outcome distribution:" );
		for( const auto& probability : drawConfiguration.CreatePenaltyOutcomeDistribution( 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Penalty outcome distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.CreatePenaltyOutcomeDistribution( 1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Direct free kick outcome distribution:" );
		for( const auto& probability : drawConfiguration.CreateDirectFreeKickOutcomeDistribution( 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Direct free kick outcome distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.CreateDirectFreeKickOutcomeDistribution( 1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Indirect free kick outcome distribution:" );
		for( const auto& probability : drawConfiguration.CreateIndirectFreeKickOutcomeDistribution( 1, 1, 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Indirect free kick outcome distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.CreateIndirectFreeKickOutcomeDistribution( 1, 1, 1.1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Corner outcome distribution:" );
		for( const auto& probability : drawConfiguration.CreateCornerOutcomeDistribution( 1, 1, 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Corner outcome distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.CreateCornerOutcomeDistribution( 1, 1, 1.1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Far shot outcome distribution:" );
		for( const auto& probability : drawConfiguration.CreateFarShotOutcomeDistribution( 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Far shot outcome distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.CreateFarShotOutcomeDistribution( 1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "1 on 1 vs GK outcome distribution:" );
		for( const auto& probability : drawConfiguration.Create1vs1GKOutcomeDistribution( 1, 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "1 on 1 vs GK outcome distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.Create1vs1GKOutcomeDistribution( 1, 1.1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "1 on 1 vs DF outcome distribution:" );
		for( const auto& probability : drawConfiguration.Create1vs1DFOutcomeDistribution( 1, 1, 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "1 on 1 vs DF outcome distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.Create1vs1DFOutcomeDistribution( 1, 1, 1.1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Near shot outcome distribution:" );
		for( const auto& probability : drawConfiguration.CreateNearShotOutcomeDistribution( 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.push_back( "Near shot outcome distribution with attacking advantage:" );
		for( const auto& probability : drawConfiguration.CreateNearShotOutcomeDistribution( 1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );

		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, drawConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TDrawConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Possession draw configuration",
		"Foul draw configuration",
		"Chances draw configuration",
		"Goal draw configuration",
		"Possession distribution:",
		"0.642063",
		"0.239620",
		"0.118317",
		"Possession distribution with attacking advantage:",
		"0.651276",
		"0.239620",
		"0.109104",
		"Foul distribution:",
		"0.167785",
		"0.003783",
		"0.828432",
		"Set piece distribution probability: 0.188530",
		"Chance distribution probability: 0.217718",
		"Chance distribution with attacking advantage probability: 0.234387",
		"Set piece type distribution:",
		"0.067314",
		"0.194822",
		"0.737864",
		"Chance type distribution:",
		"0.252175",
		"0.134234",
		"0.191284",
		"0.201351",
		"0.220956",
		"Penalty outcome distribution:",
		"0.711538",
		"0.250000",
		"0.019231",
		"0.019231",
		"Penalty outcome distribution with attacking advantage:",
		"0.714871",
		"0.250000",
		"0.017564",
		"0.017564",
		"Direct free kick outcome distribution:",
		"0.056478",
		"0.250000",
		"0.346761",
		"0.346761",
		"Direct free kick outcome distribution with attacking advantage:",
		"0.061662",
		"0.250000",
		"0.344169",
		"0.344169",
		"Indirect free kick outcome distribution:",
		"0.033333",
		"0.250000",
		"0.358333",
		"0.358333",
		"Indirect free kick outcome distribution with attacking advantage:",
		"0.036504",
		"0.250000",
		"0.356748",
		"0.356748",
		"Corner outcome distribution:",
		"0.039426",
		"0.250000",
		"0.355287",
		"0.355287",
		"Corner outcome distribution with attacking advantage:",
		"0.043141",
		"0.250000",
		"0.353429",
		"0.353429",
		"Far shot outcome distribution:",
		"0.103917",
		"0.250000",
		"0.323042",
		"0.323042",
		"Far shot outcome distribution with attacking advantage:",
		"0.112746",
		"0.250000",
		"0.318627",
		"0.318627",
		"1 on 1 vs GK outcome distribution:",
		"0.350000",
		"0.250000",
		"0.200000",
		"0.200000",
		"1 on 1 vs GK outcome distribution with attacking advantage:",
		"0.367834",
		"0.250000",
		"0.191083",
		"0.191083",
		"1 on 1 vs DF outcome distribution:",
		"0.200000",
		"0.250000",
		"0.275000",
		"0.275000",
		"1 on 1 vs DF outcome distribution with attacking advantage:",
		"0.214286",
		"0.250000",
		"0.267857",
		"0.267857",
		"Near shot outcome distribution:",
		"0.128421",
		"0.250000",
		"0.310789",
		"0.310789",
		"Near shot outcome distribution with attacking advantage:",
		"0.138885",
		"0.250000",
		"0.305557",
		"0.305557",
		"{\n"
		"	\"Draw configuration\": {\n"
		"		\"Possession draw configuration\": {\n"
		"			\"Keep possession probability\": 0.6420632665059802\n"
		"		},\n"
		"		\"Foul draw configuration\": {\n"
		"			\"Average fouls\": 21.56578947368421,\n"
		"			\"Average yellow cards\": 3.6184210526315788,\n"
		"			\"Average red cards\": 0.08157894736842106\n"
		"		},\n"
		"		\"Chances draw configuration\": {\n"
		"			\"Average chances\": 25.28684210526316,\n"
		"			\"Average corner kicks\": 10.078947368421053,\n"
		"			\"Average 1 on 1 vs GK chances\": 2.0,\n"
		"			\"Average 1 on 1 vs DF chances\": 2.85,\n"
		"			\"Average near shots\": 3.0,\n"
		"			\"Average set pieces\": 4.065789473684211,\n"
		"			\"Average penalties\": 0.2736842105263158,\n"
		"			\"Average direct free kicks\": 0.7921052631578948\n"
		"		},\n"
		"		\"Goal draw configuration\": {\n"
		"			\"Average goals\": 2.7342105263157896,\n"
		"			\"Average penalty goals\": 0.19473684210526315,\n"
		"			\"Average direct free kick goals\": 0.04473684210526316,\n"
		"			\"Average indirect free kick goals\": 0.1,\n"
		"			\"Average corner goals\": 0.3973684210526316,\n"
		"			\"Average far shot goals\": 0.3421052631578947,\n"
		"			\"1 on 1 vs GK chance goal probability\": 0.35,\n"
		"			\"1 on 1 vs DF chance goal probability\": 0.2,\n"
		"			\"Extra corner probability\": 0.25\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
