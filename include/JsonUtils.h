#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

//! Concept to check that a given type is a supported json type.
template<typename T> concept is_json_type = std::convertible_to <T, nlohmann::json>;

//! Concept for a type that has a JSON_KEY member.
template<typename T> concept has_json_key = requires { T::JSON_KEY; };

//! Concept for a type that must have a JSON_KEY member.
template<typename T> concept is_json_constructible = std::is_constructible_v<T, nlohmann::json>&&
has_json_key<T>;

//! Concept for a type that has a ToJson method.
template<typename T> concept has_to_json = requires ( T aT )
{
	{ aT.ToJSON() } -> std::convertible_to<nlohmann::json>;
};

//! Concept for a type that can be converted to JSON.
template<typename T> concept is_jsonable = has_json_key<T> && has_to_json<T>;

//! Concept for a type that cannot be converted to JSON.
template<typename T> concept is_not_jsonable = ( has_json_key<T> == false || has_to_json<T> == false );

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
 * @brief Helper function to add a jsonable object to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
 * @param aKeyName Name of the key.
*/
template<is_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSON( JsonType& aJSON, const T& aObject, const std::string_view aKeyName = T::JSON_KEY ) noexcept;

/**
 * @brief Helper function to add a value to a key in a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
 * @param aKeyName Name of the key.
*/
template<is_not_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSON( JsonType& aJSON, const T& aObject, const std::string_view aKeyName ) noexcept;

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
inline JsonType& AddToJSON( JsonType& aJSON, const T& aObject, const std::string_view aKeyName ) noexcept
{
	return AddToJSON( aJSON, aObject.ToJSON(), aKeyName );
}

template<is_not_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSON( JsonType& aJSON, const T& aObject, const std::string_view aKeyName ) noexcept
{
	aJSON[ aKeyName ] = aObject;
	return aJSON;
}

} //futsim namespace