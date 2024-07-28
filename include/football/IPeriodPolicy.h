#pragma once

#include "football/types/CPeriodStates.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor interface for the periods.
*/
class IPeriodPolicy
{
protected:
	using period_states = types::CPeriodStates::period_states;

public:
	/**
	 * @copydoc DoOperator
	*/
	bool operator()( const period_states& aPeriodStates,
		const CMatchConfiguration& aMatchConfiguration ) const;

protected:
	/**
	 * @brief Returns whether another period must be played.
	 * @param aPeriodStates Current period states.
	 * @param aMatchConfiguration Match configuration.
	*/
	virtual bool DoOperator( const period_states& aPeriodStates,
		const CMatchConfiguration& aMatchConfiguration ) const = 0;
};

} // futsim::football namespace