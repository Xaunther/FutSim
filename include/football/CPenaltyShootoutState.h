#pragma once

#include "IJsonable.h"
#include "football/traits/CPenaltyShootoutState.h"

#include "types/CPenaltyShootoutState.h"

#include "football/CMatch.h"
#include "football/CMatchConfiguration.h"
#include "football/CPenaltyState.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

namespace detail
{

//! Type for player references.
using shooters = std::vector<std::reference_wrapper<const CPlayer>>;

} // detail namespace

/**
 * @brief Class that represents the state of a penalty shootout.
*/
class CPenaltyShootoutState : public IJsonable, protected json_traits<CPenaltyShootoutState>
{
protected:
	using penalty_states = types::CPenaltyShootoutState::penalty_states;
	//! Aggregate for the score of each team, calculated as scored penalties + opposite team misses.
	struct score : public types::CPenaltyShootoutState::score
	{
		/**
		 * @brief Adds a score for the given team.
		 * @tparam tHomeTeam Whether the score is added to the home team.
		*/
		template <bool tHomeTeam> void Add() noexcept;
	};

public:
	/**
	 * @brief Constructor match definition and configuration.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aHomeTeamStrategy Current match strategy for the home team.
	 * @param aAwayTeamStrategy Current match strategy for the away team.
	 * @param aHomeTeamShoot Whether the home team starts shooting.
	 * @param aGenerator RNG to use.
	*/
	explicit CPenaltyShootoutState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		bool aHomeTeamShoot,
		std::uniform_random_bit_generator auto& aGenerator
	);

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPenalties
	const penalty_states& GetPenalties() const noexcept;

private:
	/**
	 * @brief Adds a penalty to the penalty states.
	 * @details The score is updated and the next shooter selected.
	 * @tparam tHomeTeam Whether the home team took the penalty.
	 * @param aPenaltyState Penalty to add.
	 * @param aShooterIt Iterator for the shooter.
	 * @param aShooters Shooters.
	 * @param [in,out] aScore Penalty score.
	*/
	template <bool tHomeTeam> void PushPenaltyState( CPenaltyState&& aPenaltyState,
		detail::shooters::const_iterator& aShooterIt, const detail::shooters& aShooters,
		score& aScore ) noexcept;

	/**
	 * @brief Returns whether the penalty shootout has been decided.
	 * @param aMinPenaltyCount Minimum number of penalties each team may take.
	 * @param aScore Current penalty score.
	*/
	bool IsDecided( const types::CPenaltyShootoutConfiguration::penalty_count& aMinPenaltyCount, const score& aScore ) const noexcept;

	//! Penalties.
	penalty_states mPenalties;
};

namespace detail
{

/**
 * @brief Creates penalty shooter list in ability order (from best to worst).
 * @param aTeam Team definition.
 * @param aCurrentPlayers View of the current playing players.
 * @param aShootersCount Number of shooters.
*/
shooters CreateShooters( const CTeam& aTeam, const auto& aCurrentPlayers, const std::size_t& aShootersCount );

/**
 * @brief Returns the function that calculates the next shooting team.
 * @param aPenaltySequence Penalty sequence used.
*/
std::function<bool( const bool, const std::size_t& )> NextHomeTeamShoot( const E_PENALTY_SEQUENCE& aPenaltySequence );

} // detail namespace

CPenaltyShootoutState::CPenaltyShootoutState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aHomeTeamStrategy,
	const CTeamStrategy& aAwayTeamStrategy,
	bool aHomeTeamShoot,
	std::uniform_random_bit_generator auto& aGenerator
) try
{
	if( !aMatchConfiguration.GetPenaltyShootoutConfiguration() )
		throw std::invalid_argument{ "The match configuration must include a penalty shootout configuration." };

	// Get playing players
	const auto& homeTeamCurrentPlayers = aHomeTeamStrategy.GetLineup().CreatePlayersView<false>(),
		awayTeamCurrentPlayers = aAwayTeamStrategy.GetLineup().CreatePlayersView<false>();

	// Get number of shooters, taking into account any send-offs or unreplaced injuries
	const std::size_t shootersCount = std::min( std::ranges::distance( homeTeamCurrentPlayers ), std::ranges::distance( awayTeamCurrentPlayers ) );

	// Create shooters for each time, in decreasing shoot skill level
	const auto& homeTeamShooters = detail::CreateShooters( aMatch.GetHomeTeam(), homeTeamCurrentPlayers, shootersCount ),
		awayTeamShooters = detail::CreateShooters( aMatch.GetAwayTeam(), awayTeamCurrentPlayers, shootersCount );

	// Get goalkeeper for each team
	const auto& homeTeamGK = aMatch.GetHomeTeam().GetPlayer( aHomeTeamStrategy.GetLineup().GetPlayers<E_PLAYER_POSITION::GK>() ),
		awayTeamGK = aMatch.GetAwayTeam().GetPlayer( aAwayTeamStrategy.GetLineup().GetPlayers<E_PLAYER_POSITION::GK>() );

	// Get the function deciding who's next
	const auto& nextHomeTeamShoot = detail::NextHomeTeamShoot( aMatchConfiguration.GetPenaltyShootoutConfiguration()->GetPenaltySequence() );

	// Initialize penalty score
	score currentScore;

	for( auto homeTeamShooterIt = homeTeamShooters.cbegin(), awayTeamShooterIt = awayTeamShooters.cbegin();
		!IsDecided( aMatchConfiguration.GetPenaltyShootoutConfiguration()->GetMinPenaltyCount(), currentScore ); )
	{
		if( aHomeTeamShoot )
			PushPenaltyState<true>( CPenaltyState{ aMatch, aMatchConfiguration, *homeTeamShooterIt,
				awayTeamGK, aHomeTeamShoot, aGenerator }, homeTeamShooterIt, homeTeamShooters, currentScore );
		else
			PushPenaltyState<false>( CPenaltyState{ aMatch, aMatchConfiguration, *awayTeamShooterIt,
				homeTeamGK, aHomeTeamShoot, aGenerator }, awayTeamShooterIt, awayTeamShooters, currentScore );
		aHomeTeamShoot = nextHomeTeamShoot( aHomeTeamShoot, mPenalties.size() );
	};
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the penalty shootout state." )

namespace detail
{

shooters CreateShooters( const CTeam& aTeam, const auto& aCurrentPlayers, const std::size_t& aShootersCount ) try
{
	shooters result;
	result.reserve( std::ranges::distance( aCurrentPlayers ) );
	std::ranges::transform( aCurrentPlayers, std::back_inserter( result ), [ &aTeam ]( const auto& aPlayer )
	{
		return std::cref( aTeam.GetPlayer( aPlayer ) );
	} );

	std::ranges::sort( result, std::ranges::greater{}, []( const CPlayer& aPlayer )
	{
		return aPlayer.GetPlayerSkills().GetSkill( E_PLAYER_SKILL::Sh );
	} );
	result.erase( result.cbegin() + static_cast<shooters::difference_type>( aShootersCount ), result.cend() );
	return result;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the penalty shooters." )

} // detail namespace

} // futsim::football namespace
