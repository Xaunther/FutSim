#include "football/CTeam.h"

#include "ExceptionUtils.h"

#include <regex>

namespace futsim
{

namespace football
{

namespace
{

/**
 * @brief Checks correctness of the name.
 * @param aName Name.
 * @param aNameString String with the name label to add to the error message.
*/
const std::string_view CheckName( const std::string_view aName, const std::string_view aNameString );

/**
 * @brief Checks correctness of the abbreviation.
 * @param aAbbreviation Abbreviation.
*/
const std::string_view CheckAbbreviation( const std::string_view aAbbreviation );

/**
 * @brief Checks positiveness of a number.
 * @param aNumber Number to check.
 * @param aNumberDescription Number description to add to the error message.
*/
template <typename T> const T& CheckPositiveness( const T& aNumber, const std::string_view aNumberDescription );

/**
 * @brief Checks non-negativeness of a number.
 * @param aNumber Number to check.
 * @param aNumberDescription Number description to add to the error message.
*/
template <typename T> const T& CheckNonNegativeness( const T& aNumber, const std::string_view aNumberDescription );

} // anonymous namespace

CTeam::CTeam(
	const std::string_view aName,
	const std::string_view aAbbreviation,
	const std::string_view aManager,
	const players& aPlayers,
	const support_factor& aSupportFactor,
	const double& aMeanAttendance,
	const double& aStdDevAttendance
) try :
	mName( CheckName( aName, "name" ) ),
	mAbbreviation( CheckAbbreviation( aAbbreviation ) ),
	mManager( CheckName( aManager, "manager name" ) ),
	mPlayers( aPlayers ),
	mSupportFactor( CheckPositiveness( aSupportFactor, "support factor" ) ),
	mAttendanceDistribution( CheckNonNegativeness( aMeanAttendance, "mean attendance" ),
		CheckPositiveness( aStdDevAttendance, "standard deviation of fans willing to attend the match" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team." )

namespace
{

const std::string_view CheckName( const std::string_view aName, const std::string_view aNameString ) try
{
	if( aName.empty() )
		throw std::invalid_argument{ "The " + std::string( aNameString.data() ) + " cannot be empty." };
	return aName;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aNameString << "." )

const std::string_view CheckAbbreviation( const std::string_view aAbbreviation ) try
{
	if( aAbbreviation.size() != 3 )
		throw std::invalid_argument{ "The abbreviation must contain 3 characters, not " + std::to_string( aAbbreviation.size() ) + "." };
	if( std::regex_search( aAbbreviation.data(), std::basic_regex{ "[^A-Z]", std::regex_constants::icase } ) )
		throw std::invalid_argument{ "The abbreviation can only contain letters from A to Z." };
	return aAbbreviation;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the abbreviation." )

template <typename T> const T& CheckPositiveness( const T& aNumber, const std::string_view aNumberDescription ) try
{
	if( aNumber <= T{} )
		throw std::invalid_argument{ "The " + std::string( aNumberDescription.data() ) + " must be positive." };
	return aNumber;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aNumberDescription << "." )

template <typename T> const T& CheckNonNegativeness( const T& aNumber, const std::string_view aNumberDescription ) try
{
	if( aNumber < T{} )
		throw std::invalid_argument{ "The " + std::string( aNumberDescription.data() ) + " must be non-negative." };
	return aNumber;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aNumberDescription << "." )

} // anonymous namespace

} // football namespace

} // futsim namespace