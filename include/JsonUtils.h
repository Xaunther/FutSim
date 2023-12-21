#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

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
	return aJSON.at( aKeyName ).template get<T>();
}

template<typename T>
T ValueFromOptionalJSONKey( const auto& aJSON, const std::string_view aKeyName, const T& aDefault )
{
	const auto& found = aJSON.find( aKeyName );
	return found != aJSON.cend() ? ( *found ).template get<T>() : aDefault;
}

} //futsim namespace