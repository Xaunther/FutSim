#include "CPlayTime.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim
{

namespace
{

/**
 * @brief Checks that a number is not zero.
 * @param aNumber Number.
 * @param aNameString String with the name label to add to the error message.
*/
template<typename T> const T& CheckNonZero( const T& aNumber, const std::string_view aNameString );

} // anonymous namespace

CPlayTime::CPlayTime(
	const period_count& aPeriodCount,
	const period_time& aPeriodTime
) try :
	mPeriodCount( CheckNonZero( aPeriodCount, "number of periods" ) ),
	mPeriodTime( CheckNonZero( aPeriodTime, "length of the period" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the play time." )

CPlayTime::CPlayTime( const json& aJSON ) try :
	mPeriodCount( CheckNonZero( ValueFromRequiredJSONKey<period_count>( aJSON, JSON_PERIOD_COUNT ), "number of periods" ) ),
	mPeriodTime( CheckNonZero( ValueFromRequiredJSONKey<period_time>( aJSON, JSON_PERIOD_TIME ), "length of the period" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the play time from JSON." )

namespace
{

template<typename T> const T& CheckNonZero( const T& aNumber, const std::string_view aNameString ) try
{
	if( aNumber == 0 )
		throw std::invalid_argument{ "The " + std::string( aNameString.data() ) + " cannot be zero." };
	return aNumber;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aNameString << "." )

} // anonymous namespace

} // futsim namespace