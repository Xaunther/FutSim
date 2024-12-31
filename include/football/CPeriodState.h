#pragma once

#include "IJsonable.h"
#include "football/traits/CPeriodState.h"

#include "types/CPeriodState.h"

#include "football/CPlayState.h"
#include "football/CPeriodPlayPolicy.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a match period.
*/
class CPeriodState : public IJsonable, protected json_traits<football::CPeriodState>
{
protected:
	using plays = types::CPeriodState::plays;
	using goal_count = types::CTieCondition::goal_count;

public:
	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aHomeTeamStrategy Current match strategy for the home team.
	 * @param aAwayTeamStrategy Current match strategy for the away team.
	 * @param aHomeTeamAttack Whether the home team is attacking.
	 * @param aGenerator RNG to use.
	 * @param aPeriodPlayPolicy Period play policy.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	explicit CPeriodState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator,
		const IPeriodPlayPolicy& aPeriodPlayPolicy = CPeriodPlayPolicy{}
	);

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPlays
	const plays& GetPlays() const noexcept;

	/**
	 * @brief Counts the goals scored by the given team.
	 * @param aHomeTeam Whether to count the home team goals.
	*/
	goal_count CountScoredGoals( const bool aHomeTeam ) const noexcept;

protected:
	/**
	 * @brief Adds a play to the plays of the period
	 * @param aPlayState Play to add.
	 * @param aHomeTeamAttack Whether the home team is attacking.
	*/
	void PushPlayState( CPlayState&& aPlayState, const bool aHomeTeamAttack ) noexcept;

	/**
	 * @brief Returns whether the home team is starting the next attack.
	*/
	bool IsHomeTeamAttackNext() const;

private:
	//! Plays of the period.
	plays mPlays;
};

CPeriodState::CPeriodState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aHomeTeamStrategy,
	const CTeamStrategy& aAwayTeamStrategy,
	bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator,
	const IPeriodPlayPolicy& aPeriodPlayPolicy
)
{
	mPlays.reserve( aMatchConfiguration.GetPlayTime().GetPeriodTime() );

	do
	{
		if( aHomeTeamAttack )
			PushPlayState( CPlayState{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy,
				aHomeTeamAttack, aGenerator }, aHomeTeamAttack );
		else
			PushPlayState( CPlayState{ aMatch, aMatchConfiguration, aAwayTeamStrategy, aHomeTeamStrategy,
				aHomeTeamAttack, aGenerator }, aHomeTeamAttack );
		aHomeTeamAttack = IsHomeTeamAttackNext();
	} while( aPeriodPlayPolicy( mPlays, aMatchConfiguration ) );
}

} // futsim::football namespace
