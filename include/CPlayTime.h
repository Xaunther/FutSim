#pragma once

#include "IJsonable.h"

#include "CPlayTimeTypes.h"

namespace futsim
{

/**
 * @brief Class that defines a play time phase of a match.
*/
class CPlayTime : public IJsonable
{
	using period_count = CPlayTimeTypes::period_count;
	using period_time = CPlayTimeTypes::period_time;

public:
	/**
	 * @brief Member constructor.
	 * @param aPeriodCount \ref mPeriodCount
	 * @param aPeriodTime \ref mPeriodTime
	 * @pre At least 1 period must compose the play time.
	 * @pre Each period must be at least 1 minute long.
	*/
	explicit CPlayTime(
		const period_count& aPeriodCount,
		const period_time& aPeriodTime );

private:
	//! Number of periods.
	period_count mPeriodCount;
	//! Length of each period.
	period_time mPeriodTime;
};

} // futsim namespace