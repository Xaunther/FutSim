#include "football/CPeriodStates.h"

namespace futsim::football
{

const CPeriodStates::period_states& CPeriodStates::GetStates() const noexcept
{
	return mStates;
}

} // futsim::football namespace