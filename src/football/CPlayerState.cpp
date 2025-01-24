#include "football/CPlayerState.h"

#include "football/CFoulState.h"

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

CPlayerState CPlayerState::operator+( const CPlayerState& aOther ) const noexcept
{
	return CPlayerState{ *this } += aOther;
}

CPlayerState& CPlayerState::operator+=( const CPlayerState& aOther ) noexcept
{
	mMinutesPlayed += aOther.mMinutesPlayed;
	mSaves += aOther.mSaves;
	mTackles += aOther.mTackles;
	mPasses += aOther.mPasses;
	mShots += aOther.mShots;
	mAssists += aOther.mAssists;
	mGoals += aOther.mGoals;
	mFoulsCommitted += aOther.mFoulsCommitted;
	mYellowCards += aOther.mYellowCards;
	mRedCards += aOther.mRedCards;
	
	return *this;
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

void CPlayerState::AddMinutePlayed() noexcept
{
	++mMinutesPlayed;
}

void CPlayerState::AddFoul( const CFoulState& aFoulState ) noexcept
{
	using types::CFoulDrawConfiguration::E_FOUL_DRAW_OUTCOME;
	++mFoulsCommitted;
	switch( aFoulState.GetOutcome() )
	{
	case E_FOUL_DRAW_OUTCOME::YELLOW_CARD :
		++mYellowCards;
		break;
	case E_FOUL_DRAW_OUTCOME::RED_CARD :
		++mRedCards;
		break;
	case E_FOUL_DRAW_OUTCOME::NO_CARD: default :
		break;
	}
}

void CPlayerState::AddSave() noexcept
{
	++mSaves;
}

void CPlayerState::AddTackle() noexcept
{
	++mTackles;
}

void CPlayerState::AddPass( bool aIsAssist ) noexcept
{
	++mPasses;
	if( aIsAssist )
		++mAssists;
}

} // futsim::football namespace
