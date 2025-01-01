#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPossessionState;
}

template <> struct json_traits<football::CPossessionState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Possession state";
	//! JSON key for the \copybrief football::CPossessionState::mOutcome
	static inline constexpr std::string_view OUTCOME_KEY = "Outcome";
	//! JSON key for the \copybrief football::CPossessionState::mTackler
	static inline constexpr std::string_view TACKLER_KEY = "Tackler";
	//! JSON key for the \copybrief football::CPossessionState::mPasser
	static inline constexpr std::string_view PASSER_KEY = "Passer";
};

} // futsim namespace
