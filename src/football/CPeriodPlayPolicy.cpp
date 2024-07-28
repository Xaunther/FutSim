#include "football/CPeriodPlayPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPlayState.h"

namespace futsim::football
{

bool CPeriodPlayPolicy::DoOperator( const plays& aPlays,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IPeriodPlayPolicy::DoOperator( aPlays, aMatchConfiguration );
}

} // futsim::football namespace
