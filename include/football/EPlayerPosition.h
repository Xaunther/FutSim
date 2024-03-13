#pragma once

#include <nlohmann/json.hpp>

namespace futsim::football
{

//! Enumeration for the different player positions.
enum class E_PLAYER_POSITION {
	GK,
	DF,
	DM,
	MF,
	AM,
	FW,
};

NLOHMANN_JSON_SERIALIZE_ENUM( E_PLAYER_POSITION, {
	{E_PLAYER_POSITION::GK, "GK"},
	{E_PLAYER_POSITION::DF, "DF"},
	{E_PLAYER_POSITION::DM, "DM"},
	{E_PLAYER_POSITION::MF, "MF"},
	{E_PLAYER_POSITION::AM, "AM"},
	{E_PLAYER_POSITION::FW, "FW"},
	} )

} // futsim::football namespace