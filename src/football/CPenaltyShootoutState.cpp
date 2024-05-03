#include "football/CPenaltyShootoutState.h"

namespace futsim::football
{

const CPenaltyShootoutState::penalty_states& CPenaltyShootoutState::GetPenalties() const noexcept
{
	return mPenalties;
}

}  // futsim::football namespace