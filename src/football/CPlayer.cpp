#include "football/CPlayer.h"

#include "ExceptionUtils.h"
#include "NationalityUtils.h"

namespace futsim
{

namespace football
{

namespace
{

/**
 * @brief Checks correctness of the ability
 * @param aSkill Skill value.
 * @param aNameString String with the name label to add to the error message.
*/
const std::string_view CheckName( const std::string_view aName, const std::string_view aNameString );

/**
 * @brief Creates known name from JSON
 * @param aJSON JSON object.
 * @param aSurnames Surnames of the player.
*/
std::string CreateKnownName( const IJsonableTypes::json& aJSON, const std::string_view aSurnames ) noexcept;

} // anonymous namespace

CPlayer::CPlayer(
	const std::string_view aFirstName,
	const std::string_view aSurnames,
	const std::string_view aKnownName,
	const unsigned short& aAge,
	const E_NATIONALITY& aNationality,
	const CPlayerSkills& aPlayerSkills
) try :
	mFirstName( CheckName( aFirstName, "name" ) ),
	mSurnames( CheckName( aSurnames, "surnames" ) ),
	mKnownName( aKnownName.empty() ? mSurnames : CheckName( aKnownName, "known name" ) ),
	mAge( aAge ),
	mNationality( aNationality ),
	mPlayerSkills( aPlayerSkills )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player." )

CPlayer::CPlayer( const json& aJSON ) try :
	mFirstName( CheckName( aJSON.at( JSON_FIRST_NAME ), "name" ) ),
	mSurnames( CheckName( aJSON.at( JSON_SURNAMES ), "surnames" ) ),
	mKnownName( CreateKnownName( aJSON, mSurnames ) ),
	mAge( aJSON.at( JSON_AGE ) ),
	mNationality( ToNationality( aJSON.at( JSON_NATIONALITY ) ) ),
	mPlayerSkills( aJSON.at( CPlayerSkills::JSON_NAME ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player from JSON." )

CPlayer::json CPlayer::JSON() const noexcept
{
	json result;

	result[ JSON_FIRST_NAME ] = mFirstName;
	result[ JSON_SURNAMES ] = mSurnames;
	if( mKnownName != mSurnames )
		result[ JSON_KNOWN_NAME ] = mKnownName;
	result[ JSON_AGE ] = mAge;
	result[ JSON_NATIONALITY ] = ToString( mNationality );
	result[ CPlayerSkills::JSON_NAME ] = mPlayerSkills.ToJSON();

	return result;
}

namespace
{

const std::string_view CheckName( const std::string_view aName, const std::string_view aNameString ) try
{
	if( aName.empty() )
		throw std::invalid_argument{ "The " + std::string( aNameString.data() ) + " cannot be empty." };
	return aName;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aNameString << "." )

std::string CreateKnownName( const IJsonableTypes::json& aJSON, const std::string_view aSurnames ) noexcept
{
	const auto& found = aJSON.find( CPlayer::JSON_KNOWN_NAME );
	return found != aJSON.cend() ? ( *found ) : aSurnames.data();
}

} // anonymous namespace

} // football namespace

}  // futsim namespace