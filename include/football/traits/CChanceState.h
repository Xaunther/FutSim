#pragma once

#include "traits/json.h"

#include <string_view>

#include "football/EPlayerSkill.h"

namespace futsim
{

namespace football
{
class CChanceState;
}

template <> struct json_traits<football::CChanceState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Chance state";
	//! JSON key for the \copybrief football::CChanceState::mChanceType
	static inline constexpr std::string_view CHANCE_TYPE_KEY = "Chance type";
	//! JSON key for the \copybrief football::CChanceState::mOutcome
	static inline constexpr std::string_view OUTCOME_KEY = "Outcome";
	/**
	 * @brief JSON key template for the actor.
	 * @tparam tPlayerSkill Skill used by the actor.
	*/
	template<football::E_PLAYER_SKILL tPlayerSkill> static inline constexpr std::string_view ACTOR{};
};

template <> inline constexpr std::string_view json_traits<football::CChanceState>::ACTOR<football::E_PLAYER_SKILL::St> = "Goalkeeper";
template <> inline constexpr std::string_view json_traits<football::CChanceState>::ACTOR<football::E_PLAYER_SKILL::Tk> = "Tackler";
template <> inline constexpr std::string_view json_traits<football::CChanceState>::ACTOR<football::E_PLAYER_SKILL::Ps> = "Passer";
template <> inline constexpr std::string_view json_traits<football::CChanceState>::ACTOR<football::E_PLAYER_SKILL::Sh> = "Shooter";

} // futsim namespace
