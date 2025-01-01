#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include "football/types/CDrawConfiguration.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CFoulDrawConfiguration;
}

template <> struct default_traits<football::CFoulDrawConfiguration>
{
protected:
	using stat = football::types::CDrawConfiguration::stat;
public:
	//! Default \copybrief football::CFoulDrawConfiguration::mAverageFouls
	static inline constexpr stat AVERAGE_FOULS = stat{ 8195 } / 380;
	//! Default \copybrief football::CFoulDrawConfiguration::mAverageYellowCards
	static inline constexpr stat AVERAGE_YELLOW_CARDS = stat{ 1375 } / 380;
	//! Default \copybrief football::CFoulDrawConfiguration::mAverageRedCards
	static inline constexpr stat AVERAGE_RED_CARDS = stat{ 31 } / 380;
};

template <> struct json_traits<football::CFoulDrawConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Foul draw configuration";
	//! JSON key for the \copybrief football::CFoulDrawConfiguration::mAverageFouls
	static inline constexpr std::string_view AVERAGE_FOULS_KEY = "Average fouls";
	//! JSON key for the \copybrief football::CFoulDrawConfiguration::mAverageYellowCards
	static inline constexpr std::string_view AVERAGE_YELLOW_CARDS_KEY = "Average yellow cards";
	//! JSON key for the \copybrief football::CFoulDrawConfiguration::mAverageRedCards
	static inline constexpr std::string_view AVERAGE_RED_CARDS_KEY = "Average red cards";
};

} // futsim namespace
