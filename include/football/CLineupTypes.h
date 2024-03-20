#pragma once

#include "CPersonTypes.h"

#include "football/EPlayerPosition.h"

#include <array>
#include <vector>

namespace futsim::football::CLineupTypes
{

//! Type for a vector of names.
using names = std::vector<CPersonTypes::name_type>;

//! Type for the names in every position or bench.
using position_names = std::array<names, static_cast< std::size_t >( E_PLAYER_POSITION::FW ) + 2>;

//! Type for the position weights
using position_weights = std::array<double, std::tuple_size_v<position_names>>;

} // futsim::football::CLineupTypes namespace