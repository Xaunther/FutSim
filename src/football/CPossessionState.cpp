#include "football/CPossessionState.h"

namespace futsim::football
{

const CPossessionState::optional_name& CPossessionState::GetTackler() const noexcept
{
	return mTackler;
}

const CPossessionState::optional_name& CPossessionState::GetPasser() const noexcept
{
	return mPasser;
}

const CPossessionState::E_POSSESSION_DRAW_OUTCOME& CPossessionState::GetOutcome() const noexcept
{
	return mOutcome;
}

} // futsim::football namespace