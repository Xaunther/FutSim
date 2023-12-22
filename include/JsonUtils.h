#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

//! Concept to check that a given type is a supported json type.
template<typename T> concept is_json_type = std::convertible_to <T, nlohmann::json>;

//! Concept for a type that has a JSON_KEY member.
template<typename T> concept has_json_key = requires { T::JSON_KEY; };

//! Concept for a type that can be constructed from a JSON object.
template<typename T> concept is_json_constructible = std::is_constructible_v<T, nlohmann::json>&& has_json_key<T>;

//! Concept for a type that cannot be constructed from a JSON object.
template<typename T> concept is_not_json_constructible = std::is_constructible_v<T, nlohmann::json> == false || has_json_key<T> == false;

//! Concept for a type that has a ToJson method.
template<typename T> concept has_to_json = requires ( T aT )
{
	{ aT.ToJSON() } -> std::convertible_to<nlohmann::json>;
};

//! Concept for a type that can be converted to JSON.
template<typename T> concept is_jsonable = has_json_key<T> && has_to_json<T>;

//! Concept for a type that cannot be converted to JSON.
template<typename T> concept is_not_jsonable = ( has_json_key<T> == false || has_to_json<T> == false );

template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON, auto&&... aArgs );

template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON );

template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromRequiredJSONKey( const JsonType& aJSON, auto&&... aArgs, const std::string_view aKeyName = T::JSON_KEY );

template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromRequiredJSONKey( const JsonType& aJSON, const std::string_view aKeyName );

template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromOptionalJSONKey( const JsonType& aJSON, auto&&... aArgs, const std::string_view aKeyName = T::JSON_KEY, const T& aDefaultValue = T{} );

template<is_not_json_constructible T, is_json_type JsonType>
inline T ValueFromOptionalJSONKey( const JsonType& aJSON, const std::string_view aKeyName, const T& aDefaultValue = T{} );

template<is_json_constructible T>
inline T ValueFromJSONString( const std::string_view& aJSONString, auto&&... aArgs );

template<is_not_json_constructible T>
inline T ValueFromJSONString( const std::string_view& aJSONString );

template<is_json_constructible T>
inline T ValueFromJSONKeyString( const std::string_view& aJSONString, auto&&... aArgs, const std::string_view aKeyName = T::JSON_KEY );

template<is_not_json_constructible T>
inline T ValueFromJSONKeyString( const std::string_view& aJSONString, const std::string_view aKeyName );

template<is_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSON( JsonType& aJSON, const T& aObject ) noexcept;

template<is_not_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSON( JsonType& aJSON, const T& aObject ) noexcept;

template<is_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSONKey( JsonType& aJSON, const T& aObject, const std::string_view aKeyName = T::JSON_KEY ) noexcept;

template<is_not_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSONKey( JsonType& aJSON, const T& aObject, const std::string_view aKeyName ) noexcept;







template<is_json_constructible T, is_json_type JsonType>
inline T ValueFromJSON( const JsonType& aJSON, auto&&... aArgs )
{
	return T{ aJSON, std::forward<decltype( aArgs )>( aArgs )... };
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
inline JsonType& AddToJSON( JsonType& aJSON, const T& aObject ) noexcept
{
	return aJSON = aObject.ToJSON();
}

template<is_not_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSON( JsonType& aJSON, const T& aObject ) noexcept
{
	return aJSON = aObject;
}

template<is_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSONKey( JsonType& aJSON, const T& aObject, const std::string_view aKeyName ) noexcept
{
	return AddToJSON( aJSON[ aKeyName ], aObject );
}

template<is_not_jsonable T, is_json_type JsonType>
inline JsonType& AddToJSONKey( JsonType& aJSON, const T& aObject, const std::string_view aKeyName ) noexcept
{
	return AddToJSON( aJSON[ aKeyName ], aObject );
}

} //futsim namespace