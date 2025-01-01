#include "football/CMatchState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CMatchState::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mMandatoryPlayTimeState, MANDATORY_PERIOD_STATES_KEY );
	if( mExtraTimeState )
		AddToJSONKey( aJSON, *mExtraTimeState, EXTRA_PERIOD_STATES_KEY );
	if( mPenaltyShootoutState )
		AddToJSONKey( aJSON, *mPenaltyShootoutState );
}

const CPeriodStates& CMatchState::GetMandatoryPlayTimeState() const noexcept
{
	return mMandatoryPlayTimeState;
}

const CMatchState::optional_period_states& CMatchState::GetExtraTimeState() const noexcept
{
	return mExtraTimeState;
}

const CMatchState::optional_penalty_shootout_state& CMatchState::GetPenaltyShootoutState() const noexcept
{
	return mPenaltyShootoutState;
}

} // futsim::football namespace
