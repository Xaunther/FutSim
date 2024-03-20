#include "football/CFoulState.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

void CFoulState::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mCommitter, JSON_COMMIITER );
	AddToJSONKey( aJSON, mOutcome, JSON_OUTCOME );
}

std::string_view CFoulState::GetCommitter() const noexcept
{
	return mCommitter;
}

const CFoulDrawConfigurationTypes::E_FOUL_DRAW_OUTCOME& CFoulState::GetOutcome() const noexcept
{
	return mOutcome;
}

} // futsim::football namespace