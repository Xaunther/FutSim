#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPlayer;
}

template <> struct json_traits<football::CPlayer>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Player";
};

} // futsim namespace
