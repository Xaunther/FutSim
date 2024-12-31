#pragma once

#include "../CPlayTime.h"
#include "football/traits/CPlayTime.h"

#include "football/types/CPlayTime.h"

namespace futsim::football
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

} // futsim::football namespace
