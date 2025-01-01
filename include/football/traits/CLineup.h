#pragma once

#include "traits/json.h"

#include "football/EPlayerPosition.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CLineup;
}

template <> struct json_traits<football::CLineup>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Lineup";
	//! JSON key for a position
	template <football::E_PLAYER_POSITION tPlayerPosition> static inline constexpr std::string_view POSITION_KEY{};
	//! JSON key for the substitutes.
	static inline constexpr std::string_view SUBS_KEY = "Subs";
};

template <> inline constexpr std::string_view json_traits<football::CLineup>::POSITION_KEY<football::E_PLAYER_POSITION::GK> = "GK";
template <> inline constexpr std::string_view json_traits<football::CLineup>::POSITION_KEY<football::E_PLAYER_POSITION::DF> = "DFs";
template <> inline constexpr std::string_view json_traits<football::CLineup>::POSITION_KEY<football::E_PLAYER_POSITION::DM> = "DMs";
template <> inline constexpr std::string_view json_traits<football::CLineup>::POSITION_KEY<football::E_PLAYER_POSITION::MF> = "MFs";
template <> inline constexpr std::string_view json_traits<football::CLineup>::POSITION_KEY<football::E_PLAYER_POSITION::AM> = "AMs";
template <> inline constexpr std::string_view json_traits<football::CLineup>::POSITION_KEY<football::E_PLAYER_POSITION::FW> = "FWs";

} // futsim namespace
