#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

//! Concept to check that a given type is a supported json type.
template<typename T> concept is_json_type = std::convertible_to <T, nlohmann::json>;

//! Concept for a type that can be constructed from a JSON object.
template<typename T> concept is_json_constructible = std::is_constructible_v<T, nlohmann::json>;

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
template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON, auto&&... aArgs );

/**
 * @brief Helper function to construct a non-jsonable type from a JSON object.
 * @param aJSON JSON object.
*/
template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON );

/**
 * @brief Helper function to construct a jsonable class under a key in a JSON object.
 * @param aJSON JSON object.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
 * @param aKeyName Name of the key to search.
*/
template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromRequiredJSONKey( const JsonType& aJSON, auto&&... aArgs, const std::string_view aKeyName = T::JSON_KEY );

/**
 * @brief Helper function to construct a non-jsonable type under a key in a JSON object.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
*/
template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromRequiredJSONKey( const JsonType& aJSON, const std::string_view aKeyName );

/**
 * @brief Helper function to construct a jsonable class under an optional key in a JSON object.
 * @param aJSON JSON object.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
 * @param aKeyName Name of the key to search.
 * @param aDefaultValue Default value is key is not found.
*/
template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromOptionalJSONKey( const JsonType& aJSON, auto&&... aArgs, const std::string_view aKeyName = T::JSON_KEY, const T& aDefaultValue = T{} );

/**
 * @brief Helper function to construct a non-jsonable type under an optional key in a JSON object.
 * @param aJSON JSON object.
 * @param aKeyName Name of the key to search.
 * @param aDefaultValue Default value is key is not found.
*/
template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromOptionalJSONKey( const JsonType& aJSON, const std::string_view aKeyName, const T& aDefaultValue = T{} );

/**
 * @brief Helper function to construct a jsonable class from a JSON string.
 * @param aJSONString JSON string.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
*/
template<is_json_constructible T>
inline T ValueFromJSONString( const std::string_view& aJSONString, auto&&... aArgs );

/**
 * @brief Helper function to construct a non-jsonable type from a JSON string.
 * @param aJSONString JSON string.
*/
template<is_not_json_constructible T>
inline T ValueFromJSONString( const std::string_view& aJSONString );

/**
 * @brief Helper function to construct a jsonable class from a key in a JSON string.
 * @param aJSONString JSON string.
 * @param aArgs Extra arguments to be forwarded to the JSON constructor.
 * @param aKeyName Name of the key to search.
*/
template<is_json_constructible T>
inline T ValueFromJSONKeyString( const std::string_view& aJSONString, auto&&... aArgs, const std::string_view aKeyName = T::JSON_KEY );

/**
 * @brief Helper function to construct a non-jsonable type from a key in a JSON string.
 * @param aJSONString JSON string.
 * @param aKeyName Name of the key to search.
*/
template<is_not_json_constructible T>
inline T ValueFromJSONKeyString( const std::string_view& aJSONString, const std::string_view aKeyName );

/**
 * @brief Helper function to add a jsonable object to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
template<is_jsonable T, is_json_type JsonType>
inline void AddToJSON( JsonType& aJSON, const T& aObject, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a non-jsonable type to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
*/
template<is_not_jsonable T, is_json_type JsonType>
inline void AddToJSON( JsonType& aJSON, const T& aObject ) noexcept;

/**
 * @brief Helper function to add a container to a JSON object.
 * @param aJSON JSON object.
 * @param aContainer Container to add.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
template<is_json_type JsonType>
inline void AddArrayToJSON( JsonType& aJSON, const auto& aContainer, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a container with keys to a JSON object.
 * @param aJSON JSON object.
 * @param aContainer Container to add.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
template<is_json_type JsonType>
inline void AddKeyArrayToJSON( JsonType& aJSON, const auto& aContainer, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a jsonable class to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
 * @param aKeyName Name of the key under which to add it.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
template<is_jsonable T, is_json_type JsonType>
inline void AddToJSONKey( JsonType& aJSON, const T& aObject, auto&&... aArgs, const std::string_view aKeyName = T::JSON_KEY ) noexcept;

/**
 * @brief Helper function to add a non-jsonable type to a JSON object.
 * @param aJSON JSON object.
 * @param aObject Value to add.
 * @param aKeyName Name of the key under which to add it.
*/
template<is_not_jsonable T, is_json_type JsonType>
inline void AddToJSONKey( JsonType& aJSON, const T& aObject, const std::string_view aKeyName ) noexcept;

/**
 * @brief Helper function to add a container with keys to a JSON object.
 * @param aJSON JSON object.
 * @param aContainer Container to add.
 * @param aKeyName Name of the key under which to add it.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
template<is_json_type JsonType>
inline void AddArrayToJSONKey( JsonType& aJSON, const auto& aContainer, const std::string_view aKeyName, auto&&... aArgs ) noexcept;

/**
 * @brief Helper function to add a container with keys to a JSON object.
 * @param aJSON JSON object.
 * @param aContainer Container to add.
 * @param aKeyName Name of the key under which to add it.
 * @param aArgs Arguments to be forwarded to the ToJSON method.
*/
template<is_json_type JsonType>
inline void AddKeyArrayToJSONKey( JsonType& aJSON, const auto& aContainer, const std::string_view aKeyName, auto&&... aArgs ) noexcept;

