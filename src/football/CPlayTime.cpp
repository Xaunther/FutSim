#include "football/CPlayTime.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

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

CPlayTime::CPlayTime( const json& aJSON ) try :
	futsim::CPlayTime( aJSON ),
	mAvailableSubs( ValueFromRequiredJSONKey<subs_count>( aJSON, JSON_AVAILABLE_SUBS ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football play time from JSON." )

void CPlayTime::JSON( json& aJSON ) const noexcept
{
	futsim::CPlayTime::JSON( aJSON );
	AddToJSONKey( aJSON, mAvailableSubs, JSON_AVAILABLE_SUBS );
}

const CPlayTime::subs_count& CPlayTime::GetAvailableSubs() const noexcept
{
	return mAvailableSubs;
}

} // futsim::football namespace