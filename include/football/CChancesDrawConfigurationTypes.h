#pragma once

#include <nlohmann/json.hpp>
#include "CEnumDistribution.h"

namespace futsim::football::CChancesDrawConfigurationTypes
{

//! Enumeration for the different set piece types.
enum class E_SET_PIECE_TYPE {
	PENALTY,
	DIRECT_FREE_KICK,
	INDIRECT_FREE_KICK,
};

//! Type for the set piece type draw.
using set_piece_type_draw_distribution = CEnumDistribution<E_SET_PIECE_TYPE>;

NLOHMANN_JSON_SERIALIZE_ENUM( E_SET_PIECE_TYPE, {
	{E_SET_PIECE_TYPE::PENALTY, "Penalty"},
	{E_SET_PIECE_TYPE::DIRECT_FREE_KICK, "Direct free kick"},
	{E_SET_PIECE_TYPE::INDIRECT_FREE_KICK, "Indirect free kick"},
	} );

} // futsim::football::CChancesDrawConfigurationTypes namespace