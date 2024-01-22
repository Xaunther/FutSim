#pragma once

#include "EGoalRule.h"

#include <string>

namespace futsim::football
{

/**
 * @brief Converts the goal rule enum into a string.
 * @param aGoalRule Goal rule enum.
*/
const std::string& ToString( const E_GOAL_RULE& aGoalRule ) noexcept;

/**
 * @brief Converts the goal rule string into enum.
 * @param aGoalRule Goal rule string.
*/
const E_GOAL_RULE& ToGoalRule( const std::string_view aGoalRule );


} // futsim::football namespace
