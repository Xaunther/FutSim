#pragma once

#include "IJsonable.h"

#include "football/types/CLineup.h"

#include <random>

namespace futsim::football
{

/**
 * @brief Class that defines a lineup.
*/
class CLineup : public IJsonable
{
protected:
	using name = types::CLineup::name;
	using names = types::CLineup::names;
	using position_weights = types::CLineup::position_weights;
	using position_names = std::array<names, std::tuple_size_v<position_weights>>;
	template<E_PLAYER_POSITION tPlayerPosition> using players = types::CLineup::players<tPlayerPosition>;
	using player_predicate = types::CLineup::player_predicate;

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

	/**
	 * @brief Creates a view of the players
	 * @tparam tUseSubs Whether the subs must be counted too.
	*/
	template <bool tUseSubs> auto CreatePlayersView() const noexcept;

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

template <bool tUseSubs> auto CLineup::CreatePlayersView() const noexcept
{
	if constexpr( tUseSubs )
		return mPlayersLineup | std::ranges::views::join;
	else
		return mPlayersLineup | std::ranges::views::take( static_cast< names::size_type >( E_PLAYER_POSITION::FW ) + 1 )
		| std::ranges::views::join;
}

} // futsim namespace