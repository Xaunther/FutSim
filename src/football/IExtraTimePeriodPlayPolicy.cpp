#include "football/IExtraTimePeriodPlayPolicy.h"

#include "football/CMatchConfiguration.h"
#include "football/CPlayState.h"

namespace futsim::football
{

bool IExtraTimePeriodPlayPolicy::operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPlays.size() < aMatchConfiguration.GetExtraTime()->GetPeriodTime();
}

const CMatchConfiguration& IExtraTimePeriodPlayPolicy::CheckMatchConfiguration(
	const CMatchConfiguration& aMatchConfiguration )
{
	if( !aMatchConfiguration.GetExtraTime() )
		throw std::invalid_argument{ "The match configuration cannot be used for the default extra time period play policy." };
	return aMatchConfiguration;
}

} // futsim::football namespace