#include "football/SPeriodPlayPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPlayState.h"

namespace futsim::football
{

bool SPeriodPlayPolicy::operator()( const plays& aPlays,
	const CMatchConfiguration& aMatchConfiguration ) const
{
	return IPeriodPlayPolicy::operator()( aPlays, aMatchConfiguration );
}

} // futsim::football namespace
