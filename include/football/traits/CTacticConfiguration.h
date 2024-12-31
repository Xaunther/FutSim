#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include <string_view>

#include "football/types/CTacticConfiguration.h"

namespace futsim
{

namespace football
{
class CTacticConfiguration;
}

template <> struct default_traits<football::CTacticConfiguration>
{
protected:
	using position_penalties = football::types::CTacticConfiguration::position_penalties;
public:
	//! Default \copybrief football::CTacticConfiguration::mPositionPenalties
	static inline constexpr position_penalties POSITION_PENALTIES = { 0, -0.2, -0.4 };
};

template <> struct json_traits<football::CTacticConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Tactic configuration";
	//! JSON key for the \copybrief football::CTacticConfiguration::mTkBonus
	static inline constexpr std::string_view TK_BONUS_KEY = "Tk bonus";
	//! JSON key for the \copybrief football::CTacticConfiguration::mPsBonus
	static inline constexpr std::string_view PS_BONUS_KEY = "Ps bonus";
	//! JSON key for the \copybrief football::CTacticConfiguration::mFavourableTactics
	static inline constexpr std::string_view FAVOURABLE_TACTICS_KEY = "Favourable tactics";
	//! JSON key for the \copybrief football::CTacticConfiguration::mPositionPenalties
	static inline constexpr std::string_view POSITION_PENALTIES_KEY = "Position penalties";
};

} // futsim namespace
