#pragma once

#include "football/types/CPlayTime.h"

namespace futsim::football::types::CLineupConfiguration
{

//! Type for an optional player count.
using optional_player_count = types::CPlayTime::subs_count;

//! Type for a player count.
using player_count = optional_player_count::value_type;

//! Type for a player count range.
using player_count_range = std::pair<player_count, optional_player_count>;


} // futsim::football::types::CLineupConfiguration namespace