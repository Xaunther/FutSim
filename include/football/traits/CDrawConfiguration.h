#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CDrawConfiguration;
}

template <> struct json_traits<football::CDrawConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Draw configuration";
};

} // futsim namespace
