#pragma once

#include "football/CPeriodStates.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a series of extra time periods.
 * @details The periods have the same play policy and alternate the team that kicks off.
*/
class CExtraTimePeriodStates : public CPeriodStates
{
public:
	/**
	 * @brief Default policy functor for the periods of extra time.
	 * @details All configured periods are played.
	*/
	struct SDefaultPeriodPolicy
	{
		/**
		 * @brief Returns whether another period must be played.
		 * @param aPeriodStates Current period states.
		 * @param aMatchConfiguration Match configuration.
		*/
		bool operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const;
	};

	/**
	 * @brief Default policy functor for the periods of extra time with silver goal.
	 * @details No more periods are played when the tie condition is no longer satisfied after a period.
	*/
	struct SSilverGoalPeriodPolicy : public SDefaultPeriodPolicy
	{
		/**
		 * @brief Returns whether another period must be played.
		 * @param aPeriodStates Current period states.
		 * @param aMatchConfiguration Match configuration.
		*/
		bool operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const;
	};
};

} // futsim::football namespace