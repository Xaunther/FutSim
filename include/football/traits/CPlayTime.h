#pragma once

#include "traits/default.h"
#include "traits/json.h"
#include "traits/CPlayTime.h"

#include <string_view>

#include "types/CPlayTime.h"
#include "football/types/CPlayTime.h"

namespace futsim
{

namespace football
{
class CPlayTime;
}

template <> struct default_traits<football::CPlayTime>
{
private:
	using period_count = types::CPlayTime::period_count;
	using subs_count = football::types::CPlayTime::subs_count;
public:
	//! Default \copybrief football::CPlayTime::mPeriodCount
	static inline constexpr period_count PERIOD_COUNT = 2;
	//! Default \copybrief football::CPlayTime::mPeriodTime
	static inline constexpr period_count PERIOD_TIME = 45;
	//! Default \copybrief football::CPlayTime::mAvailableSubs
	static inline constexpr subs_count AVAILABLE_SUBS = 5;
};

template <> struct json_traits<football::CPlayTime> : public json_traits<CPlayTime>
{
	///! JSON key for the \copybrief football::CPlayTime::mAvailableSubs
	static inline constexpr std::string_view AVAILABLE_SUBS_KEY = "Available subs";
};

} // futsim namespace
