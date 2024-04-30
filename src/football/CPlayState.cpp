#include "football/CPlayState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CPlayState::JSON( json& aJSON ) const noexcept
{

	AddToJSON( aJSON, mPossessionState );
	if( mFoulState )
		AddToJSON( aJSON, *mFoulState );
	if( !mChancesStates.empty() )
		AddArrayToJSONKey( aJSON, mChancesStates, JSON_CHANCES );
}

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
