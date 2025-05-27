#include "football/IExtraTimePeriodPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPeriodState.h"
#include "football/IExtraTimePeriodPlayPolicy.h"

namespace futsim::football
{

bool IExtraTimePeriodPolicy::DoOperator(
	const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPeriodStates.size() < aMatchConfiguration.GetExtraTime()->GetPeriodCount();
}

const CMatchConfiguration& IExtraTimePeriodPolicy::CheckMatchConfiguration(
	const CMatchConfiguration& aMatchConfiguration )
{
	return IExtraTimePeriodPlayPolicy::CheckMatchConfiguration( aMatchConfiguration );
}

} // futsim::football namespace
