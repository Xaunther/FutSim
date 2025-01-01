#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include "football/types/CDrawConfiguration.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CGoalDrawConfiguration;
}

template <> struct default_traits<football::CGoalDrawConfiguration>
{
protected:
	using stat = football::types::CDrawConfiguration::stat;
public:
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageGoals
	static inline constexpr stat AVERAGE_GOALS = stat{ 1039 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAveragePenaltyGoals
	static inline constexpr stat AVERAGE_PENALTY_GOALS = stat{ 74 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageDirectFreeKickGoals
	static inline constexpr stat AVERAGE_DIRECT_FREE_KICK_GOALS = stat{ 17 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageIndirectFreeKickGoals
	static inline constexpr stat AVERAGE_INDIRECT_FREE_KICK_GOALS = stat{ 38 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageCornerGoals
	static inline constexpr stat AVERAGE_CORNER_GOALS = stat{ 151 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageFarShotGoals
	static inline constexpr stat AVERAGE_FAR_SHOT_GOALS = stat{ 147 } / 380 - AVERAGE_DIRECT_FREE_KICK_GOALS;
	//! Default \copybrief football::CGoalDrawConfiguration::m1vs1GKGoalProbability
	static inline constexpr stat ONE_VS_ONE_GK_GOAL_PROBABILITY = 0.35;
	//! Default \copybrief football::CGoalDrawConfiguration::m1vs1DFGoalProbability
	static inline constexpr stat ONE_VS_ONE_DF_GOAL_PROBABILITY = 0.2;
	//! Default \copybrief football::CGoalDrawConfiguration::mExtraCornerProbability
	static inline constexpr stat EXTRA_CORNER_PROBABILITY = 0.25;
};

template <> struct json_traits<football::CGoalDrawConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Goal draw configuration";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageGoals
	static inline constexpr std::string_view AVERAGE_GOALS_KEY = "Average goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAveragePenaltyGoals
	static inline constexpr std::string_view AVERAGE_PENALTY_GOALS_KEY = "Average penalty goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageDirectFreeKickGoals
	static inline constexpr std::string_view AVERAGE_DIRECT_FREE_KICK_GOALS_KEY = "Average direct free kick goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageIndirectFreeKickGoals
	static inline constexpr std::string_view AVERAGE_INDIRECT_FREE_KICK_GOALS_KEY = "Average indirect free kick goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageCornerGoals
	static inline constexpr std::string_view AVERAGE_CORNER_GOALS_KEY = "Average corner goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageFarShotGoals
	static inline constexpr std::string_view AVERAGE_FAR_SHOT_GOALS_KEY = "Average far shot goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::m1vs1GKGoalProbability
	static inline constexpr std::string_view ONE_VS_ONE_GK_GOAL_PROBABILITY_KEY = "1 on 1 vs GK chance goal probability";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::m1vs1DFGoalProbability
	static inline constexpr std::string_view ONE_VS_ONE_DF_GOAL_PROBABILITY_KEY = "1 on 1 vs DF chance goal probability";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mExtraCornerProbability
	static inline constexpr std::string_view EXTRA_CORNER_PROBABILITY_KEY = "Extra corner probability";
};

} // futsim namespace
