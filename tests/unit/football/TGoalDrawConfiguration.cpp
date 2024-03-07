#include "ITest.h"

#include "football/CGoalDrawConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TGoalDrawConfiguration )

void TGoalDrawConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CGoalDrawConfiguration{ -1 }; },
		"The average number of goals cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, -1 }; },
		"The average number of penalty goals cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS, -1 }; },
		"The average number of direct free kick goals cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS, -1 }; },
		"The average number of indirect free kick goals cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS, -1 }; },
		"The average number of corner kick goals cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_CORNER_GOALS, -1 }; },
		"The average number of far shot goals cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_CORNER_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_FAR_SHOT_GOALS, -1 }; },
		"The probability to score in a 1 on 1 vs GK chance cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_CORNER_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_FAR_SHOT_GOALS,
		CGoalDrawConfiguration::DEFAULT_1VS1_GK_GOAL_PROBABILITY, -1 }; },
		"The probability to score in a 1 on 1 vs DF chance cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_CORNER_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_FAR_SHOT_GOALS,
		CGoalDrawConfiguration::DEFAULT_1VS1_GK_GOAL_PROBABILITY, CGoalDrawConfiguration::DEFAULT_1VS1_DF_GOAL_PROBABILITY, -1 }; },
		"The probability to be awarded an extra corner cannot be negative." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_CORNER_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_FAR_SHOT_GOALS,
		0.8, CGoalDrawConfiguration::DEFAULT_1VS1_DF_GOAL_PROBABILITY, 0.3 }; },
		"The joint probability of getting an extra corner or scoring in a 1 on 1 vs GK chance cannot be greater than 1." );
	CheckException( []() { CGoalDrawConfiguration{ CGoalDrawConfiguration::DEFAULT_AVERAGE_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_PENALTY_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS,
		CGoalDrawConfiguration::DEFAULT_AVERAGE_CORNER_GOALS, CGoalDrawConfiguration::DEFAULT_AVERAGE_FAR_SHOT_GOALS,
		CGoalDrawConfiguration::DEFAULT_1VS1_GK_GOAL_PROBABILITY, 0.8, 0.3 }; },
		"The joint probability of getting an extra corner or scoring in a 1 on 1 vs DF chance cannot be greater than 1." );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average goals": -1
			}
		} )" ); }, "The average number of goals cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average penalty goals": -1
			}
		} )" ); }, "The average number of penalty goals cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average direct free kick goals": -1
			}
		} )" ); }, "The average number of direct free kick goals cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average indirect free kick goals": -1
			}
		} )" ); }, "The average number of indirect free kick goals cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average corner goals": -1
			}
		} )" ); }, "The average number of corner kick goals cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Average far shot goals": -1
			}
		} )" ); }, "The average number of far shot goals cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"1 on 1 vs GK chance goal probability": -1
			}
		} )" ); }, "The probability to score in a 1 on 1 vs GK chance cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"1 on 1 vs DF chance goal probability": -1
			}
		} )" ); }, "The probability to score in a 1 on 1 vs DF chance cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"Extra corner probability": -1
			}
		} )" ); }, "The probability to be awarded an extra corner cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"1 on 1 vs GK chance goal probability": 0.8,
				"Extra corner probability": 0.3
			}
		} )" ); }, "The joint probability of getting an extra corner or scoring in a 1 on 1 vs GK chance cannot be greater than 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CGoalDrawConfiguration>( R"( {
			"Goal draw configuration": {
				"1 on 1 vs DF chance goal probability": 0.8,
				"Extra corner probability": 0.3
			}
		} )" ); }, "The joint probability of getting an extra corner or scoring in a 1 on 1 vs DF chance cannot be greater than 1." );
}

std::vector<std::string> TGoalDrawConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TGoalDrawConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
