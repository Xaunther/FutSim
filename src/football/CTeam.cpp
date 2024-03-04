#include "football/CTeam.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NameUtils.h"
#include "NumberUtils.h"

#include <regex>

namespace futsim::football
{

namespace
{

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
const auto& CheckPositiveness( const auto& aNumber, const std::string_view aNumberDescription ) try
{
	if( aNumber <= decltype( aNumber ){} )
		throw std::invalid_argument{ "The " + std::string( aNumberDescription.data() ) + " must be positive." };
	return aNumber;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aNumberDescription << "." )

/**
 * @brief Create the players from JSON.
 * @param aJSON JSON object.
*/
CTeamTypes::players CreatePlayersFromJSON( const IJsonableTypes::json& aJSON );

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
		CheckPositiveness( aStdDevAttendance, "standard deviation of the attendance" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team." )

CTeam::CTeam( const json& aJSON ) try :
	mName( CheckName( ValueFromRequiredJSONKey<name_type>( aJSON, JSON_NAME ), "name" ) ),
	mAbbreviation( CheckAbbreviation( ValueFromRequiredJSONKey<name_type>( aJSON, JSON_ABBREVIATION ) ) ),
	mManager( CheckName( ValueFromRequiredJSONKey<name_type>( aJSON, JSON_MANAGER ), "manager name" ) ),
	mPlayers( CreatePlayersFromJSON( aJSON ) ),
	mSupportFactor( CheckPositiveness( ValueFromRequiredJSONKey<support_factor>( aJSON, JSON_SUPPORT_FACTOR ), "support factor" ) ),
	mAttendanceDistribution( CheckNonNegativeness( ValueFromRequiredJSONKey<double>( aJSON, JSON_MEAN_ATTENDANCE ), "mean attendance" ),
		CheckPositiveness( ValueFromRequiredJSONKey<double>( aJSON, JSON_STD_DEV_ATTENDANCE ), "standard deviation of the attendance" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team from JSON." )

void CTeam::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mName, JSON_NAME );
	AddToJSONKey( aJSON, mAbbreviation, JSON_ABBREVIATION );
	AddToJSONKey( aJSON, mManager, JSON_MANAGER );
	if( !mPlayers.empty() )
		AddKeyArrayToJSONKey( aJSON, mPlayers, JSON_PLAYERS );
	AddToJSONKey( aJSON, mSupportFactor, JSON_SUPPORT_FACTOR );
	AddToJSONKey( aJSON, mAttendanceDistribution.mean(), JSON_MEAN_ATTENDANCE );
	AddToJSONKey( aJSON, mAttendanceDistribution.stddev(), JSON_STD_DEV_ATTENDANCE );
}

const std::string_view CTeam::GetName() const noexcept
{
	return mName;
}

const std::string_view CTeam::GetAbbreviation() const noexcept
{
	return mAbbreviation;
}

const std::string_view CTeam::GetManager() const noexcept
{
	return mManager;
}

const CTeam::players& CTeam::GetPlayers() const noexcept
{
	return mPlayers;
}

const CTeam::support_factor& CTeam::GetSupportFactor() const noexcept
{
	return mSupportFactor;
}

double CTeam::GetMeanAttendance() const noexcept
{
	return mAttendanceDistribution.mean();
}

double CTeam::GetStdDevAttendance() const noexcept
{
	return mAttendanceDistribution.stddev();
}

CTeam::attendance CTeam::GenerateAttendance( std::uniform_random_bit_generator auto& aGenerator ) noexcept
{
	auto result = mAttendanceDistribution( aGenerator );
	return result < 0 ? 0 : std::lround( result );
}

namespace
{

const std::string_view CheckAbbreviation( const std::string_view aAbbreviation ) try
{
	if( aAbbreviation.size() != 3 )
		throw std::invalid_argument{ "The abbreviation must contain 3 characters, not " + std::to_string( aAbbreviation.size() ) + "." };
	if( std::regex_search( aAbbreviation.data(), std::basic_regex{ "[^A-Z]", std::regex_constants::icase } ) )
		throw std::invalid_argument{ "The abbreviation can only contain letters from A to Z." };
	return aAbbreviation;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the abbreviation." )

CTeamTypes::players CreatePlayersFromJSON( const IJsonableTypes::json& aJSON ) try
{
	CTeamTypes::players result;
	for( const auto& JSONPlayer : ValueFromOptionalJSONKey<IJsonableTypes::json>( aJSON, CTeam::JSON_PLAYERS ) )
		result.emplace_back( ValueFromRequiredJSONKey<CPlayer>( JSONPlayer ) );
	return result;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the players from JSON." )

} // anonymous namespace

} // futsim::football namespace