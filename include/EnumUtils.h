#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

//! Macro to get the string representation of an enum.
#define FUTSIM_STRING_ENUM(ENUM_TYPE, ...) \
	inline std::string_view ToString(const ENUM_TYPE& aEnum) \
	{ \
		static_assert(std::is_enum<ENUM_TYPE>::value, #ENUM_TYPE " must be an enum!"); \
		static const std::pair<ENUM_TYPE, std::string> enumStrings[] = __VA_ARGS__; \
		return (*std::find_if(std::cbegin(enumStrings), std::cend(enumStrings), \
				[&aEnum](const auto& aEnumPair){return aEnumPair.first == aEnum;})).second; \
	} \

//! Macro for both JSON and string serialization.
#define FUTSIM_SERIALIZE_ENUM(ENUM_TYPE, ...) \
	FUTSIM_STRING_ENUM( ENUM_TYPE, __VA_ARGS__ ); \
	NLOHMANN_JSON_SERIALIZE_ENUM( ENUM_TYPE, __VA_ARGS__ ); \

//! Macro to list a value of an enum, comma separated.
#define FUTSIM_LIST_ENUM(name, ... ) name,

} // futsim namespace