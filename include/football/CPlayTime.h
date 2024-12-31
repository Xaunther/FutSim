#pragma once

#include "../CPlayTime.h"
#include "traits/default.h"
#include "traits/json.h"

#include "football/types/CPlayTime.h"

namespace futsim
{

namespace football
{
class CPlayTime;
}

template <> struct default_traits<football::CPlayTime>
{
private:
	using period_count = types::CPlayTime::period_count;
	using subs_count = football::types::CPlayTime::subs_count;
public:
	//! Default \copybrief football::CPlayTime::mPeriodCount
	static inline constexpr period_count PERIOD_COUNT = 2;
	//! Default \copybrief football::CPlayTime::mPeriodTime
	static inline constexpr period_count PERIOD_TIME = 45;
	//! Default \copybrief football::CPlayTime::mAvailableSubs
	static inline constexpr subs_count AVAILABLE_SUBS = 5;
};

template <> struct json_traits<football::CPlayTime> : public json_traits<CPlayTime>
{
	///! JSON key for the \copybrief football::CPlayTime::mAvailableSubs
	static inline constexpr std::string_view AVAILABLE_SUBS_KEY = "Available subs";
};

namespace football
{

/**
 * @brief Class that defines a play time phase of a football match.
*/
class CPlayTime : public futsim::CPlayTime, protected default_traits<CPlayTime>, protected json_traits<CPlayTime>
{
protected:
	using futsim::CPlayTime::period_count;
	using subs_count = types::CPlayTime::subs_count;

public:
	/**
	 * @copydoc futsim::CPlayTime::CPlayTime
	 * @param aAvailableSubs \ref mAvailableSubs
	*/
	explicit CPlayTime(
		const period_count& aPeriodCount = PERIOD_COUNT,
		const period_time& aPeriodTime = PERIOD_TIME,
		const subs_count& aAvailableSubs = AVAILABLE_SUBS );

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

private:
	//! Number of available subs.
	subs_count mAvailableSubs;
};

} // football namespace

} // futsim namespace
