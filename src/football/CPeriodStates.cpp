#include "football/CPeriodStates.h"

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

types::CPenaltyShootoutState::score CPeriodStates::CountScore() const noexcept
{
	return std::accumulate( mStates.cbegin(), mStates.cend(), types::CPenaltyShootoutState::score{}, []
	( const auto& aScore, const auto& aPeriodState )
	{
		return aScore + aPeriodState.CountScore();
	} );
}

} // futsim::football namespace
