#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

template<typename tEnum, typename tIntType> class CEnumDistribution;

namespace football::CPossessionDrawConfigurationTypes
{

//! Enumeration for the different possession draw outcomes.
enum class E_POSSESSION_DRAW_OUTCOME {
	KEEP_POSSESSION,
	FOUL,
	COUNTER_ATTACK,
};

//! Type for the possession draw.
using possession_draw_distribution = CEnumDistribution<E_POSSESSION_DRAW_OUTCOME, int>;

NLOHMANN_JSON_SERIALIZE_ENUM( E_POSSESSION_DRAW_OUTCOME, {
	{E_POSSESSION_DRAW_OUTCOME::KEEP_POSSESSION, "Keep possession"},
	{E_POSSESSION_DRAW_OUTCOME::FOUL, "Foul"},
	{E_POSSESSION_DRAW_OUTCOME::COUNTER_ATTACK, "Counter attack"},
	} );

} // football::CPossessionDrawConfigurationTypes namespace

} // futsim namespace