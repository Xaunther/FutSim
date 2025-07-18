#pragma once

#include "IJsonable.h"
#include "football/traits/CChanceState.h"

#include "football/types/CChanceState.h"
#include "football/types/CGoalDrawConfiguration.h"

#include "football/CMatch.h"
#include "football/CMatchConfiguration.h"
#include "football/CTeamStrategy.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a chance.
*/
class CChanceState : public IJsonable, protected json_traits<CChanceState>
{
protected:
	using chance_type = types::CChanceState::chance_type;
	using optional_name = types::CChanceState::optional_name;
	using E_CHANCE_OUTCOME = types::CGoalDrawConfiguration::E_CHANCE_OUTCOME;

public:
	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @tparam tIsSetPiece Indicates whether the chance is a set piece
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aAttackingTeamStrategy Current match strategy for the attacking team.
	 * @param aDefendingTeamStrategy Current match strategy for the defending team.
	 * @param aHomeTeamAttack Whether the home team is attacking.
	 * @param aGenerator RNG to use.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	template<typename tIsSetPiece> requires std::same_as<tIsSetPiece, std::true_type> || std::same_as<tIsSetPiece, std::false_type>
	explicit CChanceState(
		const tIsSetPiece&,
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aAttackingTeamStrategy,
		const CTeamStrategy& aDefendingTeamStrategy,
		const bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator
	);

	/**
	 * @brief Constructor for a certain chance type from the match definition, configuration and current strategies.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aAttackingTeamStrategy Current match strategy for the attacking team.
	 * @param aDefendingTeamStrategy Current match strategy for the defending team.
	 * @param aHomeTeamAttack Whether the home team is attacking.
	 * @param aChanceType Chance type.
	 * @param aGenerator RNG to use.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	explicit CChanceState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aAttackingTeamStrategy,
		const CTeamStrategy& aDefendingTeamStrategy,
		const bool aHomeTeamAttack,
		const chance_type& aChanceType,
		std::uniform_random_bit_generator auto& aGenerator
	);

protected:
	/**
	 * @brief Member constructor.
	 * @param aChanceType \ref mChanceType
	 * @param aOutcome \ref mOutcome
	 * @param aStopper \ref mChanceType
	 * @param aTackler \ref mChanceType
	 * @param aPasser \ref mChanceType
	 * @param aShooter \ref mChanceType
	*/
	explicit CChanceState(
		const chance_type& aChanceType,
		const E_CHANCE_OUTCOME& aOutcome,
		const optional_name& aStopper = {},
		const optional_name& aTackler = {},
		const optional_name& aPasser = {},
		const optional_name& aShooter = {}
	) noexcept;

	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mChanceType
	const chance_type& GetChanceType() const noexcept;

	//! Retrieves the \copybrief mOutcome
	const E_CHANCE_OUTCOME& GetChanceOutcome() const noexcept;

	/**
	 * @brief Retrieves the given actor, if any.
	 * @tparam tPlayerSkill Skill used by the actor.
	*/
	template <E_PLAYER_SKILL tPlayerSkill> const optional_name& GetActor() const noexcept;

protected:
	/**
	 * @brief Adds an actor to the JSON object.
	 * @tparam tPlayerSkill Skill used by the actor.
	 * @param aJSON JSON object.
	*/
	template <E_PLAYER_SKILL tPlayerSkill> void JSONActor( json& aJSON ) const noexcept;

private:
	//! \copydoc GetActor
	template <E_PLAYER_SKILL tPlayerSkill> optional_name& Actor() noexcept;

	//! Chance type draw outcome.
	chance_type mChanceType;
	//! Chance outcome.
	E_CHANCE_OUTCOME mOutcome;
	//! Player that made the save, if any.
	optional_name mStopper;
	//! Player that made the tackle, if any.
	optional_name mTackler;
	//! Player that made the pass, if any.
	optional_name mPasser;
	//! Player that made the shot, if any.
	optional_name mShooter;
};

