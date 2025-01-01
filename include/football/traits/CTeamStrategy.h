#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CTeamStrategy;
}

template <> struct json_traits<football::CTeamStrategy>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Team strategy";
	//! JSON key for the \copybrief football::CTeamStrategy::mTacticID
	static inline constexpr std::string_view TACTIC_KEY = "Tactic";
};

} // futsim namespace

