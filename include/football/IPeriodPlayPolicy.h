#pragma once

#include "football/types/CPeriodState.h"

namespace futsim::football
{

class CMatchConfiguration;

/**
 * @brief Functor interface for the plays of the period.
*/
class IPeriodPlayPolicy
{
protected:
	using plays = types::CPeriodState::plays;

public:
	/**
	 * @copydoc DoOperator
	*/
	bool operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const;

protected:
	/**
	 * @brief Returns whether another minute must be played.
	 * @param aPlays Plays of the period.
	 * @param aMatchConfiguration Match configuration.
	*/
	virtual bool DoOperator( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const = 0;
};

} // futsim::football namespace