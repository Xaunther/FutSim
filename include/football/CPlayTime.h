#pragma once

#include "../CPlayTime.h"

#include "football/types/CPlayTime.h"

namespace futsim::football
{

/**
 * @brief Class that defines a play time phase of a football match.
*/
class CPlayTime : public futsim::CPlayTime
{
protected:
	using subs_count = types::CPlayTime::subs_count;

public:
	/**
	 * @copydoc futsim::CPlayTime::CPlayTime
	 * @param aAvailableSubs \ref mAvailableSubs
	*/
	explicit CPlayTime(
		const period_count& aPeriodCount = DEFAULT_PERIOD_COUNT,
		const period_time& aPeriodTime = DEFAULT_PERIOD_TIME,
		const subs_count& aAvailableSubs = DEFAULT_AVAILABLE_SUBS );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPlayTime( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mAvailableSubs
	const subs_count& GetAvailableSubs() const noexcept;

	//! JSON key for the \copybrief mAvailableSubs
	static inline constexpr std::string_view JSON_AVAILABLE_SUBS = "Available subs";

	//! Default \copybrief mPeriodCount
	static inline constexpr period_count DEFAULT_PERIOD_COUNT = 2;
	//! Default \copybrief mPeriodTime
	static inline constexpr period_count DEFAULT_PERIOD_TIME = 45;
	//! Default \copybrief mAvailableSubs
	static inline constexpr subs_count DEFAULT_AVAILABLE_SUBS = 5;

private:
	//! Number of available subs.
	subs_count mAvailableSubs;
};

} // futsim::football namespace