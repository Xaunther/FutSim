#include "football/IPeriodPlayPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPlayState.h"

namespace futsim::football
{

bool IPeriodPlayPolicy::operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	return DoOperator( aPlays, aMatchConfiguration );
}

bool IPeriodPlayPolicy::DoOperator( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPlays.size() < aMatchConfiguration.GetPlayTime().GetPeriodTime();
}

} // futsim::football namespace
