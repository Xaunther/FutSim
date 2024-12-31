#pragma once

#include "traits/json.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CTieCondition;
}

template <> struct json_traits<football::CTieCondition>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Tie condition";
	//! JSON key for the \copybrief football::CTieCondition::mHomeTeamLead
	static inline constexpr std::string_view HOME_TEAM_LEAD_KEY = "Home team lead";
	//! JSON key for the \copybrief football::CTieCondition::mHomeTeamGoals
	static inline constexpr std::string_view HOME_TEAM_GOALS_KEY = "Home team goals";
};

} // futsim namespace
