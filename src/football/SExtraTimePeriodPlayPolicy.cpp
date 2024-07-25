#include "football/SExtraTimePeriodPlayPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPlayState.h"

namespace futsim::football
{

//! Macro to explicitly instantiate SExtraTimePeriodPlayPolicy struct
#define EXPLICIT_INSTANTIATE_STRUCT_EXTRA_TIME_PERIOD_PLAY_POLICY(name, ... ) \
	template struct SExtraTimePeriodPlayPolicy<E_GOAL_RULE::name>; \

template <E_GOAL_RULE GOAL_RULE>
bool SExtraTimePeriodPlayPolicy<GOAL_RULE>::operator()( const plays& aPlays,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IExtraTimePeriodPlayPolicy::operator()( aPlays, aMatchConfiguration );
}

template <>
bool SExtraTimePeriodPlayPolicy<E_GOAL_RULE::GOLDEN_GOAL>::operator()( const plays& aPlays,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IExtraTimePeriodPlayPolicy::operator()( aPlays, aMatchConfiguration ) &&
		!aPlays.back().state.IsGoalScored();
}

FOR_EACH_GOAL_RULE( EXPLICIT_INSTANTIATE_STRUCT_EXTRA_TIME_PERIOD_PLAY_POLICY )

} // futsim::football namespace
