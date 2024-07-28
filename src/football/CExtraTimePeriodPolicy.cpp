#include "football/CExtraTimePeriodPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPeriodState.h"

namespace futsim::football
{

//! Macro to explicitly instantiate SExtraTimePeriodPlayPolicy struct
#define EXPLICIT_INSTANTIATE_STRUCT_EXTRA_TIME_PERIOD_POLICY(name, ... ) \
	template class CExtraTimePeriodPolicy<E_GOAL_RULE::name>; \

template <E_GOAL_RULE GOAL_RULE>
bool CExtraTimePeriodPolicy<GOAL_RULE>::DoOperator( const period_states& aPeriodStates,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IExtraTimePeriodPolicy::DoOperator( aPeriodStates, aMatchConfiguration );
}

template <>
bool CExtraTimePeriodPolicy<E_GOAL_RULE::SILVER_GOAL>::DoOperator( const period_states& aPeriodStates,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	if( !IExtraTimePeriodPolicy::DoOperator( aPeriodStates, aMatchConfiguration ) )
		return false;

	// We only need to check the goals scored in the last period
	const auto& homeScoredGoals = aPeriodStates.back().CountScoredGoals( true );
	const auto& awayScoredGoals = aPeriodStates.back().CountScoredGoals( false );
	return homeScoredGoals == awayScoredGoals && ( !aMatchConfiguration.GetTieCondition()->GetHomeTeamGoals() || homeScoredGoals == 0 );
}

FOR_EACH_GOAL_RULE( EXPLICIT_INSTANTIATE_STRUCT_EXTRA_TIME_PERIOD_POLICY )

} // futsim::football namespace
