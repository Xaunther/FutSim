#pragma once

#include <array>
#include <set>
#include <string>

namespace futsim::football::CTacticConfigurationTypes
{

//! Type for a skill bonus.
using skill_bonus = double;
//! Type for an array of skill bonuses.
using skill_bonuses = std::array<skill_bonus, 3>;
//! Type for a tactic ID.
using id = std::string;
//! Type for a set of tactic IDs.
using ids = std::set<id>;

} // futsim::football::CTacticConfigurationTypes namespace