#pragma once

#include "football/CPlayTime.h"
#include "football/traits/CExtraTime.h"

#include "football/CGoalRule.h"

namespace futsim::football
{

/**
 * @brief Class that defines an extra time phase of a football match.
*/
class CExtraTime : public CPlayTime, protected default_traits<CExtraTime>, protected json_traits<CExtraTime>
{
protected:
	using CPlayTime::period_count;
	using CPlayTime::subs_count;
	using default_traits<CExtraTime>::PERIOD_TIME;
	using default_traits<CExtraTime>::AVAILABLE_SUBS;

public:
	/**
	 * @copydoc futsim::football::CPlayTime::CPlayTime
	 * @param aGoalRule \ref mGoalRule
	*/
	explicit CExtraTime(
		const period_count& aPeriodCount = PERIOD_COUNT,
		const period_time& aPeriodTime = PERIOD_TIME,
		const subs_count& aAvailableSubs = AVAILABLE_SUBS,
		const CGoalRule& aGoalRule = {} );

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
	const CGoalRule& GetGoalRule() const noexcept;

private:
	//! Goal rule.
	CGoalRule mGoalRule;
};

} // futsim::football namespace
