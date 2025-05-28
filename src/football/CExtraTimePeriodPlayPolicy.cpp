#include "football/CExtraTimePeriodPlayPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPlayState.h"

namespace futsim::football
{

template <typename GOAL_RULE>
bool CExtraTimePeriodPlayPolicy<GOAL_RULE>::DoOperator( const plays& aPlays,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IExtraTimePeriodPlayPolicy::DoOperator( aPlays, aMatchConfiguration );
}

template <>
bool CExtraTimePeriodPlayPolicy<CGoalRule::GOLDEN_GOAL>::DoOperator( const plays& aPlays,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IExtraTimePeriodPlayPolicy::DoOperator( aPlays, aMatchConfiguration ) &&
		!aPlays.back().state.IsGoalScored();
}

template class CExtraTimePeriodPlayPolicy<CGoalRule ::NO>;
template class CExtraTimePeriodPlayPolicy<CGoalRule ::SILVER_GOAL>;
template class CExtraTimePeriodPlayPolicy<CGoalRule ::GOLDEN_GOAL>;

} // futsim::football namespace
