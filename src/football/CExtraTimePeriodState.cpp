#include "football/CExtraTimePeriodState.h"

namespace futsim::football
{

bool CExtraTimePeriodState::SDefaultPeriodPlayPolicy::operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPlays.size() < aMatchConfiguration.GetExtraTime()->GetPeriodTime();
}

bool CExtraTimePeriodState::SGoldenGoalPeriodPlayPolicy::operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	using enum types::CGoalDrawConfiguration::E_CHANCE_OUTCOME;
	return SDefaultPeriodPlayPolicy::operator()( aPlays, aMatchConfiguration )
		&& ( aPlays.back().state.GetChancesStates().empty() || aPlays.back().state.GetChancesStates().back().GetChanceOutcome() != GOAL );
}

void CExtraTimePeriodState::JSON( json& aJSON ) const noexcept
{
	CPeriodState::JSON( aJSON );
}

const CMatchConfiguration& CExtraTimePeriodState::CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration )
{
	if( !aMatchConfiguration.GetExtraTime() )
		throw std::invalid_argument{ "The match configuration cannot configure an extra time period state." };
	return aMatchConfiguration;
}

} // futsim::football namespace