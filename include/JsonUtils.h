#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

//! Checks whether the given type is a supported json type.
template<class T> struct is_json : std::bool_constant<
	std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, nlohmann::ordered_json> ||
	std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, nlohmann::json>> {};

//! Helper value template.
template<class T> inline constexpr bool is_json_v = is_json<T>::value;

/**
 * @brief Helper function to get a value from a certain key in a JSON array.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
*/
template<typename T>
T ValueFromRequiredJSONKey( const auto& aJSON, const std::string_view aKeyName );

/**
 * @brief Helper function to get a value from a certain optional key in a JSON array.
 * @details Returns the default value if the key is not found.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
 * @param aDefault Value to return if key is not found.
*/
template<typename T>
T ValueFromOptionalJSONKey( const auto& aJSON, const std::string_view aKeyName, const T& aDefault = T{} );

template<typename T>
T ValueFromRequiredJSONKey( const auto& aJSON, const std::string_view aKeyName )
{
	static_assert( is_json_v<decltype( aJSON )>, "The type of the JSON object is not supported." );
	return aJSON.at( aKeyName ).template get<T>();
}

template<typename T>
T ValueFromOptionalJSONKey( const auto& aJSON, const std::string_view aKeyName, const T& aDefault )
{
	static_assert( is_json_v<decltype( aJSON )>, "The type of the JSON object is not supported." );
	const auto& found = aJSON.find( aKeyName );
	return found != aJSON.cend() ? ( *found ).template get<T>() : aDefault;
}

} //futsim namespace