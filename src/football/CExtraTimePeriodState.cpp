#include "football/CExtraTimePeriodState.h"

namespace futsim::football
{

bool CExtraTimePeriodState::SDefaultPeriodPlayPolicy::operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPlays.size() < aMatchConfiguration.GetExtraTime()->GetPeriodTime();
}

bool CExtraTimePeriodState::HasGoalBeenScoredLast() const
{
	using enum types::CGoalDrawConfiguration::E_CHANCE_OUTCOME;
	const auto& lastPlay = GetPlays().back();
	return !lastPlay.state.GetChancesStates().empty() && lastPlay.state.GetChancesStates().back().GetChanceOutcome() == GOAL;
}

const CMatchConfiguration& CExtraTimePeriodState::CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration )
{
	if( !aMatchConfiguration.GetExtraTime() )
		throw std::invalid_argument{ "The match configuration cannot configure an extra time period state." };
	return aMatchConfiguration;
}

} // futsim::football namespace