namespace detail
{

//! Aggregate for the drawn player.
struct drawn_player
{
	//! Player name.
	std::string_view name;
	//! Player position.
	E_PLAYER_POSITION position;
};

/**
 * @brief Draws a player from a lineup.
 * @tparam tPlayerSkill Player skill to consider.
 * @param aGoalDrawConfiguration Goal draw configuration.
 * @param aLineup Lineup.
 * @param aGenerator RNG to use.
 * @return A pair containing the drawn player name and their position.
*/
template <E_PLAYER_SKILL tPlayerSkill>
drawn_player DrawPlayer( const CGoalDrawConfiguration& aGoalDrawConfiguration,
	const CLineup& aLineup, std::uniform_random_bit_generator auto& aGenerator );

/**
 * @brief Draws a chance outcome.
 * @param aChanceType Chance type to draw an outcome from.
 * @param aOutcomeDrawer Function that draws the chance outcome.
*/
types::CGoalDrawConfiguration::E_CHANCE_OUTCOME DrawOutcome( const types::CChanceState::chance_type& aChanceType, const auto& aOutcomeDrawer );

} // detail namespace

template <typename tIsSetPiece> requires std::same_as<tIsSetPiece, std::true_type> || std::same_as<tIsSetPiece, std::false_type>
CChanceState::CChanceState(
	const tIsSetPiece&,
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
) :
	CChanceState( aMatch, aMatchConfiguration, aAttackingTeamStrategy, aDefendingTeamStrategy, aHomeTeamAttack,
		tIsSetPiece() ? chance_type{ aMatchConfiguration.GetDrawConfiguration().CreateSetPieceTypeDistribution()( aGenerator ) } :
		chance_type{ aMatchConfiguration.GetDrawConfiguration().CreateChanceTypeDistribution()( aGenerator ) }, aGenerator )
{
}

