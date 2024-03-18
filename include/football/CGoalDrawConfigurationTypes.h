#pragma once

#include <nlohmann/json.hpp>
#include "CEnumDistribution.h"

namespace futsim::football::CGoalDrawConfigurationTypes
{

//! Enumeration for the different chance outcomes.
enum class E_CHANCE_OUTCOME {
	GOAL,
	EXTRA_CORNER,
	KEEP_POSSESSION,
	LOSE_POSSESSION,
};

//! Type for the goal draw.
using goal_draw_distribution = CEnumDistribution<E_CHANCE_OUTCOME>;

NLOHMANN_JSON_SERIALIZE_ENUM( E_CHANCE_OUTCOME, {
	{E_CHANCE_OUTCOME::GOAL, "Goal"},
	{E_CHANCE_OUTCOME::EXTRA_CORNER, "Extra corner"},
	{E_CHANCE_OUTCOME::KEEP_POSSESSION, "Keep possession"},
	{E_CHANCE_OUTCOME::LOSE_POSSESSION, "Lose possession"},
	} );

} // futsim::football::CGoalDrawConfigurationTypes namespace