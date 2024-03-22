#pragma once

#include "EPlayerSkill.h"

/**
 * @brief Types defined for \ref CPlayerSkills.
*/
namespace futsim::football::types::CPlayerSkills
{

//! Type for the skill value.
using skill_type = unsigned short;
//! Type for the experience value. 
using xp_type = unsigned short;
//! Type for the skills container.
using skills = std::array<skill_type, static_cast< std::size_t >( E_PLAYER_SKILL::Sh ) + 1>;
//! Type for the experience container.
using experiences = std::array<xp_type, static_cast< std::size_t >( E_PLAYER_SKILL::Sh ) + 1>;

} // futsim::football::types::CPlayerSkills namespace