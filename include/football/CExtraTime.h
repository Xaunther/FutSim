#pragma once

#include "football/CPlayTime.h"

#include "football/EGoalRule.h"

namespace futsim
{

namespace football
{

/**
 * @brief Class that defines an extra time phase of a football match.
*/
class CExtraTime : public CPlayTime
{
public:
	/**
	 * @copydoc futsim::football::CPlayTime::CPlayTime
	 * @param aGoalRule \ref mGoalRule
	*/
	explicit CExtraTime(
		const period_count& aPeriodCount = DEFAULT_PERIOD_COUNT,
		const period_time& aPeriodTime = DEFAULT_PERIOD_TIME,
		const subs_count& aAvailableSubs = DEFAULT_AVAILABLE_SUBS,
		const E_GOAL_RULE& aGoalRule = DEFAULT_GOAL_RULE );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CExtraTime( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mGoalRule
	const E_GOAL_RULE& GetGoalRule() const noexcept;

	//! JSON key for the \copybrief mGoalRule
	static inline constexpr std::string_view JSON_GOAL_RULE = "Goal rule";

	//! Default \copybrief mPeriodTime
	static inline constexpr period_count DEFAULT_PERIOD_TIME = 15;
	//! Default \copybrief mAvailableSubs
	static inline constexpr subs_count DEFAULT_AVAILABLE_SUBS = 1;
	//! Default \copybrief mGoalRule
	static inline constexpr E_GOAL_RULE DEFAULT_GOAL_RULE = E_GOAL_RULE::NO;

private:
	//! Goal rule.
	E_GOAL_RULE mGoalRule;
};

} // football namespace

template <> struct json_traits<football::CExtraTime>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Extra time";
};

} // futsim namespace