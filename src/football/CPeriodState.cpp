#include "football/CPeriodState.h"

#include "JsonUtils.h"

namespace futsim::football
{

const CPeriodState::plays& CPeriodState::GetPlays() const noexcept
{
	return mPlays;
}

void CPeriodState::JSON( json& aJSON ) const noexcept
{
	for( auto& JSONPlays = aJSON[ JSON_PLAYS ]; const auto & play : mPlays )
	{
		json elementJSON;
		AddToJSONKey( elementJSON, play.homeTeam, JSON_HOME_TEAM_PLAY );
		AddToJSON( elementJSON, play.state );
		JSONPlays.push_back( std::move( elementJSON ) );
	}
}

bool CPeriodState::IsHomeTeamAttackNext() const
{
	using enum types::CGoalDrawConfiguration::E_CHANCE_OUTCOME;
	const auto& lastPlay = mPlays.back();
	return ( lastPlay.state.GetChancesStates().empty() ||
		lastPlay.state.GetChancesStates().back().GetChanceOutcome() == KEEP_POSSESSION_FROM_DF ||
		lastPlay.state.GetChancesStates().back().GetChanceOutcome() == KEEP_POSSESSION_FROM_GK ) ? lastPlay.homeTeam : !lastPlay.homeTeam;
}

} // futsim::football namespace