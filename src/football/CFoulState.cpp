#include "football/CFoulState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CFoulState::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mCommitter, COMMIITER_KEY );
	AddToJSONKey( aJSON, mOutcome, OUTCOME_KEY );
}

std::string_view CFoulState::GetCommitter() const noexcept
{
	return mCommitter;
}

const types::CFoulDrawConfiguration::E_FOUL_DRAW_OUTCOME& CFoulState::GetOutcome() const noexcept
{
	return mOutcome;
}

} // futsim::football namespace
