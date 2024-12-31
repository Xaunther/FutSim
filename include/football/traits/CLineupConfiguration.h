#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include "football/types/CLineupConfiguration.h"

#include <string_view>

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

} // futsim namespace
