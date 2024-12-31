#pragma once

#include "IJsonable.h"

#include "football/types/CLineupConfiguration.h"
#include "DefaultTraits.h"

namespace futsim
{

namespace football
{
class CLineupConfiguration;
}

template <> struct default_traits<football::CLineupConfiguration>
{
protected:
	using optional_player_count = football::types::CLineupConfiguration::optional_player_count;
	using player_count = football::types::CLineupConfiguration::player_count;
	using player_count_range = football::types::CLineupConfiguration::player_count_range;
public:
	//! Default \copybrief football::CLineupConfiguration::mDFRange
	static inline constexpr player_count_range DF_RANGE = { 3, 6 };
	//! Default \copybrief football::CLineupConfiguration::mMFRange
	static inline constexpr player_count_range MF_RANGE = { 2, 6 };
	//! Default \copybrief football::CLineupConfiguration::mFWRange
	static inline constexpr player_count_range FW_RANGE = { 0, 4 };
	//! Default \copybrief football::CLineupConfiguration::mMinPlayerCount
	static inline constexpr player_count MIN_PLAYERS = 7;
	//! Maximum number of players
	static inline constexpr player_count MAX_PLAYERS = 11;
	//! Default \copybrief football::CLineupConfiguration::mBenchedPlayersCount
	static inline constexpr optional_player_count BENCHED_PLAYERS = 9;
};

template <> struct json_traits<football::CLineupConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Lineup configuration";
	//! JSON key for the minimum number of DFs.
	static inline constexpr std::string_view MIN_DFS_KEY = "Min DFs";
	//! JSON key for the minimum number of MFs.
	static inline constexpr std::string_view MIN_MFS_KEY = "Min MFs";
	//! JSON key for the minimum number of FWs.
	static inline constexpr std::string_view MIN_FWS_KEY = "Min FWs";
	//! JSON key for the maximum number of DFs.
	static inline constexpr std::string_view MAX_DFS_KEY = "Max DFs";
	//! JSON key for the maximum number of MFs.
	static inline constexpr std::string_view MAX_MFS_KEY = "Max MFs";
	//! JSON key for the maximum number of FWs.
	static inline constexpr std::string_view MAX_FWS_KEY = "Max FWs";
	//! JSON key for the \copybrief football::CLineupConfiguration::mMinPlayerCount
	static inline constexpr std::string_view MIN_PLAYERS_KEY = "Min players";
	//! JSON key for the \copybrief football::CLineupConfiguration::mBenchedPlayersCount
	static inline constexpr std::string_view BENCHED_PLAYERS_KEY = "Benched players";
};

namespace football
{

class CLineup;

/**
 * @brief Class that configures the lineup rules.
*/
class CLineupConfiguration : public IJsonable, protected default_traits<CLineupConfiguration>, protected json_traits<CLineupConfiguration>
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
		const player_count_range& aDFRange = DF_RANGE,
		const player_count_range& aMFRange = MF_RANGE,
		const player_count_range& aFWRange = FW_RANGE,
		const player_count& aMinPlayerCount = MIN_PLAYERS,
		const optional_player_count& aBenchedPlayersCount = BENCHED_PLAYERS
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

} // football namespace

} // futsim namespace
