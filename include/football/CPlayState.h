#pragma once

#include "IJsonable.h"

#include "football/types/CPlayState.h"

#include "football/CChanceState.h"
#include "football/CFoulState.h"
#include "football/CPossessionState.h"
#include "football/EPlayerSkill.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a single play.
*/
class CPlayState : public IJsonable
{
protected:
	using optional_foul_state = types::CPlayState::optional_foul_state;
	using chances_states = types::CPlayState::chances_states;

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
	explicit CPlayState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aAttackingTeamStrategy,
		const CTeamStrategy& aDefendingTeamStrategy,
		const bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator
	) noexcept;

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPossessionState
	const CPossessionState& GetPossessionState() const noexcept;

	//! Retrieves the \copybrief mFoulState
	const optional_foul_state& GetFoulState() const noexcept;

	//! Retrieves the \copybrief mChancesStates
	const chances_states& GetChancesStates() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Play state";
	//! JSON key for the \copybrief mChancesStates
	static inline constexpr std::string_view JSON_CHANCES = "Chances";

private:
	//! Possession state.
	CPossessionState mPossessionState;
	//! Foul state, if any.
	optional_foul_state mFoulState;
	//! Chances states.
	chances_states mChancesStates;
};

namespace detail
{

/**
 * @brief Draws the chances.
 * @param aPossessionDrawOutcome Outcome of the possession draw.
 * @param aMatch Match definition.
 * @param aMatchConfiguration Match configuration.
 * @param aAttackingTeamStrategy Current match strategy for the attacking team.
 * @param aDefendingTeamStrategy Current match strategy for the defending team.
 * @param aHomeTeamAttack Whether the home team is attacking.
 * @param aGenerator RNG to use.
 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
*/
types::CPlayState::chances_states DrawChances(
	const types::CPossessionDrawConfiguration::E_POSSESSION_DRAW_OUTCOME& aPossessionDrawOutcome,
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
) noexcept;

/**
 * @brief Creates the chance sequence.
 * @param aMatch Match definition.
 * @param aMatchConfiguration Match configuration.
 * @param aAttackingTeamStrategy Current match strategy for the attacking team.
 * @param aDefendingTeamStrategy Current match strategy for the defending team.
 * @param aHomeTeamAttack Whether the home team is attacking.
 * @param aIsSetPiece Whether the chance generates from a set piece.
 * @param aGenerator RNG to use.
 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
 * @post The sequence has at least one chance.
*/
types::CPlayState::chances_states CreateChances(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	const bool aIsSetPiece,
	std::uniform_random_bit_generator auto& aGenerator
) noexcept;

} // detail namespace

CPlayState::CPlayState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
) noexcept :
	mPossessionState( aMatch, aMatchConfiguration, aAttackingTeamStrategy, aDefendingTeamStrategy, aHomeTeamAttack, aGenerator ),
	mFoulState( mPossessionState.GetOutcome() == types::CPossessionDrawConfiguration::E_POSSESSION_DRAW_OUTCOME::FOUL ?
		CFoulState{ aMatchConfiguration, aDefendingTeamStrategy, aGenerator } : optional_foul_state{} ),
	mChancesStates( mPossessionState.GetOutcome() == types::CPossessionDrawConfiguration::E_POSSESSION_DRAW_OUTCOME::COUNTER_ATTACK ?
		detail::DrawChances( mPossessionState.GetOutcome(), aMatch, aMatchConfiguration, aDefendingTeamStrategy,
			aAttackingTeamStrategy, !aHomeTeamAttack, aGenerator ) :
		detail::DrawChances( mPossessionState.GetOutcome(), aMatch, aMatchConfiguration, aAttackingTeamStrategy,
			aDefendingTeamStrategy, aHomeTeamAttack, aGenerator ) )
{
}

namespace detail
{

types::CPlayState::chances_states DrawChances(
	const types::CPossessionDrawConfiguration::E_POSSESSION_DRAW_OUTCOME& aPossessionDrawOutcome,
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
) noexcept
{
	if( aPossessionDrawOutcome != types::CPossessionDrawConfiguration::E_POSSESSION_DRAW_OUTCOME::FOUL )
	{
		types::CTacticConfiguration::skill_bonus TkSkill = 0, ShSkill = 0;
		if( aMatchConfiguration.GetDrawConfiguration().CreateChanceDistribution( ( aDefendingTeamStrategy.ForEachPlayerSkill(
			E_PLAYER_SKILL::Tk, aMatch, aMatchConfiguration, !aHomeTeamAttack, aAttackingTeamStrategy,
			[ &TkSkill ]( const auto& aSkill ) { TkSkill += aSkill; } ), TkSkill ),
			( aAttackingTeamStrategy.ForEachPlayerSkill( E_PLAYER_SKILL::Sh, aMatch, aMatchConfiguration, aHomeTeamAttack, aDefendingTeamStrategy,
				[ &ShSkill ]( const auto& aSkill ) { ShSkill += aSkill; } ), ShSkill ) )( aGenerator ) )
			return CreateChances( aMatch, aMatchConfiguration, aAttackingTeamStrategy, aDefendingTeamStrategy, aHomeTeamAttack, false, aGenerator );
	}
	else if( aMatchConfiguration.GetDrawConfiguration().CreateSetPieceDistribution()( aGenerator ) )
		return CreateChances( aMatch, aMatchConfiguration, aAttackingTeamStrategy, aDefendingTeamStrategy, aHomeTeamAttack, true, aGenerator );

	return {};
}

types::CPlayState::chances_states CreateChances(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	const bool aIsSetPiece,
	std::uniform_random_bit_generator auto& aGenerator
) noexcept
{
	using enum types::CGoalDrawConfiguration::E_CHANCE_OUTCOME;
	types::CPlayState::chances_states result{ CChanceState{ aMatch, aMatchConfiguration, aAttackingTeamStrategy, aDefendingTeamStrategy, aHomeTeamAttack, aIsSetPiece, aGenerator } };
	while( result.back().GetChanceOutcome() == EXTRA_CORNER_FROM_DF || result.back().GetChanceOutcome() == EXTRA_CORNER_FROM_GK )
		result.emplace_back( aMatch, aMatchConfiguration, aAttackingTeamStrategy, aDefendingTeamStrategy, aHomeTeamAttack, types::CChancesDrawConfiguration::E_CHANCE_TYPE::CORNER, aGenerator );
	return result;
}

} // detail namespace

} // futsim::football namespace
