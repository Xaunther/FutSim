#include "football/CPenaltyState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CPenaltyState::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, GetChanceOutcome(), OUTCOME_KEY );
	JSONActor<E_PLAYER_SKILL::St>( aJSON );
	JSONActor<E_PLAYER_SKILL::Sh>( aJSON );
}

const futsim::types::CPerson::name_type& CPenaltyState::GetGoalkeeper() const noexcept
{
	return *GetActor<E_PLAYER_SKILL::St>();
}

const futsim::types::CPerson::name_type& CPenaltyState::GetShooter() const noexcept
{
	return *GetActor<E_PLAYER_SKILL::Sh>();
}

} // futsim::football namespace
