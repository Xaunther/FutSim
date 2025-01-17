#include "football/CPlayerState.h"

namespace futsim::football
{

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
