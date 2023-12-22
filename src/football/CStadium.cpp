#include "football/CStadium.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim
{

namespace football
{

namespace
{

/**
 * @brief Checks correctness of stadium name.
 * @param aName Stadium name.
*/
const std::string_view CheckName( const std::string_view aName );

/**
 * @brief Checks correctness of the ambient factor.
 * @param aAmbientFactor Ambient factor.
*/
const CStadiumTypes::ambient_factor& CheckAmbientFactor( const CStadiumTypes::ambient_factor& aAmbientFactor );

} // anonymous namespace

CStadium::CStadium(
	const std::string_view aName,
	const capacity aCapacity,
	const ambient_factor aAmbientFactor
) try :
	mName( CheckName( aName ) ),
	mCapacity( aCapacity ),
	mAmbientFactor( CheckAmbientFactor( aAmbientFactor ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the stadium." )

CStadium::CStadium( const json& aJSON ) try :
	mName( CheckName( ValueFromRequiredJSONKey<std::string>( aJSON, JSON_NAME ) ) ),
	mCapacity( ValueFromRequiredJSONKey<capacity>( aJSON, JSON_CAPACITY ) ),
	mAmbientFactor( CheckAmbientFactor( ValueFromRequiredJSONKey<ambient_factor>( aJSON, JSON_AMBIENT_FACTOR ) ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the stadium from JSON." )

CStadium::json CStadium::JSON() const noexcept
{
	json result;

	AddToJSONKey( result, mName, JSON_NAME );
	AddToJSONKey( result, mCapacity, JSON_CAPACITY );
	AddToJSONKey( result, mAmbientFactor, JSON_AMBIENT_FACTOR );

	return result;
}

const std::string_view CStadium::GetName() const noexcept
{
	return mName;
}

const CStadium::capacity& CStadium::GetCapacity() const noexcept
{
	return mCapacity;
}

const CStadium::ambient_factor& CStadium::GetAmbientFactor() const noexcept
{
	return mAmbientFactor;
}

namespace
{

const std::string_view CheckName( const std::string_view aName ) try
{
	if( aName.empty() )
		throw std::invalid_argument( "The stadium name cannot be empty." );
	return aName;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the stadium name." )

const CStadiumTypes::ambient_factor& CheckAmbientFactor( const CStadiumTypes::ambient_factor& aAmbientFactor ) try
{
	if( aAmbientFactor < 0 )
		throw std::invalid_argument( "The ambient factor cannot be negative." );
	return aAmbientFactor;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the ambient factor." )

} // anonymous namespace

} // football namespace

} // futsim namespace