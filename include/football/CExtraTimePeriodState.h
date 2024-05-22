#pragma once

#include "IJsonable.h"

#include "football/CPeriodState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of an extra time match period.
*/
class CExtraTimePeriodState : public CPeriodState
{
public:
	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aHomeTeamStrategy Current match strategy for the home team.
	 * @param aAwayTeamStrategy Current match strategy for the away team.
	 * @param aHomeTeamAttack Whether the home team is attacking.
	 * @param aGenerator RNG to use.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	explicit CExtraTimePeriodState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator
	);
};

} // futsim::football namespace