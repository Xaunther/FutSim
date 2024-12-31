#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CTeam;
}

template <> struct json_traits<football::CTeam>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Team";
	//! JSON key for the \copybrief football::CTeam::mName
	static inline constexpr std::string_view NAME_KEY = "Name";
	//! JSON key for the \copybrief football::CTeam::mAbbreviation
	static inline constexpr std::string_view ABBREVIATION_KEY = "Abbreviation";
	//! JSON key for the \copybrief football::CTeam::mManager
	static inline constexpr std::string_view MANAGER_KEY = "Manager";
	//! JSON key for the \copybrief football::CTeam::mPlayers
	static inline constexpr std::string_view PLAYERS_KEY = "Players";
	//! JSON key for the \copybrief football::CTeam::mSupportFactor
	static inline constexpr std::string_view SUPPORT_FACTOR_KEY = "Support factor";
	//! JSON key for the mean attendance.
	static inline constexpr std::string_view MEAN_ATTENDANCE_KEY = "Mean attendance";
	//! JSON key for the standard deviation of the attendance.
	static inline constexpr std::string_view STD_DEV_ATTENDANCE_KEY = "StdDev attendance";
};

} // futsim namespace

