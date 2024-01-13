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

	//! Number of periods.
	period_count mPeriodCount;
	//! Length of each period.
	period_time mPeriodTime;
};

} // futsim namespace