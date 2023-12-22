#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

//! Concept to check that a given type is a supported json type.
template<typename T> concept is_json_type =
std::is_same_v<T, nlohmann::ordered_json> ||
std::is_same_v<T, nlohmann::json>;

//! Concept for a type that must have a JSON_KEY member.
template<typename T> concept is_json_constructible =
( std::is_constructible_v<T, nlohmann::json> || std::is_constructible_v<T, nlohmann::ordered_json> ) &&
	requires{ T::JSON_KEY; };

/**
 * @brief Helper function to get a value from a certain key in a JSON array.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
*/
template<typename T, is_json_type JsonType>
T ValueFromRequiredJSONKey( const JsonType& aJSON, const std::string_view aKeyName );

/**
 * @brief Helper function to get a value from a certain optional key in a JSON array.
 * @details Returns the default value if the key is not found.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
 * @param aDefault Value to return if key is not found.
*/
template<typename T, is_json_type JsonType>
T ValueFromOptionalJSONKey( const JsonType& aJSON, const std::string_view aKeyName, const T& aDefault = T{} );

/**
 * @brief Helper function to construct a jsonable class from a JSON node.
 * @details The class requires to have a json key defined in an accesible JSON_KEY member
 * @param aJSON JSON object.
*/
template<is_json_constructible T, is_json_type JsonType> T ValueFromJSON( const JsonType& aJSON );

template<typename T, is_json_type JsonType>
T ValueFromRequiredJSONKey( const JsonType& aJSON, const std::string_view aKeyName )
{
	return aJSON.at( aKeyName ).template get<T>();
}

template<typename T, is_json_type JsonType>
T ValueFromOptionalJSONKey( const JsonType& aJSON, const std::string_view aKeyName, const T& aDefault )
{
	const auto& found = aJSON.find( aKeyName );
	return found != aJSON.cend() ? ( *found ).template get<T>() : aDefault;
}

template<is_json_constructible T, is_json_type JsonType> T ValueFromJSON( const JsonType& aJSON )
{
	return T{ aJSON.at( T::JSON_KEY ) };
}

} //futsim namespace