#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CStadium;
}

template <> struct json_traits<football::CStadium>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Stadium";
	//! JSON key for the \copybrief football::CStadium::mName
	static inline constexpr std::string_view NAME_KEY = "Name";
	//! JSON key for the \copybrief football::CStadium::mCapacity
	static inline constexpr std::string_view CAPACITY_KEY = "Capacity";
	//! JSON key for the \copybrief football::CStadium::mAmbientFactor
	static inline constexpr std::string_view AMBIENT_FACTOR_KEY = "Ambient factor";
};

} // futsim namespace

