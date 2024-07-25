#pragma once

#include "football/IPeriodPlayPolicy.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor interface for the plays of the extra time period.
*/
class IExtraTimePeriodPlayPolicy : public IPeriodPlayPolicy
{
public:
	virtual bool operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const override = 0;

	/**
	 * @brief Checks that the match configuration can be used in the policy.
	 * @param aMatchConfiguration Match configuration.
	*/
	static const CMatchConfiguration& CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration );
};

} // futsim::football namespace