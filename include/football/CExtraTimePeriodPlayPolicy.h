#pragma once

#include "football/IExtraTimePeriodPlayPolicy.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor for the plays of an extra time period.
*/
template <typename GOAL_RULE>
class CExtraTimePeriodPlayPolicy : public IExtraTimePeriodPlayPolicy
{
	bool DoOperator( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const override;
};

} // futsim::football namespace
