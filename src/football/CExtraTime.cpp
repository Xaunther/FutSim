#include "football/CExtraTime.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

CExtraTime::CExtraTime(
	const period_count& aPeriodCount,
	const period_time& aPeriodTime,
	const subs_count& aAvailableSubs,
	const E_GOAL_RULE& aGoalRule
) try :
	CPlayTime( aPeriodCount, aPeriodTime, aAvailableSubs ),
	mGoalRule( aGoalRule )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football extra time." )

CExtraTime::CExtraTime( const json& aJSON ) try :
	CPlayTime( ValueFromOptionalJSONKey<period_count>( aJSON, json_traits<CPlayTime>::PERIOD_COUNT, default_traits<CPlayTime>::PERIOD_COUNT ),
		ValueFromOptionalJSONKey<period_time>( aJSON, json_traits<CPlayTime>::PERIOD_TIME, default_traits<CExtraTime>::PERIOD_TIME ),
		ValueFromOptionalJSONKey<subs_count>( aJSON, json_traits<CPlayTime>::AVAILABLE_SUBS, default_traits<CExtraTime>::AVAILABLE_SUBS ) ),
	mGoalRule( ValueFromOptionalJSONKey<E_GOAL_RULE>( aJSON, json_traits<CExtraTime>::GOAL_RULE, default_traits<CExtraTime>::GOAL_RULE ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football extra time from JSON." )

void CExtraTime::JSON( json& aJSON ) const noexcept
{
	CPlayTime::JSON( aJSON );
	if( mGoalRule != default_traits<CExtraTime>::GOAL_RULE )
		AddToJSONKey( aJSON, mGoalRule, json_traits<CExtraTime>::GOAL_RULE );
}

const E_GOAL_RULE& CExtraTime::GetGoalRule() const noexcept
{
	return mGoalRule;
}

} // futsim::football namespace