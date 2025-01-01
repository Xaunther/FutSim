#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPeriodStates;
}

template <> struct json_traits<football::CPeriodStates>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Period states";
};

} // futsim namespace
