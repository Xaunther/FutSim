#include "football/CExtraTimePeriodStates.h"

namespace futsim::football
{

bool CExtraTimePeriodStates::SDefaultPeriodPolicy::operator()(
	const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPeriodStates.size() < aMatchConfiguration.GetExtraTime()->GetPeriodCount();
}

bool CExtraTimePeriodStates::SSilverGoalPeriodPolicy::operator()(
	const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const
{
	if( !SDefaultPeriodPolicy::operator()( aPeriodStates, aMatchConfiguration ) )
		return false;

	// We only need to check the goals scored in the last period
	const auto& homeScoredGoals = aPeriodStates.back().CountScoredGoals( true );
	const auto& awayScoredGoals = aPeriodStates.back().CountScoredGoals( false );
	return homeScoredGoals == awayScoredGoals && ( !aMatchConfiguration.GetTieCondition()->GetHomeTeamGoals() || homeScoredGoals == 0 );
}

} // futsim::football namespace