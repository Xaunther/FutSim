#pragma once

#include "IJsonable.h"

#include "football/CLineupTypes.h"

#include <random>
#include <span>

namespace futsim::football
{

/**
 * @brief Class that defines a lineup.
*/
class CLineup : public IJsonable
{
protected:
	using names = CLineupTypes::names;
	using position_names = CLineupTypes::position_names;
	using position_weights = CLineupTypes::position_weights;

public:
	/**
	 * @brief Member constructor.
	 * @param aPlayersLineup \ref mPlayersLineup
	*/
	explicit CLineup( const position_names& aPlayersLineup );

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
	//! Retrieves the \copybrief mPlayersLineup
	const position_names& GetPlayers() const noexcept;

	/**
	 * @brief Retrieves the players at a certain position.
	 * @param aPlayerPosition Position.
	*/
	std::span<const names::value_type> GetPlayers( const E_PLAYER_POSITION& aPlayerPosition ) const noexcept;

	//! Retrieves the substitute players.
	std::span<const names::value_type> GetSubs() const noexcept;

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
	//! Checks the validity of the players lineup.
	void CheckPlayersLineup() const;

	//! Lined up players by position.
	position_names mPlayersLineup;
};

std::string_view CLineup::DrawPlayer( std::uniform_random_bit_generator auto& aGenerator,
	const position_weights& aPositionWeights ) const noexcept
{
	std::vector<double> playerWeights;
	for( auto positionWeightIt = aPositionWeights.cbegin(); const auto & positionPlayers : mPlayersLineup )
		std::fill_n( std::back_inserter( playerWeights ), positionPlayers.size(), *( positionWeightIt++ ) );
	const auto& drawn = std::discrete_distribution<position_names::size_type>{ playerWeights.cbegin(), playerWeights.cend() }( aGenerator );

	return *( mPlayersLineup | std::ranges::views::join
		| std::ranges::views::take( drawn + 1 )
		| std::ranges::views::drop( drawn ) ).begin();
}

} // futsim namespace