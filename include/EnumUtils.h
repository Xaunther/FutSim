#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <type_traits>
#include <nlohmann/detail/macro_scope.hpp>

namespace futsim
{

//! Macro to get the string representation of an enum.
#define FUTSIM_STRING_ENUM(ENUM_TYPE, ...) \
	inline std::string_view ToString(const ENUM_TYPE& aEnum) \
	{ \
		static_assert(std::is_enum_v<ENUM_TYPE>, #ENUM_TYPE " must be an enum!"); \
		static const struct{ ENUM_TYPE value; std::string description; } enumStrings[] = __VA_ARGS__; \
		return (*std::ranges::find_if(enumStrings, \
				[&aEnum](const auto& aEnumString){return aEnumString.value == aEnum;})).description; \
	} \

//! Macro for both JSON and string serialization.
#define FUTSIM_SERIALIZE_ENUM(ENUM_TYPE, ...) \
	FUTSIM_STRING_ENUM( ENUM_TYPE, __VA_ARGS__ ); \
	NLOHMANN_JSON_SERIALIZE_ENUM( ENUM_TYPE, __VA_ARGS__ ); \

//! Macro to list a value of an enum, comma separated.
#define FUTSIM_LIST_ENUM(name, ... ) name,

//! Macro to list a value and id of an enum, comma separated.
#define FUTSIM_LIST_ENUM_ID(name, id, ENUM_TYPE, ... ) {ENUM_TYPE::name, id},

} // futsim namespace
