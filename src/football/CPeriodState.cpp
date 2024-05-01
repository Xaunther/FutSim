#include "football/CPeriodState.h"

namespace futsim::football
{

const CPeriodState::plays& CPeriodState::GetPlays() const noexcept
{
	return mPlays;
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