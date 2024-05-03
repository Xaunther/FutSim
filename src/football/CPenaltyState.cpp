#include "football/CPenaltyState.h"

#include "JsonUtils.h"

namespace futsim::football
{

void CPenaltyState::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, GetChanceOutcome(), JSON_OUTCOME );
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

const CChanceState::E_CHANCE_OUTCOME& CPenaltyState::GetChanceOutcome() const noexcept
{
	return CChanceState::GetChanceOutcome();
}

void CPenaltyState::ToJSON( json& aJSON ) const noexcept
{
	CChanceState::ToJSON( aJSON );
}

} // futsim::football namespace