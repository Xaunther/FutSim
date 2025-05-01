#pragma once

#include "EnumUtils.h"

namespace futsim::football
{

//! Macro to do something for each goal rule.
#define FOR_EACH_GOAL_RULE(DO, ...) \
    DO(NO, "No", __VA_ARGS__) \
    DO(SILVER_GOAL, "Silver goal", __VA_ARGS__) \
    DO(GOLDEN_GOAL, "Golden goal", __VA_ARGS__) \

//! Enumeration for the different goal rules.
enum class E_GOAL_RULE {
	FOR_EACH_GOAL_RULE( FUTSIM_LIST_ENUM )
};

// NOLINTBEGIN(*-avoid-c-arrays)
FUTSIM_SERIALIZE_ENUM( E_GOAL_RULE, {
	FOR_EACH_GOAL_RULE( FUTSIM_LIST_ENUM_ID, E_GOAL_RULE )
	} )
// NOLINTEND(*-avoid-c-arrays)

} // futsim::football namespace
