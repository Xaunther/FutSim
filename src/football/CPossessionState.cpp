#include "football/CPossessionState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CPossessionState::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mOutcome, JSON_OUTCOME );
	if( mTackler )
		AddToJSONKey( aJSON, *mTackler, JSON_TACKLER );
	if( mPasser )
		AddToJSONKey( aJSON, *mPasser, JSON_PASSER );
}

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