#include "football/CExtraTime.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

CExtraTime::CExtraTime(
	const period_count& aPeriodCount,
	const period_time& aPeriodTime,
	const subs_count& aAvailableSubs,
	const CGoalRule& aGoalRule
) try :
	CPlayTime( aPeriodCount, aPeriodTime, aAvailableSubs ),
	mGoalRule( aGoalRule )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football extra time." )

CExtraTime::CExtraTime( const json& aJSON ) try :
	CPlayTime( ValueFromOptionalJSONKey<period_count>( aJSON, PERIOD_COUNT_KEY, PERIOD_COUNT ),
		ValueFromOptionalJSONKey<period_time>( aJSON, PERIOD_TIME_KEY, PERIOD_TIME ),
		ValueFromOptionalJSONKey<subs_count>( aJSON, AVAILABLE_SUBS_KEY, AVAILABLE_SUBS ) ),
	mGoalRule( ValueFromOptionalJSONKey<CGoalRule>( aJSON ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football extra time from JSON." )

void CExtraTime::JSON( json& aJSON ) const noexcept
{
	CPlayTime::JSON( aJSON );
	AddToOptionalJSONKey( aJSON, mGoalRule );
}

const CGoalRule& CExtraTime::GetGoalRule() const noexcept
{
	return mGoalRule;
}

} // futsim::football namespace
