#pragma once

#include <optional>

/**
 * @brief Types defined for \ref CTieCondition.
*/
namespace futsim::football::CTieConditionTypes
{

//! Type for a goal difference.
using goal_difference = int;
//! Type for a goal count.
using goal_count = unsigned int;
//! Type for an optional goal count.
using optional_goal_count = std::optional<goal_count>;

} // namespace futsim::football::CTieConditionTypes