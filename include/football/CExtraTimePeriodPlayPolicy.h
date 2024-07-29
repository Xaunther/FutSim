#pragma once

#include "football/IExtraTimePeriodPlayPolicy.h"

#include "football/EGoalRule.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor for the plays of an extra time period.
*/
template <E_GOAL_RULE GOAL_RULE>
class CExtraTimePeriodPlayPolicy : public IExtraTimePeriodPlayPolicy
{
	bool DoOperator( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const override;
};

} // futsim::football namespace