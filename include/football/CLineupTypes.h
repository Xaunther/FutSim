#pragma once

#include "CPersonTypes.h"

#include "football/EPlayerPosition.h"

#include <array>
#include <vector>

namespace futsim::football::CLineupTypes
{

//! Type for a name.
using name = CPersonTypes::name_type;

//! Type for a vector of names.
using names = std::vector<name>;

//! Type for the position weights.
using position_weights = std::array<double, static_cast< std::size_t >( E_PLAYER_POSITION::FW ) + 2>;

} // futsim::football::CLineupTypes namespace