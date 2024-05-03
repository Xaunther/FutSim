#include "football/CPenaltyState.h"

namespace futsim::football
{

const futsim::types::CPerson::name_type& CPenaltyState::GetGoalkeeper() const noexcept
{
	return *GetActor<E_PLAYER_SKILL::St>();
}

const futsim::types::CPerson::name_type& CPenaltyState::GetShooter() const noexcept
{
	return *GetActor<E_PLAYER_SKILL::Sh>();
}

const CChanceState::E_CHANCE_OUTCOME& CPenaltyState::GetChanceOutcome() const noexcept
{
	return CChanceState::GetChanceOutcome();
}

} // futsim::football namespace