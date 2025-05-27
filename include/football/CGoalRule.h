#pragma once

#include "IJsonable.h"
#include "football/traits/CGoalRule.h"

#include <variant>

namespace futsim::football
{

/**
 * @brief Class that represents a goal rule.
*/
class CGoalRule : public IJsonable, protected json_traits<CGoalRule>
{
public:
	//! Class for the absence of a goal rule.
	struct NO
	{
		//! Conversion to string.
		inline constexpr operator std::string_view() const noexcept{ return CGoalRule::NO_KEY; }
	};

	//! Class for a silver goal rule.
	struct SILVER_GOAL
	{
		//! Conversion to string.
		inline constexpr operator std::string_view() const noexcept{ return CGoalRule::SILVER_GOAL_KEY; }
	};

	//! Class for a golden goal rule.
	struct GOLDEN_GOAL
	{
		//! Conversion to string.
		inline constexpr operator std::string_view() const noexcept{ return CGoalRule::GOLDEN_GOAL_KEY; }
	};

	//! Type for the goal rule variant.
	using variant = std::variant<NO, SILVER_GOAL, GOLDEN_GOAL>;

private:
	//! Goal rule contained.
	variant mRule;
};

} // futsim::football namespace
