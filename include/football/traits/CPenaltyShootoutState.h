#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPenaltyShootoutState;
}

template <> struct json_traits<football::CPenaltyShootoutState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Penalty shootout state";
	//! JSON key for the \copybrief football::CPenaltyShootoutState::mPenalties
	static inline constexpr std::string_view PENALTIES_KEY = "Penalties";
	//! JSON key to indicate if the penalty corresponds to the home team.
	static inline constexpr std::string_view HOME_TEAM_PENALTY_KEY = "Home team penalty";
};

} // futsim namespace
