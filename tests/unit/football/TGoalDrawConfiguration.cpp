#include "ATest.h"

#include "football/CGoalDrawConfiguration.h"

#include "CEnumDistribution.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TGoalDrawConfiguration )

void TGoalDrawConfiguration::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CGoalDrawConfiguration{ -1 };
	},
		"The average number of goals cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, -1 };
	},
		"The average number of penalty goals cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS, -1 };
	},
		"The average number of direct free kick goals cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS, -1 };
	},
		"The average number of indirect free kick goals cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_INDIRECT_FREE_KICK_GOALS, -1 };
	},
		"The average number of corner kick goals cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_INDIRECT_FREE_KICK_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_CORNER_GOALS, -1 };
	},
		"The average number of far shot goals cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_INDIRECT_FREE_KICK_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_CORNER_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_FAR_SHOT_GOALS, -1 };
	},
		"The probability to score in a 1 on 1 vs GK chance cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_INDIRECT_FREE_KICK_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_CORNER_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_FAR_SHOT_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::ONE_VS_ONE_GK_GOAL_PROBABILITY, -1 };
	},
		"The probability to score in a 1 on 1 vs DF chance cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_INDIRECT_FREE_KICK_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_CORNER_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_FAR_SHOT_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::ONE_VS_ONE_GK_GOAL_PROBABILITY, futsim::default_traits<CGoalDrawConfiguration>::ONE_VS_ONE_DF_GOAL_PROBABILITY, -1 };
	},
		"The probability to be awarded an extra corner cannot be negative." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_INDIRECT_FREE_KICK_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_CORNER_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_FAR_SHOT_GOALS,
		0.8, futsim::default_traits<CGoalDrawConfiguration>::ONE_VS_ONE_DF_GOAL_PROBABILITY, 0.3 };
	},
		"The joint probability of getting an extra corner or scoring in a 1 on 1 vs GK chance cannot be greater than 1." );
	CheckException( []()
	{
		CGoalDrawConfiguration{ futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_INDIRECT_FREE_KICK_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_CORNER_GOALS, futsim::default_traits<CGoalDrawConfiguration>::AVERAGE_FAR_SHOT_GOALS,
		futsim::default_traits<CGoalDrawConfiguration>::ONE_VS_ONE_GK_GOAL_PROBABILITY, 0.8, 0.3 };
	},
		"The joint probability of getting an extra corner or scoring in a 1 on 1 vs DF chance cannot be greater than 1." );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average goals": -1
			}
		} )" );
	}, "The average number of goals cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average penalty goals": -1
			}
		} )" );
	}, "The average number of penalty goals cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average direct free kick goals": -1
			}
		} )" );
	}, "The average number of direct free kick goals cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average indirect free kick goals": -1
			}
		} )" );
	}, "The average number of indirect free kick goals cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average corner goals": -1
			}
		} )" );
	}, "The average number of corner kick goals cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average far shot goals": -1
			}
		} )" );
	}, "The average number of far shot goals cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"1 on 1 vs GK chance goal probability": -1
			}
		} )" );
	}, "The probability to score in a 1 on 1 vs GK chance cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"1 on 1 vs DF chance goal probability": -1
			}
		} )" );
	}, "The probability to score in a 1 on 1 vs DF chance cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Extra corner probability": -1
			}
		} )" );
	}, "The probability to be awarded an extra corner cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"1 on 1 vs GK chance goal probability": 0.8,
				"Extra corner probability": 0.3
			}
		} )" );
	}, "The joint probability of getting an extra corner or scoring in a 1 on 1 vs GK chance cannot be greater than 1." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"1 on 1 vs DF chance goal probability": 0.8,
				"Extra corner probability": 0.3
			}
		} )" );
	}, "The joint probability of getting an extra corner or scoring in a 1 on 1 vs DF chance cannot be greater than 1." );
}

