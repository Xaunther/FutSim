#include "football/CPlayTime.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

CPlayTime::CPlayTime(
	const period_count& aPeriodCount,
	const period_time& aPeriodTime,
	const subs_count& aAvailableSubs
) try :
	futsim::CPlayTime( aPeriodCount, aPeriodTime ),
	mAvailableSubs( aAvailableSubs )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football play time from JSON." )

} // futsim::football namespace