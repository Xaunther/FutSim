#pragma once

#include "football/EPlayerPosition.h"

#include "EnumUtils.h"

namespace futsim
{

template<typename tEnum, typename tIntType> class CEnumDistribution;

namespace football::types::CGoalDrawConfiguration
{

//! Enumeration for the different chance outcomes.
enum class E_CHANCE_OUTCOME {
	GOAL,
	EXTRA_CORNER_FROM_GK,
	EXTRA_CORNER_FROM_DF,
	KEEP_POSSESSION_FROM_GK,
	KEEP_POSSESSION_FROM_DF,
	LOSE_POSSESSION,
};

//! Type for the goal draw.
using goal_draw_distribution = CEnumDistribution<E_CHANCE_OUTCOME, int>;
//! Type for the position draw.
using position_draw_distribution = CEnumDistribution<E_PLAYER_POSITION, int>;

// NOLINTBEGIN(*-avoid-c-arrays)
FUTSIM_SERIALIZE_ENUM( E_CHANCE_OUTCOME, {
	{E_CHANCE_OUTCOME::GOAL, "Goal"},
	{E_CHANCE_OUTCOME::EXTRA_CORNER_FROM_GK, "Extra corner from goalkeeper"},
	{E_CHANCE_OUTCOME::EXTRA_CORNER_FROM_DF, "Extra corner from defender"},
	{E_CHANCE_OUTCOME::KEEP_POSSESSION_FROM_GK, "Keep possession from goalkeeper"},
	{E_CHANCE_OUTCOME::KEEP_POSSESSION_FROM_DF, "Keep possession from defender"},
	{E_CHANCE_OUTCOME::LOSE_POSSESSION, "Lose possession"},
	} );
// NOLINTEND(*-avoid-c-arrays)

} // football::types::CGoalDrawConfiguration namespace

} // futsim: namespace
