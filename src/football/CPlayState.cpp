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
		AddArrayToJSONKey( aJSON, mChancesStates, json_traits<CPlayState>::CHANCES );
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

bool CPlayState::IsGoalScored() const noexcept
{
	using enum types::CGoalDrawConfiguration::E_CHANCE_OUTCOME;
	return !mChancesStates.empty() && mChancesStates.back().GetChanceOutcome() == GOAL;
}

} // futsim::football namespace
