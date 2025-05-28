#include "football/CExtraTimePeriodPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPeriodState.h"

namespace futsim::football
{

template <typename GOAL_RULE>
bool CExtraTimePeriodPolicy<GOAL_RULE>::DoOperator( const period_states& aPeriodStates,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IExtraTimePeriodPolicy::DoOperator( aPeriodStates, aMatchConfiguration );
}

template <>
bool CExtraTimePeriodPolicy<CGoalRule::SILVER_GOAL>::DoOperator( const period_states& aPeriodStates,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	if( !IExtraTimePeriodPolicy::DoOperator( aPeriodStates, aMatchConfiguration ) )
		return false;

	// We only need to check the goals scored in the last period
	const auto score = aPeriodStates.back().CountScore();
	return score.home == score.away && ( !aMatchConfiguration.GetTieCondition()->GetHomeTeamGoals() || score.home == 0 );
}

template class CExtraTimePeriodPolicy<CGoalRule ::NO>;
template class CExtraTimePeriodPolicy<CGoalRule ::SILVER_GOAL>;
template class CExtraTimePeriodPolicy<CGoalRule ::GOLDEN_GOAL>;

} // futsim::football namespace
