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
	 * @pre The match configuration must pass \ref CheckMatchConfiguration
	*/
	explicit CExtraTimePeriodState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator
	);

	/**
	 * @brief Returns whether a goal has been scored in the last play.
	 * @pre At least one play must have been occurred.
	*/
	bool HasGoalBeenScoredLast() const;

	/**
	 * @brief Checks that the match configuration can produce an extra time period.
	 * @param aMatchConfiguration Match configuration.
	*/
	static const CMatchConfiguration& CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration );
};

CExtraTimePeriodState::CExtraTimePeriodState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aHomeTeamStrategy,
	const CTeamStrategy& aAwayTeamStrategy,
	bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
) try :
	CPeriodState( aMatchConfiguration.GetExtraTime()->GetPeriodTime() )
{
	const auto& extraTime = *aMatchConfiguration.GetExtraTime();
	do
	{
		if( aHomeTeamAttack )
			PushPlayState( CPlayState{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy,
				aHomeTeamAttack, aGenerator }, aHomeTeamAttack );
		else
			PushPlayState( CPlayState{ aMatch, aMatchConfiguration, aAwayTeamStrategy, aHomeTeamStrategy,
				aHomeTeamAttack, aGenerator }, aHomeTeamAttack );
		aHomeTeamAttack = IsHomeTeamAttackNext();
	} while( GetPlays().size() < extraTime.GetPeriodTime() && ( extraTime.GetGoalRule() != E_GOAL_RULE::GOLDEN_GOAL || !HasGoalBeenScoredLast() ) );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the extra time period state." )

} // futsim::football namespace