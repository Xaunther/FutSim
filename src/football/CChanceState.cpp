#include "football/CChanceState.h"

#include "JsonUtils.h"

namespace futsim::football
{

//! Macro to explicitly instantiate GetActor method.
#define EXPLICIT_INSTANTIATE_GET_ACTOR(name, ... ) \
	template const CChanceState::optional_name& CChanceState::GetActor<E_PLAYER_SKILL::name>() const noexcept; \

//! Macro to explicitly instantiate Actor method.
#define EXPLICIT_INSTANTIATE_ACTOR(name, ... ) \
	template CChanceState::optional_name& CChanceState::Actor<E_PLAYER_SKILL::name>() noexcept; \

//! Macro to explicitly instantiate JSONActor method.
#define EXPLICIT_INSTANTIATE_JSON_ACTOR(name, ... ) \
	template void CChanceState::JSONActor<E_PLAYER_SKILL::name>( json& ) const noexcept; \

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
	if constexpr( tPlayerSkill == E_PLAYER_SKILL::St )
		return mStopper;
	else if constexpr( tPlayerSkill == E_PLAYER_SKILL::Tk )
		return mTackler;
	else if constexpr( tPlayerSkill == E_PLAYER_SKILL::Ps )
		return mPasser;
	else if constexpr( tPlayerSkill == E_PLAYER_SKILL::Sh )
		return mShooter;
	else
	{
		static optional_name EMPTY;
		return EMPTY;
	}
}
FOR_EACH_PLAYER_SKILL( EXPLICIT_INSTANTIATE_GET_ACTOR )

template <E_PLAYER_SKILL tPlayerSkill> CChanceState::optional_name& CChanceState::Actor() noexcept
{
	return const_cast< optional_name& >( GetActor<tPlayerSkill>() );
}
FOR_EACH_PLAYER_SKILL( EXPLICIT_INSTANTIATE_ACTOR )

template <E_PLAYER_SKILL tPlayerSkill> void CChanceState::JSONActor( json& aJSON ) const noexcept
{
	if( const auto& actor = GetActor<tPlayerSkill>() )
		AddToJSONKey( aJSON, *actor, JSON_ACTOR<tPlayerSkill> );
}
FOR_EACH_PLAYER_SKILL( EXPLICIT_INSTANTIATE_JSON_ACTOR )

} // futsim::football namespace