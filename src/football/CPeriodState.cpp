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
	for( auto& JSONPlays = aJSON[ JSON_PLAYS ]; const auto & playPair : mPlays )
	{
		json elementJSON;
		AddToJSONKey( elementJSON, playPair.first, JSON_HOME_TEAM_PLAY );
		AddToJSON( elementJSON, playPair.second );
		JSONPlays.push_back( std::move( elementJSON ) );
	}
}

bool CPeriodState::IsHomeTeamAttackNext() const
{
	using enum types::CGoalDrawConfiguration::E_CHANCE_OUTCOME;
	const auto& lastPlay = mPlays.back();
	return ( lastPlay.second.GetChancesStates().empty() ||
		lastPlay.second.GetChancesStates().back().GetChanceOutcome() == KEEP_POSSESSION_FROM_DF ||
		lastPlay.second.GetChancesStates().back().GetChanceOutcome() == KEEP_POSSESSION_FROM_GK ) ? lastPlay.first : !lastPlay.first;
}

} // futsim::football namespace