#pragma once

#include "football/IPeriodPlayPolicy.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor for the plays of a period.
*/
struct SPeriodPlayPolicy : public IPeriodPlayPolicy
{
	bool operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const override;
};

} // futsim::football namespace