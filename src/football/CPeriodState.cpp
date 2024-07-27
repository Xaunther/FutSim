#include "football/CPeriodState.h"

#include "JsonUtils.h"

namespace futsim::football
{

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

const CPeriodState::plays& CPeriodState::GetPlays() const noexcept
{
	return mPlays;
}

CPeriodState::goal_count CPeriodState::CountScoredGoals( const bool aHomeTeam ) const noexcept
{
	return static_cast<goal_count>( std::ranges::count_if( mPlays, [ &aHomeTeam ]( const auto& aPlay )
	{
		return aPlay.homeTeam == aHomeTeam && aPlay.state.IsGoalScored();
	} ) );
}

void CPeriodState::PushPlayState( CPlayState&& aPlayState, const bool aHomeTeamAttack ) noexcept
{
	auto homeTeamPlay = aPlayState.GetPossessionState().GetOutcome() == types::CPossessionDrawConfiguration::E_POSSESSION_DRAW_OUTCOME::COUNTER_ATTACK ?
		!aHomeTeamAttack : aHomeTeamAttack;
	mPlays.emplace_back( homeTeamPlay, std::move( aPlayState ) );
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