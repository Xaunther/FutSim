#pragma once

#include <optional>

#include "types/CPerson.h"

namespace futsim::football::types::CPossessionState
{

//! Type for an optional name.
using optional_name = std::optional<futsim::types::CPerson::name_type>;

} // futsim::football::types::CPenaltyShootoutConfiguration namespace