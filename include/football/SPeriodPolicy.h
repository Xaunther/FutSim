#pragma once

#include "football/IPeriodPolicy.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor for the periods.
*/
struct SPeriodPolicy : public IPeriodPolicy
{
	bool operator()( const period_states& aPeriodStates,
		const CMatchConfiguration& aMatchConfiguration ) const override;
};

} // futsim::football namespace