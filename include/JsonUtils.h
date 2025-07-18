#pragma once

#include <nlohmann/json.hpp>

#include "traits/json.h"

namespace futsim
{

//! Concept to check that a given type is a supported json type.
template<typename T> concept is_json_type = std::convertible_to <T, nlohmann::json>;

//! Concept for a type that can be constructed from a JSON object.
template<typename T, typename... Args> concept is_json_constructible = std::is_constructible_v<T, nlohmann::json, Args...>;

//! Concept for a type that cannot be constructed from a JSON object.
template<typename T> concept is_not_json_constructible = is_json_constructible<T> == false;

//! Concept for a type that can be converted to JSON.
template<typename T> concept is_jsonable = requires ( T aT, nlohmann::json aJSON )
{
	aT.ToJSON( aJSON );
} || requires ( T aT, nlohmann::ordered_json aJSON )
{
	aT.ToJSON( aJSON );
};

//! Concept for a type that cannot be converted to JSON.
template<typename T> concept is_not_jsonable = is_jsonable<T> == false;

/**
 * @brief Helper function to construct a jsonable class from a JSON object.
 * @param aJSON JSON object.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
*/
template<typename T, typename ...Args>
inline T ValueFromJSON( const is_json_type auto& aJSON, Args&&... aArgs ) requires is_json_constructible<T, Args...>;

/**
 * @brief Helper function to construct a non-jsonable type from a JSON object.
 * @param aJSON JSON object.
*/
template<is_not_json_constructible T>
inline T ValueFromJSON( const is_json_type auto& aJSON );

/**
 * @brief Helper function to construct a class under a key in a JSON object.
 * @param aJSON JSON object.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
 * @param aKeyName Name of the key to search.
*/
template<typename T>
inline T ValueFromRequiredJSONKey( const is_json_type auto& aJSON, const std::string_view aKeyName = json_traits<T>::KEY, auto&&... aArgs );

/**
 * @brief Helper function to construct a jsonable class under an optional key in a JSON object.
 * @param aJSON JSON object.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
 * @param aKeyName Name of the key to search.
 * @param aDefaultValue Default value is key is not found.
*/
template<typename T, typename ...Args>
inline T ValueFromOptionalJSONKey( const is_json_type auto& aJSON, const std::string_view aKeyName = json_traits<T>::KEY,
		const T& aDefaultValue = T{}, Args&&... aArgs ) requires is_json_constructible<T, Args...>;

/**
 * @brief Helper function to construct a non-jsonable type under an optional key in a JSON object.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
 * @param aDefaultValue Default value is key is not found.
*/
template<is_not_json_constructible T>
inline T ValueFromOptionalJSONKey( const is_json_type auto& aJSON, const std::string_view aKeyName, const T& aDefaultValue = T{} );

/**
 * @brief Helper function to construct a class from a JSON string.
 * @param aJSONString JSON string.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
*/
template<typename T>
inline T ValueFromJSONString( const std::string_view& aJSONString, auto&&... aArgs );

/**
 * @brief Helper function to construct a class from a key in a JSON string.
 * @param aJSONString JSON string.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
 * @param aKeyName Name of the key to search.
*/
template<typename T>
inline T ValueFromJSONKeyString( const std::string_view& aJSONString, const std::string_view aKeyName = json_traits<T>::KEY, auto&&... aArgs );

/**
 * @brief Helper function to add a jsonable object to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
inline void AddToJSON( is_json_type auto& aJSON, const is_jsonable auto& aObject, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a non-jsonable type to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
*/
inline void AddToJSON( is_json_type auto& aJSON, const is_not_jsonable auto& aObject ) noexcept;

/**
 * @brief Helper function to add a container to a JSON object.
 * @param aJSON JSON object.
 * @param aContainer Container to add.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
inline void AddArrayToJSON( is_json_type auto& aJSON, const auto& aContainer, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a container with keys to a JSON object.
 * @param aJSON JSON object.
 * @param aContainer Container to add.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
inline void AddKeyArrayToJSON( is_json_type auto& aJSON, const auto& aContainer, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a jsonable class to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
 * @param aKeyName Name of the key under which to add it.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
inline void AddToJSONKey( is_json_type auto& aJSON, const auto& aObject,
		const std::string_view aKeyName = json_traits<std::decay_t<decltype( aObject )>>::KEY, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add an optional key to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
 * @param aKeyName Name of the key under which to add it.
 * @param aIgnoreValue Value for which the key is not created.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
template<typename T>
inline void AddToOptionalJSONKey( is_json_type auto& aJSON, const T& aObject, const std::string_view aKeyName = json_traits<T>::KEY, const T& aIgnoreValue = T{}, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a container with keys to a JSON object.
 * @param aJSON JSON object.
 * @param aContainer Container to add.
 * @param aKeyName Name of the key under which to add it.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
inline void AddArrayToJSONKey( is_json_type auto& aJSON, const auto& aContainer, const std::string_view aKeyName, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a container with keys to a JSON object.
 * @param aJSON JSON object.
 * @param aContainer Container to add.
 * @param aKeyName Name of the key under which to add it.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
inline void AddKeyArrayToJSONKey( is_json_type auto& aJSON, const auto& aContainer, const std::string_view aKeyName, auto&&... aArgs ) noexcept;

template<typename T, typename ...Args>
inline T ValueFromJSON( const is_json_type auto& aJSON, Args&&... aArgs ) requires is_json_constructible<T, Args...>
{
	return T( aJSON, std::forward<decltype( aArgs )>( aArgs )... );
}

template<is_not_json_constructible T>
inline T ValueFromJSON( const is_json_type auto& aJSON )
{
	return aJSON.template get<T>();
}

template<typename T>
inline T ValueFromRequiredJSONKey( const is_json_type auto& aJSON, const std::string_view aKeyName, auto&&... aArgs )
{
	return ValueFromJSON<T>( aJSON.at( aKeyName ), std::forward<decltype( aArgs )>( aArgs )... );
}

template<typename T, typename ...Args>
inline T ValueFromOptionalJSONKey( const is_json_type auto& aJSON, const std::string_view aKeyName,
		const T& aDefaultValue, Args&&... aArgs ) requires is_json_constructible<T, Args...>
{
	const auto& found = aJSON.find( aKeyName );
	return found != aJSON.cend() ? ValueFromJSON<T>( *found, std::forward<decltype( aArgs )>( aArgs )... ) : aDefaultValue;
}

template<is_not_json_constructible T>
inline T ValueFromOptionalJSONKey( const is_json_type auto& aJSON, const std::string_view aKeyName, const T& aDefaultValue )
{
	const auto& found = aJSON.find( aKeyName );
	return found != aJSON.cend() ? ValueFromJSON<T>( *found ) : aDefaultValue;
}

template<typename T>
inline T ValueFromJSONString( const std::string_view& aJSONString, auto&&... aArgs )
{
	return ValueFromJSON<T>( nlohmann::json::parse( aJSONString ), std::forward<decltype( aArgs )>( aArgs )... );
}

template<typename T>
inline T ValueFromJSONKeyString( const std::string_view& aJSONString, const std::string_view aKeyName, auto&&... aArgs )
{
	return ValueFromRequiredJSONKey<T>( nlohmann::json::parse( aJSONString ), aKeyName, std::forward<decltype( aArgs )>( aArgs )... );
}

inline void AddToJSON( is_json_type auto& aJSON, const is_jsonable auto& aObject, auto&&... aArgs ) noexcept
{
	aObject.ToJSON( aJSON, std::forward<decltype( aArgs )>( aArgs )... );
}

inline void AddToJSON( is_json_type auto& aJSON, const is_not_jsonable auto& aObject ) noexcept
{
	aJSON = aObject;
}

inline void AddArrayToJSON( is_json_type auto& aJSON, const auto& aContainer, auto&&... aArgs ) noexcept
{
	std::decay_t<decltype( aJSON )> arrayJSON;
	for( const auto& element : aContainer )
	{
		decltype( arrayJSON ) elementJSON;
		AddToJSON( elementJSON, element, std::forward<decltype( aArgs )>( aArgs )... );
		arrayJSON.push_back( std::move( elementJSON ) );
	}
	AddToJSON( aJSON, arrayJSON );
}

inline void AddKeyArrayToJSON( is_json_type auto& aJSON, const auto& aContainer, auto&&... aArgs ) noexcept
{
	std::decay_t<decltype( aJSON )> arrayJSON;
	for( const auto& element : aContainer )
	{
		decltype( arrayJSON ) elementJSON;
		AddToJSONKey( elementJSON, element, std::forward<decltype( aArgs )>( aArgs )... );
		arrayJSON.push_back( std::move( elementJSON ) );
	}
	AddToJSON( aJSON, arrayJSON );
}

inline void AddToJSONKey( is_json_type auto& aJSON, const auto& aObject, const std::string_view aKeyName, auto&&... aArgs ) noexcept
{
	AddToJSON( aJSON[ aKeyName ], aObject, std::forward<decltype( aArgs )>( aArgs )... );
}

template<typename T>
inline void AddToOptionalJSONKey( is_json_type auto& aJSON, const T& aObject, const std::string_view aKeyName, const T& aIgnoreValue, auto&&... aArgs ) noexcept
{
	if( aObject != aIgnoreValue )
		AddToJSONKey( aJSON, aObject, aKeyName, std::forward<decltype( aArgs )>( aArgs )... );
}

inline void AddArrayToJSONKey( is_json_type auto& aJSON, const auto& aContainer, const std::string_view aKeyName, auto&&... aArgs ) noexcept
{
	AddArrayToJSON( aJSON[ aKeyName ], aContainer, std::forward<decltype( aArgs )>( aArgs )... );
}

inline void AddKeyArrayToJSONKey( is_json_type auto& aJSON, const auto& aContainer, const std::string_view aKeyName, auto&&... aArgs ) noexcept
{
	AddKeyArrayToJSON( aJSON[ aKeyName ], aContainer, std::forward<decltype( aArgs )>( aArgs )... );
}

} //futsim namespace
