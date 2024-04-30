#include "football/CPlayState.h"

namespace futsim::football
{

const CPossessionState& CPlayState::GetPossessionState() const noexcept
{
	return mPossessionState;
}

const CPlayState::optional_foul_state& CPlayState::GetFoulState() const noexcept
{
	return mFoulState;
}

const CPlayState::chances_states& CPlayState::GetChancesStates() const noexcept
{
	return mChancesStates;
}

} // futsim::football namespace
