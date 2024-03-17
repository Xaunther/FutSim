#pragma once

#include <nlohmann/json.hpp>
#include "CEnumDistribution.h"

namespace futsim::football::CFoulDrawConfigurationTypes
{

//! Enumeration for the different foul draw outcomes.
enum class E_FOUL_DRAW_OUTCOME {
	YELLOW_CARD,
	RED_CARD,
	NO_CARD,
};

//! Type for the foul draw.
using foul_draw_distribution = CEnumDistribution<E_FOUL_DRAW_OUTCOME>;

NLOHMANN_JSON_SERIALIZE_ENUM( E_FOUL_DRAW_OUTCOME, {
	{E_FOUL_DRAW_OUTCOME::YELLOW_CARD, "Yellow card"},
	{E_FOUL_DRAW_OUTCOME::RED_CARD, "Red card"},
	{E_FOUL_DRAW_OUTCOME::NO_CARD, "No card"},
	} );

} // futsim::football::CFoulDrawConfigurationTypes namespace