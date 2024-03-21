#pragma once

#include "IJsonable.h"

#include "football/CLineupTypes.h"

#include <random>

namespace futsim::football
{

/**
 * @brief Class that defines a lineup.
*/
class CLineup : public IJsonable
{
protected:
	using name = CLineupTypes::name;
	using names = CLineupTypes::names;
	using position_weights = CLineupTypes::position_weights;
	using position_names = std::array<names, std::tuple_size_v<position_weights>>;
	template<E_PLAYER_POSITION tPlayerPosition> using players = CLineupTypes::players<tPlayerPosition>;
	using player_predicate = CLineupTypes::player_predicate;

public:
	/**
	 * @brief Constructor from the players in each position.
	 * @param aGK Goalkeeper.
	 * @param aDFs Defenders.
	 * @param aDMs Defensive midfielders.
	 * @param aMFs Midfielders.
	 * @param aAMs Attacking midfielders.
	 * @param aFWs Forwards.
	 * @param aSubs Substitutes.
	*/
	explicit CLineup(
		const std::string_view aGK,
		const std::span<const name> aDFs,
		const std::span<const name> aDMs,
		const std::span<const name> aMFs,
		const std::span<const name> aAMs,
		const std::span<const name> aFWs,
		const std::span<const name> aSubs
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CLineup( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	/**
	 * @brief Retrieves the players at a certain position.
	 * @tparam tPlayerPosition Position.
	*/
	template <E_PLAYER_POSITION tPlayerPosition>
	players<tPlayerPosition> GetPlayers() const noexcept;

	//! Retrieves the substitute players.
	std::span<const name> GetSubs() const noexcept;

	//! Gets the number of players currently playing.
	names::size_type GetPlayersInPlayCount() const noexcept;

	/**
	 * @brief Applies the given predicate to every player currently playing.
	 * @param aPredicate Player predicate.
	 * @tparam tUseSubs Whether the predicate must be applied to the subs too.
	*/
	template <bool tUseSubs> void ForEachPlayer( const player_predicate& aPredicate ) const;

	/**
	 * @brief Draws a random player using the given weights for each position.
	 * @details The players in the same position have equal probabilities.
	 * @param aGenerator RNG to use.
	 * @param aPositionWeights Weight given to each position.
	 * @return A view to the drawn player's name.
	*/
	std::string_view DrawPlayer( std::uniform_random_bit_generator auto& aGenerator,
		const position_weights& aPositionWeights ) const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Lineup";
	//! JSON key for the GK.
	static inline constexpr std::string_view JSON_GK = "GK";
	//! JSON key for the DFs.
	static inline constexpr std::string_view JSON_DFS = "DFs";
	//! JSON key for the DMs.
	static inline constexpr std::string_view JSON_DMS = "DMs";
	//! JSON key for the MFs.
	static inline constexpr std::string_view JSON_MFS = "MFs";
	//! JSON key for the AMs.
	static inline constexpr std::string_view JSON_AMS = "AMs";
	//! JSON key for the FWs.
	static inline constexpr std::string_view JSON_FWS = "FWs";
	//! JSON key for the substitutes.
	static inline constexpr std::string_view JSON_SUBS = "Subs";

private:
	//! Lined up players by position.
	position_names mPlayersLineup;
};

std::string_view CLineup::DrawPlayer( std::uniform_random_bit_generator auto& aGenerator,
	const position_weights& aPositionWeights ) const noexcept
{
	std::vector<position_weights::value_type> playerWeights;
	for( auto positionWeightIt = aPositionWeights.cbegin(); const auto & positionPlayers : mPlayersLineup )
		std::fill_n( std::back_inserter( playerWeights ), positionPlayers.size(), *( positionWeightIt++ ) );

	return *( mPlayersLineup | std::ranges::views::join | std::ranges::views::drop(
		std::discrete_distribution<position_names::size_type>{ playerWeights.cbegin(), playerWeights.cend() }( aGenerator ) ) ).begin();
}

} // futsim namespace