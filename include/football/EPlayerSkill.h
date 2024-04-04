#pragma once

#include "EnumUtils.h"

namespace futsim::football
{

//! Macro to do something for each player skill.
#define FOR_EACH_PLAYER_SKILL(DO, ...) \
    DO(St, "St", __VA_ARGS__) \
    DO(Tk, "Tk", __VA_ARGS__) \
    DO(Ps, "Ps", __VA_ARGS__) \
    DO(Sh, "Sh", __VA_ARGS__) \

//! Enumeration for the different player skills.
enum class E_PLAYER_SKILL {
	FOR_EACH_PLAYER_SKILL( FUTSIM_LIST_ENUM )
};

FUTSIM_SERIALIZE_ENUM( E_PLAYER_SKILL, {
	FOR_EACH_PLAYER_SKILL( FUTSIM_LIST_ENUM_ID, E_PLAYER_SKILL )
	} )

} // futsim::football namespace