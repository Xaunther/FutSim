#include "football/CPossessionState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CPossessionState::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mOutcome, OUTCOME_KEY );
	if( mTackler )
		AddToJSONKey( aJSON, *mTackler, TACKLER_KEY );
	if( mPasser )
		AddToJSONKey( aJSON, *mPasser, PASSER_KEY );
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
