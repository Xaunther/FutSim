#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include "football/EGoalRule.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CGoalRule;
}

template <> struct json_traits<football::CGoalRule>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Goal rule";
	//! JSON key for the absence of rule.
	static inline constexpr std::string_view NO_KEY = "No";
	//! JSON key for the silver goal rule.
	static inline constexpr std::string_view SILVER_GOAL_KEY = "Silver goal";
	//! JSON key for the golden goal rule.
	static inline constexpr std::string_view GOLDEN_GOAL_KEY = "Golden goal";

	/**
	 * @brief Define comparisor operators.
	 */
	auto operator<=>( const json_traits<football::CGoalRule>& ) const = default;
};

} // futsim namespace
