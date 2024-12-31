#pragma once

#include "traits/json.h"

#include <string_view>

#include "football/EPlayerSkill.h"

namespace futsim
{

namespace football
{
class CPlayerSkills;
}

template <> struct json_traits<football::CPlayerSkills>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Player skills";
	//! JSON key for a skill.
	template <football::E_PLAYER_SKILL tPlayerSkill> static inline constexpr std::string_view SKILL_KEY{};
	//! JSON key for a skill experience.
	template <football::E_PLAYER_SKILL tPlayerSkill> static inline constexpr std::string_view XP_KEY{};
};

FOR_EACH_PLAYER_SKILL( FUTSIM_INSTANTIATE_ENUM_TRAIT, football::CPlayerSkills, SKILL_KEY, football::E_PLAYER_SKILL, " skill" )
FOR_EACH_PLAYER_SKILL( FUTSIM_INSTANTIATE_ENUM_TRAIT, football::CPlayerSkills, XP_KEY, football::E_PLAYER_SKILL, " experience" )

} // futsim namespace