template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON, auto&&... aArgs )
{
	return T( aJSON, std::forward<decltype( aArgs )>( aArgs )... );
}

template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON )
{
	return aJSON.template get<T>();
}

template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromRequiredJSONKey( const JsonType& aJSON, auto&&... aArgs, const std::string_view aKeyName )
{
	return ValueFromJSON<T>( aJSON.at( aKeyName ), std::forward<decltype( aArgs )>( aArgs )... );
}

template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromRequiredJSONKey( const JsonType& aJSON, const std::string_view aKeyName )
{
	return ValueFromJSON<T>( aJSON.at( aKeyName ) );
}

template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromOptionalJSONKey( const JsonType& aJSON, auto&&... aArgs, const std::string_view aKeyName, const T& aDefaultValue )
{
	const auto& found = aJSON.find( aKeyName );
	return found != aJSON.cend() ? ValueFromJSON<T>( *found, std::forward<decltype( aArgs )>( aArgs )... ) : aDefaultValue;
}

template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromOptionalJSONKey( const JsonType& aJSON, const std::string_view aKeyName, const T& aDefaultValue )
{
	const auto& found = aJSON.find( aKeyName );
	return found != aJSON.cend() ? ValueFromJSON<T>( *found ) : aDefaultValue;
}

template<is_json_constructible T>
inline T ValueFromJSONString( const std::string_view& aJSONString, auto&&... aArgs )
{
	return ValueFromJSON<T>( nlohmann::json::parse( aJSONString ), std::forward<decltype( aArgs )>( aArgs )... );
}

template<is_not_json_constructible T>
inline T ValueFromJSONString( const std::string_view& aJSONString )
{
	return ValueFromJSON<T>( nlohmann::json::parse( aJSONString ) );
}

template<is_json_constructible T>
inline T ValueFromJSONKeyString( const std::string_view& aJSONString, auto&&... aArgs, const std::string_view aKeyName )
{
	return ValueFromRequiredJSONKey<T>( nlohmann::json::parse( aJSONString ), std::forward<decltype( aArgs )>( aArgs )..., aKeyName );
}

template<is_not_json_constructible T>
inline T ValueFromJSONKeyString( const std::string_view& aJSONString, const std::string_view aKeyName )
{
	return ValueFromRequiredJSONKey<T>( nlohmann::json::parse( aJSONString ), aKeyName );
}

template<is_jsonable T, is_json_type JsonType>
inline void AddToJSON( JsonType& aJSON, const T& aObject, auto&&... aArgs ) noexcept
{
	aObject.ToJSON( aJSON, std::forward<decltype( aArgs )>( aArgs )... );
}

template<is_not_jsonable T, is_json_type JsonType>
inline void AddToJSON( JsonType& aJSON, const T& aObject ) noexcept
{
	aJSON = aObject;
}

template<is_json_type JsonType>
inline void AddArrayToJSON( JsonType& aJSON, const auto& aContainer, auto&&... aArgs ) noexcept
{
	JsonType arrayJSON;
	for( const auto& element : aContainer )
	{
		JsonType elementJSON;
		AddToJSON( elementJSON, element, std::forward<decltype( aArgs )>( aArgs )... );
		arrayJSON.push_back( elementJSON );
	}
	AddToJSON( aJSON, arrayJSON );
}

template<is_json_type JsonType>
inline void AddKeyArrayToJSON( JsonType& aJSON, const auto& aContainer, auto&&... aArgs ) noexcept
{
	JsonType arrayJSON;
	for( const auto& element : aContainer )
	{
		JsonType elementJSON;
		AddToJSONKey( elementJSON, element, std::forward<decltype( aArgs )>( aArgs )... );
		arrayJSON.push_back( elementJSON );
	}
	AddToJSON( aJSON, arrayJSON );
}

template<is_jsonable T, is_json_type JsonType>
inline void AddToJSONKey( JsonType& aJSON, const T& aObject, auto&&... aArgs, const std::string_view aKeyName ) noexcept
{
	AddToJSON( aJSON[ aKeyName ], aObject, std::forward<decltype( aArgs )>( aArgs )... );
}

template<is_not_jsonable T, is_json_type JsonType>
inline void AddToJSONKey( JsonType& aJSON, const T& aObject, const std::string_view aKeyName ) noexcept
{
	AddToJSON( aJSON[ aKeyName ], aObject );
}

template<is_json_type JsonType>
inline void AddArrayToJSONKey( JsonType& aJSON, const auto& aContainer, const std::string_view aKeyName, auto&&... aArgs ) noexcept
{
	AddArrayToJSON( aJSON[ aKeyName ], aContainer, std::forward<decltype( aArgs )>( aArgs )... );
}

template<is_json_type JsonType>
inline void AddKeyArrayToJSONKey( JsonType& aJSON, const auto& aContainer, const std::string_view aKeyName, auto&&... aArgs ) noexcept
{
	AddKeyArrayToJSON( aJSON[ aKeyName ], aContainer, std::forward<decltype( aArgs )>( aArgs )... );
}

} //futsim namespace