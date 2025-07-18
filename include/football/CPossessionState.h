#pragma once

#include "IJsonable.h"
#include "football/traits/CPossessionState.h"

#include <numeric>

#include "football/types/CPossessionState.h"

#include "football/CMatch.h"
#include "football/CMatchConfiguration.h"
#include "football/CTeamStrategy.h"
#include "football/types/CPossessionDrawConfiguration.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a possession draw.
*/
class CPossessionState : public IJsonable, protected json_traits<CPossessionState>
{
protected:
	using optional_name = types::CPossessionState::optional_name;
	using E_POSSESSION_DRAW_OUTCOME = types::CPossessionDrawConfiguration::E_POSSESSION_DRAW_OUTCOME;

public:
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
	explicit CPossessionState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aAttackingTeamStrategy,
		const CTeamStrategy& aDefendingTeamStrategy,
		const bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator
	);

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mOutcome
	const E_POSSESSION_DRAW_OUTCOME& GetOutcome() const noexcept;

	//! Retrieves the \copybrief mTackler
	const optional_name& GetTackler() const noexcept;

	//! Retrieves the \copybrief mPasser
	const optional_name& GetPasser() const noexcept;

private:
	//! Possession draw outcome.
	E_POSSESSION_DRAW_OUTCOME mOutcome;
	//! Player that made the tackle, if any.
	optional_name mTackler;
	//! Player that made the pass, if any.
	optional_name mPasser;
};

CPossessionState::CPossessionState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
) try
{
	using skill_bonus = types::CTacticConfiguration::skill_bonus;

	// Calculate each player's effective skill
	std::vector<skill_bonus> attackSkills, defenseSkills;
	attackSkills.reserve( futsim::default_traits<CLineupConfiguration>::MAX_PLAYERS );
	defenseSkills.reserve( futsim::default_traits<CLineupConfiguration>::MAX_PLAYERS );

	aAttackingTeamStrategy.ForEachPlayerSkill( E_PLAYER_SKILL::Ps, aMatch,
		aMatchConfiguration, aHomeTeamAttack, aDefendingTeamStrategy,
		[ &attackSkills ]( const auto& aSkill )
	{
		attackSkills.emplace_back( aSkill );
	} );
	aDefendingTeamStrategy.ForEachPlayerSkill( E_PLAYER_SKILL::Tk, aMatch,
		aMatchConfiguration, !aHomeTeamAttack, aAttackingTeamStrategy,
		[ &defenseSkills ]( const auto& aSkill )
	{
		defenseSkills.emplace_back( aSkill );
	} );

	// Draw possession outcome
	mOutcome = aMatchConfiguration.GetDrawConfiguration().CreatePossessionDistribution(
		std::accumulate( defenseSkills.cbegin(), defenseSkills.cend(), skill_bonus{} ),
		std::accumulate( attackSkills.cbegin(), attackSkills.cend(), skill_bonus{} ) )( aGenerator );

	// Draw acting player
	const auto DrawPlayer = [ &aGenerator ]( const auto& aLineup, const auto& aSkills )
	{
		return *( aLineup.template CreatePlayersView<false>()
			| std::ranges::views::drop( std::discrete_distribution<types::CLineup::names::size_type>{
			aSkills.cbegin(), aSkills.cend() }( aGenerator ) ) ).begin();
	};

	if( mOutcome == E_POSSESSION_DRAW_OUTCOME::KEEP_POSSESSION )
		mPasser = DrawPlayer( aAttackingTeamStrategy.GetLineup(), attackSkills );
	else if( mOutcome == E_POSSESSION_DRAW_OUTCOME::COUNTER_ATTACK )
		mTackler = DrawPlayer( aDefendingTeamStrategy.GetLineup(), defenseSkills );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the possession state." )

} // futsim::football namespace
