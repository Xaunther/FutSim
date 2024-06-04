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

	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aHomeTeamStrategy Current match strategy for the home team.
	 * @param aAwayTeamStrategy Current match strategy for the away team.
	 * @param aGenerator RNG to use.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	explicit CExtraTimePeriodStates(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		std::uniform_random_bit_generator auto& aGenerator
	);

	/**
	 * @brief Checks that the match configuration can produce extra time periods.
	 * @param aMatchConfiguration Match configuration.
	*/
	static const CMatchConfiguration& CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration );
};

CExtraTimePeriodStates::CExtraTimePeriodStates(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aHomeTeamStrategy,
	const CTeamStrategy& aAwayTeamStrategy,
	std::uniform_random_bit_generator auto& aGenerator
) try :
	CPeriodStates( aMatchConfiguration.GetExtraTime()->GetGoalRule() == E_GOAL_RULE::SILVER_GOAL ?
		CPeriodStates{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy, aGenerator, SSilverGoalPeriodPolicy{} } :
		CPeriodStates{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy, aGenerator, SDefaultPeriodPolicy{} } )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the extra time period states." )

} // futsim::football namespace