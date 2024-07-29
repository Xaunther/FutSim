#pragma once

#include "../CPlayTime.h"

#include "football/types/CPlayTime.h"
#include "DefaultTraits.h"

namespace futsim
{

namespace football
{
class CPlayTime;
}

template <> struct default_traits<football::CPlayTime>
{
protected:
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

namespace football
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
		const period_count& aPeriodCount = default_traits<CPlayTime>::PERIOD_COUNT,
		const period_time& aPeriodTime = default_traits<CPlayTime>::PERIOD_TIME,
		const subs_count& aAvailableSubs = default_traits<CPlayTime>::AVAILABLE_SUBS );

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

template <> struct json_traits<football::CPlayTime> : public json_traits<CPlayTime>
{
	///! JSON key for the \copybrief football::CPlayTime::mAvailableSubs
	static inline constexpr std::string_view AVAILABLE_SUBS = "Available subs";
};

} // futsim namespace
