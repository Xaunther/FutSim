#pragma once

#include "EnumUtils.h"

namespace futsim::football
{

//! Enumeration for the different goal rules.
enum class E_GOAL_RULE {
	NO,
	SILVER_GOAL,
	GOLDEN_GOAL
};

FUTSIM_SERIALIZE_ENUM( E_GOAL_RULE, {
	{E_GOAL_RULE::NO, "No"},
	{E_GOAL_RULE::SILVER_GOAL, "Silver goal"},
	{E_GOAL_RULE::GOLDEN_GOAL, "Golden goal"},
	} )

} // futsim::football namespace