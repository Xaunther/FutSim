#include "football/CChanceState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CChanceState::JSON( json& aJSON ) const noexcept
{
	std::visit( [ &aJSON ]( auto&& aChanceType ) { AddToJSONKey( aJSON, aChanceType, JSON_CHANCE_TYPE ); }, mChanceType );
	AddToJSONKey( aJSON, mOutcome, JSON_OUTCOME );
	JSONActor<E_PLAYER_SKILL::St>( aJSON );
	JSONActor<E_PLAYER_SKILL::Tk>( aJSON );
	JSONActor<E_PLAYER_SKILL::Ps>( aJSON );
	JSONActor<E_PLAYER_SKILL::Sh>( aJSON );
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

template const CChanceState::optional_name& CChanceState::GetActor<E_PLAYER_SKILL::St>() const noexcept;
template const CChanceState::optional_name& CChanceState::GetActor<E_PLAYER_SKILL::Tk>() const noexcept;
template const CChanceState::optional_name& CChanceState::GetActor<E_PLAYER_SKILL::Ps>() const noexcept;
template const CChanceState::optional_name& CChanceState::GetActor<E_PLAYER_SKILL::Sh>() const noexcept;

template <E_PLAYER_SKILL tPlayerSkill> CChanceState::optional_name& CChanceState::Actor() noexcept
{
	return const_cast< optional_name& >( GetActor<tPlayerSkill>() );
}

template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::St>() noexcept;
template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::Tk>() noexcept;
template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::Ps>() noexcept;
template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::Sh>() noexcept;

template <E_PLAYER_SKILL tPlayerSkill> void CChanceState::JSONActor( json& aJSON ) const noexcept
{
	if( const auto& actor = GetActor<tPlayerSkill>() )
		AddToJSONKey( aJSON, *actor, JSON_ACTOR<tPlayerSkill> );
}

template void CChanceState::JSONActor<E_PLAYER_SKILL::St>( json& aJSON ) const noexcept;
template void CChanceState::JSONActor<E_PLAYER_SKILL::Tk>( json& aJSON ) const noexcept;
template void CChanceState::JSONActor<E_PLAYER_SKILL::Ps>( json& aJSON ) const noexcept;
template void CChanceState::JSONActor<E_PLAYER_SKILL::Sh>( json& aJSON ) const noexcept;

} // futsim::football namespace