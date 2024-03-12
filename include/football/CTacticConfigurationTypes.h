#pragma once

#include <array>
#include <set>
#include <string>
#include "EPlayerPosition.h"
#include "EPlayerSkill.h"

namespace futsim::football::CTacticConfigurationTypes
{

//! Type for a skill bonus.
using skill_bonus = double;
//! Type for an array of skill bonuses.
template <std::size_t tSize> using skill_bonuses = std::array<skill_bonus, tSize>;
//! Type for the position penalties.
using position_penalties = skill_bonuses<static_cast< std::size_t >( E_PLAYER_SKILL::Sh )>;
//! Type for the position bonuses.
using position_bonuses = skill_bonuses<std::tuple_size_v<position_penalties>+1>;
//! Type for the bonuses table.
using bonuses_table = std::array<position_bonuses, static_cast< std::size_t >( E_PLAYER_POSITION::FW ) + 1>;
//! Type for a tactic ID.
using id = std::string;
//! Type for a set of tactic IDs.
using ids = std::set<id>;

} // futsim::football::CTacticConfigurationTypes namespace