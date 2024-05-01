#pragma once

#include "IJsonable.h"

#include "types/CPeriodState.h"

#include "football/CPlayState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a match period.
*/
class CPeriodState : public IJsonable
{
protected:
	using plays = types::CPeriodState::plays;

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
	explicit CPeriodState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator
	);

	const plays& GetPlays() const noexcept;

private:
	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aAttackingTeamStrategy Current match strategy for the attacking team.
	 * @param aDefendingTeamStrategy Current match strategy for the defending team.
	 * @param aHomeTeamAttack Whether the home team is attacking.
	 * @param aGenerator RNG to use.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	void Play(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aAttackingTeamStrategy,
		const CTeamStrategy& aDefendingTeamStrategy,
		const bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator
	);

	/**
	 * @brief Returns whether the home team is starting the next attack.
	*/
	bool IsHomeTeamAttackNext() const;

	//! Plays of the period.
	plays mPlays;
};

CPeriodState::CPeriodState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aHomeTeamStrategy,
	const CTeamStrategy& aAwayTeamStrategy,
	bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
)
{
	mPlays.reserve( aMatchConfiguration.GetPlayTime().GetPeriodTime() );

	for( futsim::types::CPlayTime::period_time time = 0; time < aMatchConfiguration.GetPlayTime().GetPeriodTime(); ++time )
	{
		if( aHomeTeamAttack )
			Play( aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy, aHomeTeamAttack, aGenerator );
		else
			Play( aMatch, aMatchConfiguration, aAwayTeamStrategy, aHomeTeamStrategy, aHomeTeamAttack, aGenerator );
		aHomeTeamAttack = IsHomeTeamAttackNext();
	}
}

void CPeriodState::Play(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
)
{
	CPlayState playState{ aMatch, aMatchConfiguration, aAttackingTeamStrategy, aDefendingTeamStrategy, aHomeTeamAttack, aGenerator };
	auto homeTeamPlay = playState.GetPossessionState().GetOutcome() == types::CPossessionDrawConfiguration::E_POSSESSION_DRAW_OUTCOME::COUNTER_ATTACK ?
		!aHomeTeamAttack : aHomeTeamAttack;
	mPlays.emplace_back( homeTeamPlay, std::move( playState ) );
}

} // futsim::football namespace