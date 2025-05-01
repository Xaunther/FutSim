#pragma once

#include "EnumUtils.h"

namespace futsim::football
{


//! Macro to do something for each player position.
#define FOR_EACH_PLAYER_POSITION(DO, ...) \
    DO(GK, "GK", __VA_ARGS__) \
    DO(DF, "DF", __VA_ARGS__) \
    DO(DM, "DM", __VA_ARGS__) \
    DO(MF, "MF", __VA_ARGS__) \
    DO(AM, "AM", __VA_ARGS__) \
    DO(FW, "FW", __VA_ARGS__) \

//! Enumeration for the different player positions.
enum class E_PLAYER_POSITION {
	FOR_EACH_PLAYER_POSITION( FUTSIM_LIST_ENUM )
};

// NOLINTBEGIN(*-avoid-c-arrays)
FUTSIM_SERIALIZE_ENUM( E_PLAYER_POSITION, {
	FOR_EACH_PLAYER_POSITION( FUTSIM_LIST_ENUM_ID, E_PLAYER_POSITION )
	} )
// NOLINTEND(*-avoid-c-arrays)

} // futsim::football namespace
