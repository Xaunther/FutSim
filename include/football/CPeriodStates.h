#pragma once

#include "IJsonable.h"

#include "football/types/CPeriodStates.h"

#include "football/CPeriodState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of series of match periods.
 * @details The periods have the same play policy and alternate the team that kicks off.
*/
class CPeriodStates : public IJsonable
{
protected:
	using period_states = types::CPeriodStates::period_states;

public:
	/**
	 * @brief Default policy functor for the periods.
	 * @details All configured periods are played.
	*/
	//! 
	struct SDefaultPeriodPolicy
	{
		/**
		 * @brief Returns whether another period must be played.
		 * @param aPeriodStates Current period states.
		 * @param aMatchConfiguration Match configuration.
		*/
		bool operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const;
	};

	//! Retrieves the \copybrief mStates
	const period_states& GetStates() const noexcept;

private:
	//! Period states.
	period_states mStates;
};

} // futsim::football namespace