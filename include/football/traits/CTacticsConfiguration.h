#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include <string_view>

#include "football/types/CTacticsConfiguration.h"

#include "football/CTacticConfiguration.h"

namespace futsim
{

namespace football
{
class CTacticsConfiguration;
}

template <> struct default_traits<football::CTacticsConfiguration>
{
protected:
	using tactic_configurations = football::types::CTacticsConfiguration::tactic_configurations;
	using skill_bonus = football::types::CTacticConfiguration::skill_bonus;
public:
	//! Default \copybrief football::CTacticsConfiguration::mTacticConfigurations
	static inline tactic_configurations TACTIC_CONFIGURATIONS = {
		{ "N", football::CTacticConfiguration{ 0, 0, { "A", "E" } } },
		{ "A", football::CTacticConfiguration{ -0.5, -0.2, { "D", "E" } } },
		{ "D", football::CTacticConfiguration{ 0.7, -0.2, { "L", "P" } } },
		{ "L", football::CTacticConfiguration{ 0.3, -0.6, { "C", "N" } } },
		{ "C", football::CTacticConfiguration{ 0.5, -0.8, { "A", "P" } } },
		{ "P", football::CTacticConfiguration{ -0.2, 0.6, { "L", "N" } } },
		{ "E", football::CTacticConfiguration{ -0.3, 0.2, { "D", "C" } } }
	};

	//! Default \copybrief football::CTacticsConfiguration::mFavourableTacticSkillBonus
	static inline constexpr skill_bonus FAVOURABLE_TACTIC_SKILL_BONUS = 1.1;
};

template <> struct json_traits<football::CTacticsConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Tactics configuration";
	//! JSON key for the \copybrief football::CTacticsConfiguration::mTacticConfigurations
	static inline constexpr std::string_view TACTIC_CONFIGURATIONS_KEY = "Tactic configurations";
	//! JSON key for the \copybrief football::CTacticsConfiguration::mFavourableTacticSkillBonus
	static inline constexpr std::string_view FAVOURABLE_TACTIC_SKILL_BONUS_KEY = "Favourable tactic skill bonus";
};

} // futsim namespace
