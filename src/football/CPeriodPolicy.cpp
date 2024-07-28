#include "football/CPeriodPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPeriodState.h"

namespace futsim::football
{

bool CPeriodPolicy::DoOperator( const period_states& aPeriodStates,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IPeriodPolicy::DoOperator( aPeriodStates, aMatchConfiguration );
}

} // futsim::football namespace
