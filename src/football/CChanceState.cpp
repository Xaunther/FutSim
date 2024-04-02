#include "football/CChanceState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CChanceState::JSON( json& aJSON ) const noexcept
{
	std::visit( [ &aJSON ]( auto&& aChanceType ) { AddToJSONKey( aJSON, aChanceType, JSON_CHANCE_TYPE ); }, mChanceType );
	AddToJSONKey( aJSON, mOutcome, JSON_OUTCOME );
	if( mStopper )
		AddToJSONKey( aJSON, *mStopper, JSON_STOPPER );
	if( mTackler )
		AddToJSONKey( aJSON, *mTackler, JSON_TACKLER );
	if( mPasser )
		AddToJSONKey( aJSON, *mPasser, JSON_PASSER );
	if( mShooter )
		AddToJSONKey( aJSON, *mShooter, JSON_SHOOTER );
}

const CChanceState::chance_type& CChanceState::GetChanceType() const noexcept
{
	return mChanceType;
}

const CChanceState::E_CHANCE_OUTCOME& CChanceState::GetChanceOutcome() const noexcept
{
	return mOutcome;
}

template <E_PLAYER_SKILL tPlayerSkill> const CChanceState::optional_name& CChanceState::GetActor() const noexcept
{
	return tPlayerSkill == E_PLAYER_SKILL::St ? mStopper :
		tPlayerSkill == E_PLAYER_SKILL::Tk ? mTackler :
		tPlayerSkill == E_PLAYER_SKILL::Ps ? mPasser :
		mShooter;
}

template <E_PLAYER_SKILL tPlayerSkill> CChanceState::optional_name& CChanceState::Actor() const noexcept
{
	return const_cast< optional_name& >( GetActor<tPlayerSkill>() );
}

template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::St>() const noexcept;
template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::Tk>() const noexcept;
template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::Ps>() const noexcept;
template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::Sh>() const noexcept;

} // futsim::football namespace