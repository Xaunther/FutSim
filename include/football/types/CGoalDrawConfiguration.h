#pragma once

#include "EnumUtils.h"

namespace futsim
{

template<typename tEnum, typename tIntType> class CEnumDistribution;

namespace football::types::CGoalDrawConfiguration
{

//! Enumeration for the different chance outcomes.
enum class E_CHANCE_OUTCOME {
	GOAL,
	EXTRA_CORNER,
	KEEP_POSSESSION,
	LOSE_POSSESSION,
};

//! Type for the goal draw.
using goal_draw_distribution = CEnumDistribution<E_CHANCE_OUTCOME, int>;

FUTSIM_SERIALIZE_ENUM( E_CHANCE_OUTCOME, {
	{E_CHANCE_OUTCOME::GOAL, "Goal"},
	{E_CHANCE_OUTCOME::EXTRA_CORNER, "Extra corner"},
	{E_CHANCE_OUTCOME::KEEP_POSSESSION, "Keep possession"},
	{E_CHANCE_OUTCOME::LOSE_POSSESSION, "Lose possession"},
	} );

} // football::types::CGoalDrawConfiguration namespace

} // futsim: namespace