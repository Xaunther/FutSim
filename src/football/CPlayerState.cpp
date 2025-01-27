#include "football/CPlayerState.h"

#include "football/CFoulState.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

CPlayerState::CPlayerState( const json& aJSON ) try :
	mMinutesPlayed( ValueFromOptionalJSONKey<counter>( aJSON, MINUTES_PLAYED_KEY ) ),
	mSaves( ValueFromOptionalJSONKey<counter>( aJSON, SAVES_KEY ) ),
	mTackles( ValueFromOptionalJSONKey<counter>( aJSON, TACKLES_KEY ) ),
	mPasses( ValueFromOptionalJSONKey<counter>( aJSON, PASSES_KEY ) ),
	mShots( ValueFromOptionalJSONKey<counter>( aJSON, SHOTS_KEY ) ),
	mAssists( ValueFromOptionalJSONKey<counter>( aJSON, ASSISTS_KEY ) ),
	mGoals( ValueFromOptionalJSONKey<counter>( aJSON, GOALS_KEY ) ),
	mFoulsCommitted( ValueFromOptionalJSONKey<counter>( aJSON, FOULS_COMMITTED ) ),
	mYellowCards( ValueFromOptionalJSONKey<counter>( aJSON, YELLOW_CARDS_KEY ) ),
	mRedCards( ValueFromOptionalJSONKey<counter>( aJSON, RED_CARDS_KEY ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player state from JSON." )

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

CPlayerState::operator bool() const noexcept
{
	return mMinutesPlayed != 0;
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

CPlayerState& CPlayerState::AddMinutePlayed() noexcept
{
	++mMinutesPlayed;
	return *this;
}

CPlayerState& CPlayerState::AddFoul( const CFoulState& aFoulState ) noexcept
{
	using types::CFoulDrawConfiguration::E_FOUL_DRAW_OUTCOME;
	++mFoulsCommitted;
	switch( aFoulState.GetOutcome() )
	{
	case E_FOUL_DRAW_OUTCOME::YELLOW_CARD :
		++mYellowCards;
		return *this;
	case E_FOUL_DRAW_OUTCOME::RED_CARD :
		++mRedCards;
		return *this;
	case E_FOUL_DRAW_OUTCOME::NO_CARD: default :
		return *this;
	}
}

CPlayerState& CPlayerState::AddSave() noexcept
{
	++mSaves;
	return *this;
}

CPlayerState& CPlayerState::AddTackle() noexcept
{
	++mTackles;
	return *this;
}

CPlayerState& CPlayerState::AddPass( bool aIsAssist ) noexcept
{
	++mPasses;
	if( aIsAssist )
		++mAssists;
	return *this;
}

CPlayerState& CPlayerState::AddShot( bool aIsGoal ) noexcept
{
	++mShots;
	if( aIsGoal )
		++mGoals;
	return *this;
}

} // futsim::football namespace
