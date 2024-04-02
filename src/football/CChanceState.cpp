#include "football/CChanceState.h"

namespace futsim::football
{

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