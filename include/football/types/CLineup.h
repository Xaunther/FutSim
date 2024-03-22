#pragma once

#include "CPersonTypes.h"

#include "football/EPlayerPosition.h"

#include <array>
#include <functional>
#include <span>
#include <vector>

namespace futsim::football::types::CLineup
{

//! Type for a name.
using name = CPersonTypes::name_type;

//! Type for a vector of names.
using names = std::vector<name>;

//! Type for the position weights.
using position_weights = std::array<double, static_cast< std::size_t >( E_PLAYER_POSITION::FW ) + 2>;

//! Type for the list of players by position.
template<E_PLAYER_POSITION tPlayerPosition> using players =
std::conditional_t<tPlayerPosition == E_PLAYER_POSITION::GK, std::string_view, std::span<const name>>;

//! Type for an indexed predicate.
using player_predicate = std::function<void( const name& )>;

} // futsim::football::types::CLineup namespace