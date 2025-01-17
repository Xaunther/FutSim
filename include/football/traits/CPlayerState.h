#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPlayerState;
}

template <> struct json_traits<football::CPlayerState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Player state";
	//! JSON key for the \copybrief football::CPlayerState::mMinutesPlayed
	static inline constexpr std::string_view MINUTES_PLAYED_KEY = "Minutes played";
	//! JSON key for the \copybrief football::CPlayerState::mSaves
	static inline constexpr std::string_view SAVES_KEY = "Saves";
	//! JSON key for the \copybrief football::CPlayerState::mTackles
	static inline constexpr std::string_view TACKLES_KEY = "Tackles";
	//! JSON key for the \copybrief football::CPlayerState::mPasses
	static inline constexpr std::string_view PASSES_KEY = "Passes";
	//! JSON key for the \copybrief football::CPlayerState::mShots
	static inline constexpr std::string_view SHOTS_KEY = "Shots";
	//! JSON key for the \copybrief football::CPlayerState::mAssists
	static inline constexpr std::string_view ASSISTS_KEY = "Assists";
	//! JSON key for the \copybrief football::CPlayerState::mGoals
	static inline constexpr std::string_view GOALS_KEY = "Goals";
	//! JSON key for the \copybrief football::CPlayerState::mFoulsCommitted
	static inline constexpr std::string_view FOULS_COMMITTED = "Fouls committed";
	//! JSON key for the \copybrief football::CPlayerState::mYellowCards
	static inline constexpr std::string_view YELLOW_CARDS_KEY = "Yellow cards";
	//! JSON key for the \copybrief football::CPlayerState::mRedCards
	static inline constexpr std::string_view RED_CARDS_KEY = "Red cards";
};

} // futsim namespace
