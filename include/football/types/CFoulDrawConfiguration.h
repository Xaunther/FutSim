#pragma once

#include "EnumUtils.h"

namespace futsim
{

template<typename tEnum, typename tIntType> class CEnumDistribution;

namespace football::types::CFoulDrawConfiguration
{

//! Enumeration for the different foul draw outcomes.
enum class E_FOUL_DRAW_OUTCOME {
	YELLOW_CARD,
	RED_CARD,
	NO_CARD,
};

//! Type for the foul draw.
using foul_draw_distribution = CEnumDistribution<E_FOUL_DRAW_OUTCOME, int>;

FUTSIM_SERIALIZE_ENUM( E_FOUL_DRAW_OUTCOME, {
	{E_FOUL_DRAW_OUTCOME::YELLOW_CARD, "Yellow card"},
	{E_FOUL_DRAW_OUTCOME::RED_CARD, "Red card"},
	{E_FOUL_DRAW_OUTCOME::NO_CARD, "No card"},
	} );

} // football::types::CFoulDrawConfiguration namespace

} // futsim