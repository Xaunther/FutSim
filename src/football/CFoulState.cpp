#include "football/CFoulState.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

std::string_view CFoulState::GetCommitter() const noexcept
{
	return mCommitter;
}

const CFoulDrawConfigurationTypes::E_FOUL_DRAW_OUTCOME& CFoulState::GetOutcome() const noexcept
{
	return mOutcome;
}

} // futsim::football namespace