#pragma once

#include <optional>
#include <variant>

#include "types/CPerson.h"
#include "football/types/CChancesDrawConfiguration.h"

namespace futsim::football::types::CChanceState
{

//! Chance type, either open play or set piece.
using chance_type = std::variant<CChancesDrawConfiguration::E_CHANCE_TYPE, CChancesDrawConfiguration::E_SET_PIECE_TYPE>;

// Optional name.
using optional_name = std::optional<futsim::types::CPerson::name_type>;

} // futsim::football::types::CChanceState namespace