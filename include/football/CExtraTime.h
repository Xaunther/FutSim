#pragma once

#include "football/CPlayTime.h"

#include "football/EGoalRule.h"

namespace futsim::football
{

/**
 * @brief Class that defines an extra time phase of a football match.
*/
class CExtraTime : public CPlayTime
{
	using subs_count = CPlayTimeTypes::subs_count;
	using period_count = futsim::CPlayTimeTypes::period_count;
	using period_time = futsim::CPlayTimeTypes::period_time;

public:
	/**
	 * @copydoc futsim::football::CPlayTime::CPlayTime
	 * @param aGoalRule \ref mGoalRule
	*/
	explicit CExtraTime(
		const period_count& aPeriodCount = 2,
		const period_time& aPeriodTime = 15,
		const subs_count& aAvailableSubs = 1,
		const E_GOAL_RULE& aGoalRule = E_GOAL_RULE::NO );

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

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Extra time";
	//! JSON key for the \copybrief mGoalRule
	static inline constexpr std::string_view JSON_GOAL_RULE = "Goal rule";

private:
	//! Goal rule.
	E_GOAL_RULE mGoalRule;
};

} // futsim::football namespace