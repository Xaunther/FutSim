#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CFoulState;
}

template <> struct json_traits<football::CFoulState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Foul state";
	//! JSON key for the \copybrief football::CFoulState::mCommitter
	static inline constexpr std::string_view COMMIITER_KEY = "Committer";
	//! JSON key for the \copybrief football::CFoulState::mOutcome
	static inline constexpr std::string_view OUTCOME_KEY = "Outcome";
};

} // futsim namespace
