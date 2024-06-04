#include "football/CPeriodState.h"

#include "JsonUtils.h"

namespace futsim::football
{

bool CPeriodState::SDefaultPeriodPlayPolicy::operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPlays.size() < aMatchConfiguration.GetPlayTime().GetPeriodTime();
}

bool CPeriodState::SDefaultExtraTimePeriodPlayPolicy::operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPlays.size() < aMatchConfiguration.GetExtraTime()->GetPeriodTime();
}

const CMatchConfiguration& CPeriodState::SDefaultExtraTimePeriodPlayPolicy::CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration )
{
	if( !aMatchConfiguration.GetExtraTime() )
		throw std::invalid_argument{ "The match configuration cannot be used for the default extra time period play policy." };
	return aMatchConfiguration;
}

bool CPeriodState::SGoldenGoalPeriodPlayPolicy::operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	return SDefaultExtraTimePeriodPlayPolicy::operator()( aPlays, aMatchConfiguration ) && !aPlays.back().state.IsGoalScored();
}

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