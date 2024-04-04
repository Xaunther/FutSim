#pragma once

#include "EnumUtils.h"

namespace futsim::football
{

//! Macro to do something for each penalty sequence.
#define FOR_EACH_PENALTY_SEQUENCE(DO, ...) \
	DO(AB, "AB", __VA_ARGS__) \
	DO(ABBA, "ABBA", __VA_ARGS__) \

//! Enumeration for the penalty sequence.
enum class E_PENALTY_SEQUENCE {
	FOR_EACH_PENALTY_SEQUENCE( FUTSIM_LIST_ENUM )
};

FUTSIM_SERIALIZE_ENUM( E_PENALTY_SEQUENCE, {
	FOR_EACH_PENALTY_SEQUENCE( FUTSIM_LIST_ENUM_ID, E_PENALTY_SEQUENCE )
	} )

} // futsim namespace