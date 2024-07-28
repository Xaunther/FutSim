#pragma once

#include "football/IPeriodPolicy.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor for the periods.
*/
class CPeriodPolicy : public IPeriodPolicy
{
	bool DoOperator( const period_states& aPeriodStates,
		const CMatchConfiguration& aMatchConfiguration ) const override;
};

} // futsim::football namespace