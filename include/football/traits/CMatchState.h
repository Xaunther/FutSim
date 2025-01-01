#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CMatchState;
}

template <> struct json_traits<football::CMatchState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Match state";
	//! JSON key for the \copybrief football::CMatchState::mMandatoryPlayTimeState
	static inline constexpr std::string_view MANDATORY_PERIOD_STATES_KEY = "Mandatory time period states";
	//! JSON key for the \copybrief football::CMatchState::mExtraTimeState
	static inline constexpr std::string_view EXTRA_PERIOD_STATES_KEY = "Extra time period states";
};

} // futsim namespace
