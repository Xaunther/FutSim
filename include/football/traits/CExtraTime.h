#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include "types/CPlayTime.h"
#include "football/types/CPlayTime.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CExtraTime;
}

template <> struct default_traits<football::CExtraTime>
{
protected:
	using period_count = types::CPlayTime::period_count;
	using subs_count = football::types::CPlayTime::subs_count;
public:
	//! Default \copybrief football::CExtraTime::mPeriodTime
	static inline constexpr period_count PERIOD_TIME = 15;
	//! Default \copybrief football::CExtraTime::mAvailableSubs
	static inline constexpr subs_count AVAILABLE_SUBS = 1;
};

template <> struct json_traits<football::CExtraTime>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Extra time";
};

} // futsim namespace
