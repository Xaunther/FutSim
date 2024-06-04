#include "football/CMatchState.h"

namespace futsim::football
{

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