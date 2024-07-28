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
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football play time." )

CPlayTime::CPlayTime( const json& aJSON ) try :
	futsim::CPlayTime( ValueFromOptionalJSONKey<period_count>( aJSON, json_traits<CPlayTime>::PERIOD_COUNT, DEFAULT_PERIOD_COUNT ),
		ValueFromOptionalJSONKey<period_time>( aJSON, json_traits<CPlayTime>::PERIOD_TIME, DEFAULT_PERIOD_TIME ) ),
	mAvailableSubs( ValueFromOptionalJSONKey<subs_count>( aJSON, json_traits<CPlayTime>::AVAILABLE_SUBS ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football play time from JSON." )

void CPlayTime::JSON( json& aJSON ) const noexcept
{
	futsim::CPlayTime::JSON( aJSON );
	if( mAvailableSubs )
		AddToJSONKey( aJSON, *mAvailableSubs, json_traits<CPlayTime>::AVAILABLE_SUBS );
}

const CPlayTime::subs_count& CPlayTime::GetAvailableSubs() const noexcept
{
	return mAvailableSubs;
}

} // futsim::football namespace