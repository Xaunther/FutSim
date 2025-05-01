#pragma once

#include "football/types/CPlayTime.h"

namespace futsim::football::types::CLineupConfiguration
{

//! Type for an optional player count.
using optional_player_count = types::CPlayTime::subs_count;

//! Type for a player count.
using player_count = optional_player_count::value_type;

//! Aggregate for a player count range.
struct player_count_range
{
	using min_type = player_count;
	using max_type = optional_player_count;
	//! Minimum number of players.
	min_type min = 0;
	//! Maximum number of players, if any.
	max_type max;
};

} // futsim::football::types::CLineupConfiguration namespace
