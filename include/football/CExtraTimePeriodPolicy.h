#pragma once

#include "football/IExtraTimePeriodPolicy.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor for the periods at extra time.
*/
template <typename GOAL_RULE>
class CExtraTimePeriodPolicy : public IExtraTimePeriodPolicy
{
	bool DoOperator( const period_states& aPeriodStates,
		const CMatchConfiguration& aMatchConfiguration ) const override;
};

} // futsim::football namespace
