#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPlayState;
}

template <> struct json_traits<football::CPlayState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Play state";
	//! JSON key for the \copybrief football::CPlayState::mChancesStates
	static inline constexpr std::string_view CHANCES_KEY = "Chances";
};

} // futsim namespace
