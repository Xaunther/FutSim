#pragma once

#include "football/CPlayTime.h"

#include "football/EGoalRule.h"

namespace futsim
{

namespace football
{
class CExtraTime;
}

template <> struct default_traits<football::CExtraTime>
{
protected:
	using period_count = types::CPlayTime::period_count;
	using subs_count = football::types::CPlayTime::subs_count;
public:
	//! Default \copybrief football::CExtraTime::mPeriodTime
	static inline constexpr period_count PERIOD_TIME = 15;
	//! Default \copybrief football::CExtraTime::mAvailableSubs
	static inline constexpr subs_count AVAILABLE_SUBS = 1;
	//! Default \copybrief football::CExtraTime::mGoalRule
	static inline constexpr football::E_GOAL_RULE GOAL_RULE = football::E_GOAL_RULE::NO;
};

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
		const period_count& aPeriodCount = default_traits<CPlayTime>::PERIOD_COUNT,
		const period_time& aPeriodTime = default_traits<CExtraTime>::PERIOD_TIME,
		const subs_count& aAvailableSubs = default_traits<CExtraTime>::AVAILABLE_SUBS,
		const E_GOAL_RULE& aGoalRule = default_traits<CExtraTime>::GOAL_RULE );

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

private:
	//! Goal rule.
	E_GOAL_RULE mGoalRule;
};

} // football namespace

template <> struct json_traits<football::CExtraTime>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Extra time";
	//! JSON key for the \copybrief football::CExtraTime::mGoalRule
	static inline constexpr std::string_view GOAL_RULE = "Goal rule";
};

} // futsim namespace