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
	CPlayTime( ValueFromOptionalJSONKey<period_count>( aJSON, JSON_PERIOD_COUNT, DEFAULT_PERIOD_COUNT ),
		ValueFromOptionalJSONKey<period_time>( aJSON, JSON_PERIOD_TIME, DEFAULT_PERIOD_TIME ),
		ValueFromOptionalJSONKey<subs_count>( aJSON, JSON_AVAILABLE_SUBS, DEFAULT_AVAILABLE_SUBS ) ),
	mGoalRule( ValueFromOptionalJSONKey<E_GOAL_RULE>( aJSON, JSON_GOAL_RULE, DEFAULT_GOAL_RULE ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football extra time from JSON." )

void CExtraTime::JSON( json& aJSON ) const noexcept
{
	CPlayTime::JSON( aJSON );
	if( mGoalRule != DEFAULT_GOAL_RULE )
		AddToJSONKey( aJSON, mGoalRule, JSON_GOAL_RULE );
}

const E_GOAL_RULE& CExtraTime::GetGoalRule() const noexcept
{
	return mGoalRule;
}

} // futsim::football namespace