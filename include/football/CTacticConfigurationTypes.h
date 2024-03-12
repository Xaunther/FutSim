#pragma once

#include <array>
#include <set>
#include <string>
#include "EPlayerSkill.h"

namespace futsim::football::CTacticConfigurationTypes
{

//! Type for a skill bonus.
using skill_bonus = double;
//! Type for an array of skill bonuses.
template <std::size_t tSize> using skill_bonuses = std::array<skill_bonus, tSize>;
//! Type for the position penalties.
using position_penalties = skill_bonuses<static_cast< std::size_t >( E_PLAYER_SKILL::Sh )>;
//! Type for a tactic ID.
using id = std::string;
//! Type for a set of tactic IDs.
using ids = std::set<id>;

} // futsim::football::CTacticConfigurationTypes namespace