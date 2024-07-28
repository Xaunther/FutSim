#pragma once

#include "football/IExtraTimePeriodPolicy.h"

#include "football/EGoalRule.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor for the periods at extra time.
*/
template <E_GOAL_RULE GOAL_RULE>
class CExtraTimePeriodPolicy : public IExtraTimePeriodPolicy
{
	bool DoOperator( const period_states& aPeriodStates,
		const CMatchConfiguration& aMatchConfiguration ) const override;
};

} // futsim::football namespace