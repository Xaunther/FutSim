#include "football/IPeriodPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPeriodState.h"

namespace futsim::football
{

bool IPeriodPolicy::operator()( const period_states& aPeriodStates,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return DoOperator( aPeriodStates, aMatchConfiguration );
}

bool IPeriodPolicy::DoOperator( const period_states& aPeriodStates,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPeriodStates.size() < aMatchConfiguration.GetPlayTime().GetPeriodCount();
}

} // futsim::football namespace
