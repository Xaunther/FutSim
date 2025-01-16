#include "football/CPeriodStates.h"
#include "football/IExtraTimePeriodPlayPolicy.h"

#include "JsonUtils.h"

namespace futsim::football
{

namespace
{

const types::CPenaltyShootoutState::score operator+( const types::CPenaltyShootoutState::score& aLHS,
		const types::CPenaltyShootoutState::score& aRHS );

} // anonymous namespace

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

types::CPenaltyShootoutState::score CPeriodStates::CountScore() const noexcept
{
	return std::accumulate( mStates.cbegin(), mStates.cend(), types::CPenaltyShootoutState::score{}, []
	( const auto& aScore, const auto& aPeriodState )
	{
		return aScore + aPeriodState.CountScore();
	} );
}

namespace
{

const types::CPenaltyShootoutState::score operator+( const types::CPenaltyShootoutState::score& aLHS,
		const types::CPenaltyShootoutState::score& aRHS )
{
	return types::CPenaltyShootoutState::score{ aLHS.home + aRHS.home, aLHS.away + aRHS.away };
}

} // anonymous namespace

} // futsim::football namespace
