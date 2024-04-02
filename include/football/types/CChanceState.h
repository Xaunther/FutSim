#pragma once

#include <variant>

#include "football/types/CChancesDrawConfiguration.h"

namespace futsim::football::types::CChanceState
{

//! Chance type, either open play or set piece.
using chance_type = std::variant<CChancesDrawConfiguration::E_CHANCE_TYPE, CChancesDrawConfiguration::E_SET_PIECE_TYPE>;

} // futsim::football::types::CChanceState namespace