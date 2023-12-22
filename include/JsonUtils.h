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

//! Concept for a type that can be converted to JSON
template<typename T> concept is_jsonable = requires { T::JSON_KEY; }&& requires ( T aT )
{
	{ aT.ToJSON() } -> std::convertible_to<nlohmann::json>;
};

/**
 * @brief Helper function to get a value from a certain key in a JSON array.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
*/
template<typename T, is_json_type JsonType>
inline T ValueFromRequiredJSONKey( const JsonType& aJSON, const std::string_view aKeyName );

/**
 * @brief Helper function to get a value from a certain optional key in a JSON array.
 * @details Returns the default value if the key is not found.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
 * @param aDefault Value to return if key is not found.
*/
template<typename T, is_json_type JsonType>
inline T ValueFromOptionalJSONKey( const JsonType& aJSON, const std::string_view aKeyName, const T& aDefault = T{} );

/**
 * @brief Helper function to construct a jsonable class from a JSON node.
 * @details The class requires to be constructible from a json type and any other set of arguments.
 * @param aJSON JSON object.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
*/
template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON, auto&&... aArgs );

/**
 * @brief Helper function to construct a jsonable class from a string JSON node.
 * @details The class requires to be constructible from a json type and any other set of arguments.
 * @param aJSONString JSON string.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
*/
template<is_json_constructible T>
inline T ValueFromJSONString( const std::string_view& aJSONString, auto&&... aArgs );

/**
 * @brief Helper function to add a jsonable class to a JSON object.
 * @param aJSON JSON object.
 * @param aValue Value to add.
*/
template<is_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSON( JsonType& aJSON, const T& aValue ) noexcept;

template<typename T, is_json_type JsonType>
inline T ValueFromRequiredJSONKey( const JsonType& aJSON, const std::string_view aKeyName )
{
	return aJSON.at( aKeyName ).template get<T>();
}

template<typename T, is_json_type JsonType>
inline T ValueFromOptionalJSONKey( const JsonType& aJSON, const std::string_view aKeyName, const T& aDefault )
{
	const auto& found = aJSON.find( aKeyName );
	return found != aJSON.cend() ? ( *found ).template get<T>() : aDefault;
}

template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON, auto&&... aArgs )
{
	return T{ aJSON.at( T::JSON_KEY ), std::forward<decltype( aArgs )>( aArgs )... };
}

template<is_json_constructible T>
inline T ValueFromJSONString( const std::string_view& aJSONString, auto&&... aArgs )
{
	return ValueFromJSON<T>( nlohmann::json::parse( aJSONString ), std::forward<decltype( aArgs )>( aArgs )... );
}

template<is_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSON( JsonType& aJSON, const T& aValue ) noexcept
{
	aJSON[ T::JSON_KEY ] = aValue.ToJSON();
	return aJSON;
}

} //futsim namespace