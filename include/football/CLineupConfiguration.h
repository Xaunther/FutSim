#pragma once

#include "IJsonable.h"

#include "football/types/CLineupConfiguration.h"

namespace futsim::football
{

class CLineup;

/**
 * @brief Class that configures the lineup rules.
*/
class CLineupConfiguration : public IJsonable
{
protected:
	using optional_player_count = types::CLineupConfiguration::optional_player_count;
	using player_count = types::CLineupConfiguration::player_count;
	using player_count_range = types::CLineupConfiguration::player_count_range;

public:
	/**
	 * @brief Member constructor.
	 * @param aDFRange \ref mDFRange
	 * @param aMFRange \ref mMFRange
	 * @param aFWRange \ref mFWRange
	 * @param aMinPlayerCount \ref mMinPlayerCount
	 * @param aBenchedPlayersCount \ref mBenchedPlayersCount
	*/
	explicit CLineupConfiguration(
		const player_count_range& aDFRange = DEFAULT_DF_RANGE,
		const player_count_range& aMFRange = DEFAULT_MF_RANGE,
		const player_count_range& aFWRange = DEFAULT_FW_RANGE,
		const player_count& aMinPlayerCount = DEFAULT_MIN_PLAYERS,
		const optional_player_count& aBenchedPlayersCount = DEFAULT_BENCHED_PLAYERS
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CLineupConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mDFRange
	const player_count_range& GetDFRange() const noexcept;

	//! Retrieves the \copybrief mMFRange
	const player_count_range& GetMFRange() const noexcept;

	//! Retrieves the \copybrief mFWRange
	const player_count_range& GetFWRange() const noexcept;

	//! Retrieves the \copybrief mMinPlayerCount
	const player_count& GetMinPlayerCount() const noexcept;

	//! Retrieves the \copybrief mBenchedPlayersCount
	const optional_player_count& GetBenchedPlayersCount() const noexcept;

	/**
	 * @brief Checks the validity of a lineup according to this configuration.
	 * @param aLineup Lineup to check.
	*/
	const CLineup& CheckLineup( const CLineup& aLineup ) const;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Lineup configuration";
	//! JSON key for the minimum number of DFs.
	static inline constexpr std::string_view JSON_MIN_DFS = "Min DFs";
	//! JSON key for the minimum number of MFs.
	static inline constexpr std::string_view JSON_MIN_MFS = "Min MFs";
	//! JSON key for the minimum number of FWs.
	static inline constexpr std::string_view JSON_MIN_FWS = "Min FWs";
	//! JSON key for the maximum number of DFs.
	static inline constexpr std::string_view JSON_MAX_DFS = "Max DFs";
	//! JSON key for the maximum number of MFs.
	static inline constexpr std::string_view JSON_MAX_MFS = "Max MFs";
	//! JSON key for the maximum number of FWs.
	static inline constexpr std::string_view JSON_MAX_FWS = "Max FWs";
	//! JSON key for the \copybrief mMinPlayerCount
	static inline constexpr std::string_view JSON_MIN_PLAYERS = "Min players";
	//! JSON key for the \copybrief mBenchedPlayersCount
	static inline constexpr std::string_view JSON_BENCHED_PLAYERS = "Benched players";

	//! Default \copybrief mDFRange
	static inline constexpr player_count_range DEFAULT_DF_RANGE = { 3, 6 };
	//! Default \copybrief mMFRange
	static inline constexpr player_count_range DEFAULT_MF_RANGE = { 2, 6 };
	//! Default \copybrief mFWRange
	static inline constexpr player_count_range DEFAULT_FW_RANGE = { 0, 4 };
	//! Default \copybrief mMinPlayerCount
	static inline constexpr player_count DEFAULT_MIN_PLAYERS = 7;
	//! Maximum number of players
	static inline constexpr player_count MAX_PLAYERS = 11;
	//! Default \copybrief mBenchedPlayersCount
	static inline constexpr optional_player_count DEFAULT_BENCHED_PLAYERS = 9;

private:
	//! Allowed DFs count range.
	player_count_range mDFRange;
	//! Allowed midfielders (DMs+MFs+AMs) count range.
	player_count_range mMFRange;
	//! Allowed FWs count range.
	player_count_range mFWRange;
	//! Minimum number of players.
	player_count mMinPlayerCount;
	//! Number of players on the bench. Empty for unlimited number.
	optional_player_count mBenchedPlayersCount;
};

} // futsim namespace