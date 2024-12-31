#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPeriodState;
}

template <> struct json_traits<football::CPeriodState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Period state";
	//! JSON key for the \copybrief football::CPeriodState::mPlays
	static inline constexpr std::string_view PLAYS_KEY = "Plays";
	//! JSON key to indicate if the play corresponds to the home team.
	static inline constexpr std::string_view HOME_TEAM_PLAY_KEY = "Home team play";
};

} // futsim namespace
