#pragma once

#include "football/IPeriodPolicy.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor interface for the periods.
*/
class IExtraTimePeriodPolicy : public IPeriodPolicy
{
protected:
	using period_states = types::CPeriodStates::period_states;

	bool DoOperator( const period_states& aPeriodStates,
		const CMatchConfiguration& aMatchConfiguration ) const override = 0;

public:
	/**
	 * @brief Checks that the match configuration can produce extra time periods.
	 * @param aMatchConfiguration Match configuration.
	*/
	static const CMatchConfiguration& CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration );
};

} // futsim::football namespace