CChanceState::CChanceState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aAttackingTeamStrategy,
	const CTeamStrategy& aDefendingTeamStrategy,
	const bool aHomeTeamAttack,
	const chance_type& aChanceType,
	std::uniform_random_bit_generator auto& aGenerator
)  try :
	mChanceType( aChanceType )
{
	// Draws an actor for a role and returns their effective skill
	const auto EffectivePlayerSkillDrawer = [ &aMatch, &aMatchConfiguration, &aGenerator, this ]<E_PLAYER_SKILL tPlayerSkill>
		( const CTeamStrategy & aOwnTeamStrategy, const CTeamStrategy & aRivalTeamStrategy, const bool aIsHomeTeam )
	{
		const auto& drawnPlayer = detail::DrawPlayer<tPlayerSkill>( aMatchConfiguration.GetDrawConfiguration().GetGoalDrawConfiguration(),
			aOwnTeamStrategy.GetLineup(), aGenerator );
		// Sets the drawn player to the given role
		// @todo Remove redundant this usage when CLANG allows it https://github.com/llvm/llvm-project/issues/81243
		this->Actor< tPlayerSkill >() = drawnPlayer.name;
		return CTeamStrategy::CalculateEffectivePlayerSkill( drawnPlayer.name, tPlayerSkill, drawnPlayer.position, aMatch,
			aMatchConfiguration, aIsHomeTeam, aOwnTeamStrategy.GetTacticID(), aRivalTeamStrategy );
	};

	// Calls the effective player skill drawer taking into account whether the actor is defending or attacking
	const auto DrawEffectivePlayerSkill = [ &EffectivePlayerSkillDrawer, &aAttackingTeamStrategy, &aDefendingTeamStrategy, aHomeTeamAttack ]
		<E_PLAYER_SKILL tPlayerSkill>( )
	{
		if constexpr( tPlayerSkill == E_PLAYER_SKILL::St || tPlayerSkill == E_PLAYER_SKILL::Tk )
			return EffectivePlayerSkillDrawer.template operator() < tPlayerSkill > ( aDefendingTeamStrategy, aAttackingTeamStrategy, !aHomeTeamAttack );
		else
			return EffectivePlayerSkillDrawer.template operator() < tPlayerSkill > ( aAttackingTeamStrategy, aDefendingTeamStrategy, aHomeTeamAttack );
	};

	// Draws an outcome
	const auto OutcomeDrawer = [ &aMatchConfiguration, &aGenerator, &DrawEffectivePlayerSkill ]<E_PLAYER_SKILL... tSkills>( const auto & aMethod )
	{
		return aMethod( aMatchConfiguration.GetDrawConfiguration(), DrawEffectivePlayerSkill.template operator() < tSkills > ( )... )( aGenerator );
	};

	mOutcome = detail::DrawOutcome( mChanceType, OutcomeDrawer );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the chance state." )

namespace detail
{

template <E_PLAYER_SKILL tPlayerSkill>
drawn_player DrawPlayer( const CGoalDrawConfiguration& aGoalDrawConfiguration,
	const CLineup& aLineup, std::uniform_random_bit_generator auto& aGenerator )
{
	using enum E_PLAYER_POSITION;
	while( true )
	{
		if( const auto& playerPosition = aGoalDrawConfiguration.CreatePositionDrawDistribution< tPlayerSkill >() ( aGenerator ); playerPosition == GK )
			return { aLineup.GetPlayers<GK>(), playerPosition };
		else if( const auto& players = playerPosition == DF ? aLineup.GetPlayers<DF>() :
			playerPosition == DM ? aLineup.GetPlayers<DM>() :
			playerPosition == MF ? aLineup.GetPlayers<MF>() :
			playerPosition == AM ? aLineup.GetPlayers<AM>() :
			aLineup.GetPlayers<FW>(); players.size() > 0 )
			return { players[ std::uniform_int_distribution<std::size_t>{ 0, players.size() - 1 }( aGenerator ) ], playerPosition };
	}
}

types::CGoalDrawConfiguration::E_CHANCE_OUTCOME DrawOutcome( const types::CChanceState::chance_type& aChanceType, const auto& aOutcomeDrawer )
{
	using enum types::CChancesDrawConfiguration::E_SET_PIECE_TYPE;
	using enum types::CChancesDrawConfiguration::E_CHANCE_TYPE;
	using enum E_PLAYER_SKILL;
	if( const auto* chance = std::get_if<types::CChancesDrawConfiguration::E_SET_PIECE_TYPE>( &aChanceType ) )
	{
		switch( *chance )
		{
		case PENALTY:
			return aOutcomeDrawer.template operator() < St, Sh > ( std::mem_fn( &CDrawConfiguration::CreatePenaltyOutcomeDistribution ) );
		case DIRECT_FREE_KICK:
			return aOutcomeDrawer.template operator() < St, Sh > ( std::mem_fn( &CDrawConfiguration::CreateDirectFreeKickOutcomeDistribution ) );
		case INDIRECT_FREE_KICK:
			return aOutcomeDrawer.template operator() < St, Tk, Ps, Sh > ( std::mem_fn( &CDrawConfiguration::CreateIndirectFreeKickOutcomeDistribution ) );
		}
	}
	else
	{
		switch( std::get<types::CChancesDrawConfiguration::E_CHANCE_TYPE>( aChanceType ) )
		{
		case CORNER:
			return aOutcomeDrawer.template operator() < St, Tk, Ps, Sh > ( std::mem_fn( &CDrawConfiguration::CreateCornerOutcomeDistribution ) );
		case ONE_ON_ONE_VS_GK:
			return aOutcomeDrawer.template operator() < St, Ps, Sh > ( std::mem_fn( &CDrawConfiguration::Create1vs1GKOutcomeDistribution ) );
		case ONE_ON_ONE_VS_DF:
			return aOutcomeDrawer.template operator() < St, Tk, Ps, Sh > ( std::mem_fn( &CDrawConfiguration::Create1vs1DFOutcomeDistribution ) );
		case NEAR_SHOT:
			return aOutcomeDrawer.template operator() < St, Sh > ( std::mem_fn( &CDrawConfiguration::CreateNearShotOutcomeDistribution ) );
		case FAR_SHOT:
			return aOutcomeDrawer.template operator() < St, Sh > ( std::mem_fn( &CDrawConfiguration::CreateFarShotOutcomeDistribution ) );
		}
	}
	throw std::domain_error{ "Error drawing the chance outcome." };
}

} //detail namespace

} // futsim::football namespace
