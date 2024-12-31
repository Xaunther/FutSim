#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include <string_view>

#include "football/types/CDrawConfiguration.h"

namespace futsim
{

namespace football
{
class CChancesDrawConfiguration;
}

template <> struct default_traits<football::CChancesDrawConfiguration>
{
protected:
	using stat = football::types::CDrawConfiguration::stat;
public:
	//! Default \copybrief football::CChancesDrawConfiguration::mAverageChances
	static inline constexpr stat AVERAGE_CHANCES = stat{ 9609 } / 380;
	//! Default \copybrief football::CChancesDrawConfiguration::mAverageCornerKicks
	static inline constexpr stat AVERAGE_CORNER_KICKS = stat{ 3830 } / 380;
	//! Default \copybrief football::CChancesDrawConfiguration::mAverage1vs1GKs
	static inline constexpr stat AVERAGE_1VS1_GKS = 2;
	//! Default \copybrief football::CChancesDrawConfiguration::mAverage1vs1DFs
	static inline constexpr stat AVERAGE_1VS1_DFS = 2.85;
	//! Default \copybrief football::CChancesDrawConfiguration::mAverageNearShots
	static inline constexpr stat AVERAGE_NEAR_SHOTS = 3;
	//! Default \copybrief football::CChancesDrawConfiguration::mAverageSetPieces
	static inline constexpr stat AVERAGE_SET_PIECES = stat{ 1545 } / 380;
	//! Default \copybrief football::CChancesDrawConfiguration::mAveragePenalties
	static inline constexpr stat AVERAGE_PENALTIES = stat{ 104 } / 380;
	//! Default \copybrief football::CChancesDrawConfiguration::mAverageDirectFreeKicks
	static inline constexpr stat AVERAGE_DIRECT_FREE_KICKS = stat{ 301 } / 380;
};

template <> struct json_traits<football::CChancesDrawConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Chances draw configuration";
	//! JSON key for the \copybrief football::CChancesDrawConfiguration::mAverageChances
	static inline constexpr std::string_view AVERAGE_CHANCES_KEY = "Average chances";
	//! JSON key for the \copybrief football::CChancesDrawConfiguration::mAverageCornerKicks
	static inline constexpr std::string_view AVERAGE_CORNER_KICKS_KEY = "Average corner kicks";
	//! JSON key for the \copybrief football::CChancesDrawConfiguration::mAverage1vs1GKs
	static inline constexpr std::string_view AVERAGE_1VS1_GKS_KEY = "Average 1 on 1 vs GK chances";
	//! JSON key for the \copybrief football::CChancesDrawConfiguration::mAverage1vs1DFs
	static inline constexpr std::string_view AVERAGE_1VS1_DFS_KEY = "Average 1 on 1 vs DF chances";
	//! JSON key for the \copybrief football::CChancesDrawConfiguration::mAverageNearShots
	static inline constexpr std::string_view AVERAGE_NEAR_SHOTS_KEY = "Average near shots";
	//! JSON key for the \copybrief football::CChancesDrawConfiguration::mAverageSetPieces
	static inline constexpr std::string_view AVERAGE_SET_PIECES_KEY = "Average set pieces";
	//! JSON key for the \copybrief football::CChancesDrawConfiguration::mAveragePenalties
	static inline constexpr std::string_view AVERAGE_PENALTIES_KEY = "Average penalties";
	//! JSON key for the \copybrief football::CChancesDrawConfiguration::mAverageDirectFreeKicks
	static inline constexpr std::string_view AVERAGE_DIRECT_FREE_KICKS_KEY = "Average direct free kicks";
};

} // futsim namespace
