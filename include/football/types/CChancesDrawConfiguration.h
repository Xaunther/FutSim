#pragma once

#include "EnumUtils.h"

namespace futsim
{

template<typename tEnum, typename tIntType> class CEnumDistribution;

namespace football::types::CChancesDrawConfiguration
{

//! Enumeration for the different set piece types.
enum class E_SET_PIECE_TYPE {
	PENALTY,
	DIRECT_FREE_KICK,
	INDIRECT_FREE_KICK,
};

//! Enumeration for the different chance types.
enum class E_CHANCE_TYPE {
	CORNER,
	ONE_ON_ONE_VS_GK,
	ONE_ON_ONE_VS_DF,
	NEAR_SHOT,
	FAR_SHOT,
};

//! Type for the set piece type draw.
using set_piece_type_draw_distribution = CEnumDistribution<E_SET_PIECE_TYPE, int>;
//! Type for the chance type draw.
using chance_type_draw_distribution = CEnumDistribution<E_CHANCE_TYPE, int>;

FUTSIM_SERIALIZE_ENUM( E_SET_PIECE_TYPE, {
	{E_SET_PIECE_TYPE::PENALTY, "Penalty"},
	{E_SET_PIECE_TYPE::DIRECT_FREE_KICK, "Direct free kick"},
	{E_SET_PIECE_TYPE::INDIRECT_FREE_KICK, "Indirect free kick"},
	} );

FUTSIM_SERIALIZE_ENUM( E_CHANCE_TYPE, {
	{E_CHANCE_TYPE::CORNER, "Corner"},
	{E_CHANCE_TYPE::ONE_ON_ONE_VS_GK, "1 on 1 vs GK"},
	{E_CHANCE_TYPE::ONE_ON_ONE_VS_DF, "1 on 1 vs DF"},
	{E_CHANCE_TYPE::NEAR_SHOT, "Near shot"},
	{E_CHANCE_TYPE::FAR_SHOT, "Far shot"},
	} );

} // football::types::CChancesDrawConfiguration namespace

} // futsim namespace