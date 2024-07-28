#include "football/CStadium.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NameUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Checks correctness of the ambient factor.
 * @param aAmbientFactor Ambient factor.
*/
const types::CStadium::ambient_factor& CheckAmbientFactor( const types::CStadium::ambient_factor& aAmbientFactor );

} // anonymous namespace

CStadium::CStadium(
	const std::string_view aName,
	const capacity aCapacity,
	const ambient_factor aAmbientFactor
) try :
	mName( CheckName( aName, "stadium name" ) ),
	mCapacity( aCapacity ),
	mAmbientFactor( CheckAmbientFactor( aAmbientFactor ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the stadium." )

CStadium::CStadium( const json& aJSON ) try :
	mName( CheckName( ValueFromRequiredJSONKey<std::string>( aJSON, json_traits<CStadium>::NAME ), "stadium name" ) ),
	mCapacity( ValueFromRequiredJSONKey<capacity>( aJSON, json_traits<CStadium>::CAPACITY ) ),
	mAmbientFactor( CheckAmbientFactor( ValueFromRequiredJSONKey<ambient_factor>( aJSON, json_traits<CStadium>::AMBIENT_FACTOR ) ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the stadium from JSON." )

void CStadium::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mName, json_traits<CStadium>::NAME );
	AddToJSONKey( aJSON, mCapacity, json_traits<CStadium>::CAPACITY );
	AddToJSONKey( aJSON, mAmbientFactor, json_traits<CStadium>::AMBIENT_FACTOR );
}

std::string_view CStadium::GetName() const noexcept
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

const types::CStadium::ambient_factor& CheckAmbientFactor( const types::CStadium::ambient_factor& aAmbientFactor ) try
{
	if( aAmbientFactor < 0 )
		throw std::invalid_argument( "The ambient factor cannot be negative." );
	return aAmbientFactor;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the ambient factor." )

} // anonymous namespace

} // futsim::football namespace