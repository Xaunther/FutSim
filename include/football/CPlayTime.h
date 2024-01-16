#pragma once

#include "../CPlayTime.h"

#include "football/CPlayTimeTypes.h"

namespace futsim::football
{

/**
 * @brief Class that defines a play time phase of a football match.
*/
class CPlayTime : public futsim::CPlayTime
{
	using subs_count = CPlayTimeTypes::subs_count;
	using period_count = futsim::CPlayTimeTypes::period_count;
	using period_time = futsim::CPlayTimeTypes::period_time;

public:
	/**
	 * @copydoc futsim::CPlayTime::CPlayTime
	 * @param aAvailableSubs \ref mAvailableSubs
	 * @pre At least 1 period must compose the play time.
	 * @pre Each period must be at least 1 minute long.
	*/
	explicit CPlayTime(
		const period_count& aPeriodCount = 2,
		const period_time& aPeriodTime = 45,
		const subs_count& aAvailableSubs = 5 );

private:
	//! Number of available subs.
	subs_count mAvailableSubs;
};

} // futsim::football namespace