std::vector<std::string> TGoalDrawConfiguration::ObtainedResults() noexcept
{
	std::vector<std::string> result;
	for( const auto& goalDrawConfiguration : {
		CGoalDrawConfiguration{},
		CGoalDrawConfiguration{ 3, 0.1, 0.2, 0.3, 1, 0.5, 0.4, 0.15, 0.25 },
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {}
		} )" ),
		futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average goals": 3.0,
				"Average penalty goals": 0.1,
				"Average direct free kick goals": 0.2,
				"Average indirect free kick goals": 0.3,
				"Average corner goals": 1.0,
				"Average far shot goals": 0.5,
				"1 on 1 vs GK chance goal probability": 0.4,
				"1 on 1 vs DF chance goal probability": 0.15,
				"Extra corner probability": 0.25
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::AVERAGE_GOALS_KEY } + ": " + std::to_string( goalDrawConfiguration.GetAverageGoals() ) );
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::AVERAGE_PENALTY_GOALS_KEY } + ": " + std::to_string( goalDrawConfiguration.GetAveragePenaltyGoals() ) );
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::AVERAGE_DIRECT_FREE_KICK_GOALS_KEY } + ": " + std::to_string( goalDrawConfiguration.GetAverageDirectFreeKickGoals() ) );
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::AVERAGE_INDIRECT_FREE_KICK_GOALS_KEY } + ": " + std::to_string( goalDrawConfiguration.GetAverageIndirectFreeKickGoals() ) );
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::AVERAGE_CORNER_GOALS_KEY } + ": " + std::to_string( goalDrawConfiguration.GetAverageCornerGoals() ) );
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::AVERAGE_FAR_SHOT_GOALS_KEY } + ": " + std::to_string( goalDrawConfiguration.GetAverageFarShotGoals() ) );
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::ONE_VS_ONE_GK_GOAL_PROBABILITY_KEY } + ": " + std::to_string( goalDrawConfiguration.Get1vs1GKGoalProbability() ) );
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::ONE_VS_ONE_DF_GOAL_PROBABILITY_KEY } + ": " + std::to_string( goalDrawConfiguration.Get1vs1DFGoalProbability() ) );
		result.push_back( std::string{ futsim::json_traits<CGoalDrawConfiguration>::EXTRA_CORNER_PROBABILITY_KEY } + ": " + std::to_string( goalDrawConfiguration.GetExtraCornerProbability() ) );
		result.emplace_back( "Default 1 on 1 vs GK chance outcome distribution" );
		for( const auto& probability : goalDrawConfiguration.Create1vs1GKOutcomeDistribution( 1, 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.emplace_back( "1.1 attacker advantage 1 on 1 vs GK chance outcome distribution" );
		for( const auto& probability : goalDrawConfiguration.Create1vs1GKOutcomeDistribution( 1, 1.1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.emplace_back( "Default 1 on 1 vs DF chance outcome distribution" );
		for( const auto& probability : goalDrawConfiguration.Create1vs1DFOutcomeDistribution( 1, 1, 1, 1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		result.emplace_back( "1.1 attacker advantage 1 on 1 vs DF chance outcome distribution" );
		for( const auto& probability : goalDrawConfiguration.Create1vs1DFOutcomeDistribution( 1, 1, 1.1, 1.1 ).probabilities() )
			result.push_back( std::to_string( probability ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, goalDrawConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TGoalDrawConfiguration::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Average goals: 2.734211",
		"Average penalty goals: 0.194737",
		"Average direct free kick goals: 0.044737",
		"Average indirect free kick goals: 0.100000",
		"Average corner goals: 0.397368",
		"Average far shot goals: 0.342105",
		"1 on 1 vs GK chance goal probability: 0.350000",
		"1 on 1 vs DF chance goal probability: 0.200000",
		"Extra corner probability: 0.250000",
		"Default 1 on 1 vs GK chance outcome distribution",
		"0.350000",
		"0.250000",
		"0.000000",
		"0.200000",
		"0.000000",
		"0.200000",
		"1.1 attacker advantage 1 on 1 vs GK chance outcome distribution",
		"0.367834",
		"0.250000",
		"0.000000",
		"0.191083",
		"0.000000",
		"0.191083",
		"Default 1 on 1 vs DF chance outcome distribution",
		"0.200000",
		"0.125000",
		"0.125000",
		"0.137500",
		"0.137500",
		"0.275000",
		"1.1 attacker advantage 1 on 1 vs DF chance outcome distribution",
		"0.214286",
		"0.125000",
		"0.125000",
		"0.133929",
		"0.133929",
		"0.267857",
		"{\n"
		"	\"Goal draw configuration\": {\n"
		"		\"Average goals\": 2.7342105263157896,\n"
		"		\"Average penalty goals\": 0.19473684210526315,\n"
		"		\"Average direct free kick goals\": 0.04473684210526316,\n"
		"		\"Average indirect free kick goals\": 0.1,\n"
		"		\"Average corner goals\": 0.3973684210526316,\n"
		"		\"Average far shot goals\": 0.3421052631578947,\n"
		"		\"1 on 1 vs GK chance goal probability\": 0.35,\n"
		"		\"1 on 1 vs DF chance goal probability\": 0.2,\n"
		"		\"Extra corner probability\": 0.25\n"
		"	}\n"
		"}",
		"Average goals: 3.000000",
		"Average penalty goals: 0.100000",
		"Average direct free kick goals: 0.200000",
		"Average indirect free kick goals: 0.300000",
		"Average corner goals: 1.000000",
		"Average far shot goals: 0.500000",
		"1 on 1 vs GK chance goal probability: 0.400000",
		"1 on 1 vs DF chance goal probability: 0.150000",
		"Extra corner probability: 0.250000",
		"Default 1 on 1 vs GK chance outcome distribution",
		"0.400000",
		"0.250000",
		"0.000000",
		"0.175000",
		"0.000000",
		"0.175000",
		"1.1 attacker advantage 1 on 1 vs GK chance outcome distribution",
		"0.417722",
		"0.250000",
		"0.000000",
		"0.166139",
		"0.000000",
		"0.166139",
		"Default 1 on 1 vs DF chance outcome distribution",
		"0.150000",
		"0.125000",
		"0.125000",
		"0.150000",
		"0.150000",
		"0.300000",
		"1.1 attacker advantage 1 on 1 vs DF chance outcome distribution",
		"0.161765",
		"0.125000",
		"0.125000",
		"0.147059",
		"0.147059",
		"0.294118",
		"{\n"
		"	\"Goal draw configuration\": {\n"
		"		\"Average goals\": 3.0,\n"
		"		\"Average penalty goals\": 0.1,\n"
		"		\"Average direct free kick goals\": 0.2,\n"
		"		\"Average indirect free kick goals\": 0.3,\n"
		"		\"Average corner goals\": 1.0,\n"
		"		\"Average far shot goals\": 0.5,\n"
		"		\"1 on 1 vs GK chance goal probability\": 0.4,\n"
		"		\"1 on 1 vs DF chance goal probability\": 0.15,\n"
		"		\"Extra corner probability\": 0.25\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
