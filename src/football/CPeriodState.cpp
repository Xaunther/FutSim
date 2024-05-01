#include "football/CPeriodState.h"

namespace futsim::football
{

const CPeriodState::plays& CPeriodState::GetPlays() const noexcept
{
	return mPlays;
}

} // futsim::football namespace