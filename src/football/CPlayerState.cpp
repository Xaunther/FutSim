#include "football/CPlayerState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CPlayerState::JSON( json& aJSON ) const noexcept
{
	AddToOptionalJSONKey( aJSON, mMinutesPlayed, MINUTES_PLAYED_KEY );
	AddToOptionalJSONKey( aJSON, mSaves, SAVES_KEY );
	AddToOptionalJSONKey( aJSON, mTackles, TACKLES_KEY );
	AddToOptionalJSONKey( aJSON, mPasses, PASSES_KEY );
	AddToOptionalJSONKey( aJSON, mShots, SHOTS_KEY );
	AddToOptionalJSONKey( aJSON, mAssists, ASSISTS_KEY );
	AddToOptionalJSONKey( aJSON, mGoals, GOALS_KEY );
	AddToOptionalJSONKey( aJSON, mFoulsCommitted, FOULS_COMMITTED );
	AddToOptionalJSONKey( aJSON, mYellowCards, YELLOW_CARDS_KEY );
	AddToOptionalJSONKey( aJSON, mRedCards, RED_CARDS_KEY );
}

const CPlayerState::counter& CPlayerState::GetMinutesPlayed() const noexcept
{
	return mMinutesPlayed;
}

const CPlayerState::counter& CPlayerState::GetSaves() const noexcept
{
	return mSaves;
}

const CPlayerState::counter& CPlayerState::GetTackles() const noexcept
{
	return mTackles;
}

const CPlayerState::counter& CPlayerState::GetPasses() const noexcept
{
	return mPasses;
}

const CPlayerState::counter& CPlayerState::GetShots() const noexcept
{
	return mShots;
}

const CPlayerState::counter& CPlayerState::GetAssists() const noexcept
{
	return mAssists;
}

const CPlayerState::counter& CPlayerState::GetGoals() const noexcept
{
	return mGoals;
}

const CPlayerState::counter& CPlayerState::GetFoulsCommitted() const noexcept
{
	return mFoulsCommitted;
}

const CPlayerState::counter& CPlayerState::GetYellowCards() const noexcept
{
	return mYellowCards;
}

const CPlayerState::counter& CPlayerState::GetRedCards() const noexcept
{
	return mRedCards;
}

} // futsim::football namespace
