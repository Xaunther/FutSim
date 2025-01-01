#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CMatch;
}

template <> struct json_traits<football::CMatch>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Match";
	//! JSON key for the \copybrief football::CMatch::mHomeTeam
	static inline constexpr std::string_view HOME_TEAM_KEY = "Home team";
	//! JSON key for the \copybrief football::CMatch::mAwayTeam
	static inline constexpr std::string_view AWAY_TEAM_KEY = "Away team";
	//! JSON key for the \copybrief football::CMatch::mReferee
	static inline constexpr std::string_view REFEREE_KEY = "Referee";
};

} // futsim namespace
