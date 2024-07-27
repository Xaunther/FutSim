#include "football/SPeriodPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPeriodState.h"

namespace futsim::football
{

bool SPeriodPolicy::operator()( const period_states& aPeriodStates,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IPeriodPolicy::operator()( aPeriodStates, aMatchConfiguration );
}

} // futsim::football namespace
