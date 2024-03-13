#pragma once

#include "football/CPlayTimeTypes.h"

namespace futsim::football::CLineupConfigurationTypes
{

//! Type for an optional player count.
using optional_player_count = CPlayTimeTypes::subs_count;

//! Type for a player count range.
using player_count_range = std::pair<optional_player_count::value_type, optional_player_count>;

} // futsim::football::CLineupConfigurationTypes namespace