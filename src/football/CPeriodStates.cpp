#include "football/CPeriodStates.h"
#include "football/IExtraTimePeriodPlayPolicy.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CPeriodStates::JSON( json& aJSON ) const noexcept
{
	AddKeyArrayToJSON( aJSON, mStates );
}

const CPeriodStates::period_states& CPeriodStates::GetStates() const noexcept
{
	return mStates;
}

CPeriodStates::goal_count CPeriodStates::CountScoredGoals( const bool aHomeTeam ) const noexcept
{
	return std::accumulate( mStates.cbegin(), mStates.cend(), goal_count{ 0 }, [ &aHomeTeam ]
	( const auto& aSum, const auto& aPeriodState )
	{
		return aSum + aPeriodState.CountScoredGoals( aHomeTeam );
	} );
}

} // futsim::football namespace