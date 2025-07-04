#pragma once

#include "IJsonable.h"
#include "football/traits/CGoalRule.h"

#include "traits/has_type.h"

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
		//! Define comparisor operators.
		auto operator<=>( const NO& ) const = default;
	};

	//! Class for a silver goal rule.
	struct SILVER_GOAL
	{
		//! Conversion to string.
		inline constexpr operator std::string_view() const noexcept{ return CGoalRule::SILVER_GOAL_KEY; }
		//! Define comparisor operators.
		auto operator<=>( const SILVER_GOAL& ) const = default;
	};

	//! Class for a golden goal rule.
	struct GOLDEN_GOAL
	{
		//! Conversion to string.
		inline constexpr operator std::string_view() const noexcept{ return CGoalRule::GOLDEN_GOAL_KEY; }
		//! Define comparisor operators.
		auto operator<=>( const GOLDEN_GOAL& ) const = default;
	};

	//! Type for the goal rule variant.
	using variant = std::variant<NO, SILVER_GOAL, GOLDEN_GOAL>;

	/**
	 * @brief Member constructor.
	 * @param aRule \ref mRule
	 */
	// cppcheck-suppress noExplicitConstructor
	template <has_type_c<variant> T = NO> CGoalRule( const T& aRule = {} ) noexcept;

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	 */
	explicit CGoalRule( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Conversion to variant.
	//! @{
	inline constexpr operator variant&() noexcept{ return mRule; }
	inline constexpr operator const variant&() const noexcept{ return mRule; }
	//! @}

	/**
	 * @brief Define comparisor operators.
	 */
	auto operator<=>( const CGoalRule& ) const = default;

private:
	//! Goal rule contained.
	variant mRule;
};

} // futsim::football namespace
