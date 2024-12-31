#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CMatchConfiguration;
}

template <> struct default_traits<football::CMatchConfiguration>
{
	//! Default \copybrief football::CMatchConfiguration::mApplyAmbientFactor
	static inline constexpr bool APPLY_AMBIENT_FACTOR = true;
};

template <> struct json_traits<football::CMatchConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Match configuration";
	//! JSON key for the \copybrief football::CMatchConfiguration::mApplyAmbientFactor
	static inline constexpr std::string_view APPLY_AMBIENT_FACTOR_KEY = "Apply ambient factor";
};

} // futsim namespace
