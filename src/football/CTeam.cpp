#include "football/CTeam.h"

#include "football/CLineup.h"

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
std::string_view CheckAbbreviation( const std::string_view aAbbreviation );

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
types::CTeam::players CreatePlayersFromJSON( const futsim::types::IJsonable::json& aJSON );

/**
 * @brief Create the player name - roster index map.
 * @param aPlayers Players.
*/
types::CTeam::name_index_map CreateNameIndexMap( const types::CTeam::players& aPlayers );

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
	mNameIndexMap( CreateNameIndexMap( mPlayers ) ),
	mSupportFactor( CheckPositiveness( aSupportFactor, "support factor" ) ),
	mAttendanceDistributionParameters( CheckNonNegativeness( aMeanAttendance, "mean attendance" ),
		CheckPositiveness( aStdDevAttendance, "standard deviation of the attendance" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team." )

CTeam::CTeam( const json& aJSON ) try :
	mName( CheckName( ValueFromRequiredJSONKey<name_type>( aJSON, NAME_KEY ), "name" ) ),
	mAbbreviation( CheckAbbreviation( ValueFromRequiredJSONKey<name_type>( aJSON, ABBREVIATION_KEY ) ) ),
	mManager( CheckName( ValueFromRequiredJSONKey<name_type>( aJSON, MANAGER_KEY ), "manager name" ) ),
	mPlayers( CreatePlayersFromJSON( aJSON ) ),
	mNameIndexMap( CreateNameIndexMap( mPlayers ) ),
	mSupportFactor( CheckPositiveness( ValueFromRequiredJSONKey<support_factor>( aJSON, SUPPORT_FACTOR_KEY ), "support factor" ) ),
	mAttendanceDistributionParameters( CheckNonNegativeness( ValueFromRequiredJSONKey<double>( aJSON, MEAN_ATTENDANCE_KEY ), "mean attendance" ),
		CheckPositiveness( ValueFromRequiredJSONKey<double>( aJSON, STD_DEV_ATTENDANCE_KEY ), "standard deviation of the attendance" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team from JSON." )

void CTeam::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mName, NAME_KEY );
	AddToJSONKey( aJSON, mAbbreviation, ABBREVIATION_KEY );
	AddToJSONKey( aJSON, mManager, MANAGER_KEY );
	if( !mPlayers.empty() )
		AddArrayToJSONKey( aJSON, mPlayers, PLAYERS_KEY );
	AddToJSONKey( aJSON, mSupportFactor, SUPPORT_FACTOR_KEY );
	AddToJSONKey( aJSON, mAttendanceDistributionParameters.mean(), MEAN_ATTENDANCE_KEY );
	AddToJSONKey( aJSON, mAttendanceDistributionParameters.stddev(), STD_DEV_ATTENDANCE_KEY );
}

std::string_view CTeam::GetName() const noexcept
{
	return mName;
}

std::string_view CTeam::GetAbbreviation() const noexcept
{
	return mAbbreviation;
}

std::string_view CTeam::GetManager() const noexcept
{
	return mManager;
}

std::span<const CPlayer> CTeam::GetPlayers() const noexcept
{
	return mPlayers;
}

const CPlayer& CTeam::GetPlayer( const std::string_view aKnownName ) const try
{
	return mPlayers[ mNameIndexMap.at( aKnownName.data() ) ];
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, aKnownName << " is not in " << mName + "'s list of players." )

const CTeam::support_factor& CTeam::GetSupportFactor() const noexcept
{
	return mSupportFactor;
}

CTeam::attendance_distribution::param_type CTeam::GetAttendanceDistributionParameters() const noexcept
{
	return mAttendanceDistributionParameters;
}

CTeam::attendance CTeam::GenerateAttendance( std::uniform_random_bit_generator auto& aGenerator ) const noexcept
{
	auto result = attendance_distribution( mAttendanceDistributionParameters )( aGenerator );
	return result < 0 ? 0 : std::lround( result );
}

const CLineup& CTeam::CheckLineup( const CLineup& aLineup ) const try
{
	std::ranges::for_each( aLineup.CreatePlayersView<true>(), [ this ]( const auto& aPlayer )
	{
		GetPlayer( aPlayer );
	} );
	return aLineup;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the lineup against the team." )

namespace
{

std::string_view CheckAbbreviation( const std::string_view aAbbreviation ) try
{
	if( aAbbreviation.size() != 3 )
		throw std::invalid_argument{ "The abbreviation must contain 3 characters, not " + std::to_string( aAbbreviation.size() ) + "." };
	if( std::regex_search( aAbbreviation.data(), std::basic_regex{ "[^A-Z]", std::regex_constants::icase } ) )
		throw std::invalid_argument{ "The abbreviation can only contain letters from A to Z." };
	return aAbbreviation;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the abbreviation." )

types::CTeam::players CreatePlayersFromJSON( const futsim::types::IJsonable::json& aJSON ) try
{
	types::CTeam::players result;
	for( const auto& JSONPlayer : ValueFromOptionalJSONKey<futsim::types::IJsonable::json>( aJSON, json_traits<CTeam>::PLAYERS_KEY ) )
		result.emplace_back( ValueFromJSON<types::CTeam::players::value_type>( JSONPlayer ) );
	return result;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the players from JSON." )

types::CTeam::name_index_map CreateNameIndexMap( const types::CTeam::players& aPlayers ) try
{
	types::CTeam::name_index_map result;

	for( const auto& player : aPlayers )
		if( !result.emplace( player.GetKnownName(), result.size() ).second )
			throw std::invalid_argument{ "There are two players with the same known name '" + std::string{ player.GetKnownName() } + "'." };

	return result;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the map of player names." )

} // anonymous namespace

} // futsim::football namespace
