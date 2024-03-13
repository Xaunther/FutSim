#pragma once

#include <nlohmann/json.hpp>

namespace futsim::football
{

//! Enumeration for the different player skills.
enum class E_PLAYER_SKILL {
	St,
	Tk,
	Ps,
	Sh,
};

NLOHMANN_JSON_SERIALIZE_ENUM( E_PLAYER_SKILL, {
	{E_PLAYER_SKILL::St, "St"},
	{E_PLAYER_SKILL::Tk, "Tk"},
	{E_PLAYER_SKILL::Ps, "Ps"},
	{E_PLAYER_SKILL::Sh, "Sh"},
	} )

} // futsim::football namespace