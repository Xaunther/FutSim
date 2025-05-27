#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

class CPlayTime;

template <> struct json_traits<CPlayTime>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Play time";
	//! JSON key for the \copybrief CPlayTime::mPeriodCount
	static inline constexpr std::string_view PERIOD_COUNT_KEY = "Period count";
	//! JSON key for the \copybrief CPlayTime::mPeriodTime
	static inline constexpr std::string_view PERIOD_TIME_KEY = "Period time";
};

} // futsim namespace
