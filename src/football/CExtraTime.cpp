#include "football/CExtraTime.h"

#include "ExceptionUtils.h"
#include "football/GoalRuleUtils.h"
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
	CPlayTime( aJSON ),
	mGoalRule( ToGoalRule( ValueFromOptionalJSONKey<std::string_view>( aJSON, JSON_GOAL_RULE, ToString( E_GOAL_RULE::NO ) ) ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the football extra time from JSON." )

void CExtraTime::JSON( json& aJSON ) const noexcept
{
	CPlayTime::JSON( aJSON );
	if( mGoalRule != E_GOAL_RULE::NO )
		AddToJSONKey( aJSON, ToString( mGoalRule ), JSON_GOAL_RULE );
}

} // futsim::football namespace