#include "football/CExtraTimePeriodPlayPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPlayState.h"

namespace futsim::football
{

//! Macro to explicitly instantiate CExtraTimePeriodPlayPolicy struct
#define EXPLICIT_INSTANTIATE_STRUCT_EXTRA_TIME_PERIOD_PLAY_POLICY(name, ... ) \
	template class CExtraTimePeriodPlayPolicy<E_GOAL_RULE::name>; \

template <E_GOAL_RULE GOAL_RULE>
bool CExtraTimePeriodPlayPolicy<GOAL_RULE>::DoOperator( const plays& aPlays,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IExtraTimePeriodPlayPolicy::DoOperator( aPlays, aMatchConfiguration );
}

template <>
bool CExtraTimePeriodPlayPolicy<E_GOAL_RULE::GOLDEN_GOAL>::DoOperator( const plays& aPlays,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IExtraTimePeriodPlayPolicy::DoOperator( aPlays, aMatchConfiguration ) &&
		!aPlays.back().state.IsGoalScored();
}

FOR_EACH_GOAL_RULE( EXPLICIT_INSTANTIATE_STRUCT_EXTRA_TIME_PERIOD_PLAY_POLICY )

} // futsim::football namespace
