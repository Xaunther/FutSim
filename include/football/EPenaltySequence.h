#pragma once

#include <nlohmann/json.hpp>

namespace futsim::football
{

//! Enumeration for the penalty sequence.
enum class E_PENALTY_SEQUENCE {
	AB,
	ABBA
};

NLOHMANN_JSON_SERIALIZE_ENUM( E_PENALTY_SEQUENCE, {
	{E_PENALTY_SEQUENCE::AB, "AB"},
	{E_PENALTY_SEQUENCE::ABBA, "ABBA"},
	} )

} // futsim namespace