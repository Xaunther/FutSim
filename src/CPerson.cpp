#include "CPerson.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NationalityUtils.h"

namespace futsim
{

namespace
{

/**
 * @brief Checks correctness of the ability
 * @param aSkill Skill value.
 * @param aNameString String with the name label to add to the error message.
*/
const std::string_view CheckName( const std::string_view aName, const std::string_view aNameString );

} // anonymous namespace

CPerson::CPerson(
	const std::string_view aFirstName,
	const std::string_view aSurnames,
	const std::string_view aKnownName,
	const unsigned short& aAge,
	const E_NATIONALITY& aNationality
) try :
	mFirstName( CheckName( aFirstName, "name" ) ),
	mSurnames( CheckName( aSurnames, "surnames" ) ),
	mKnownName( aKnownName.empty() ? mSurnames : CheckName( aKnownName, "known name" ) ),
	mAge( aAge ),
	mNationality( aNationality )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player." )

CPerson::CPerson( const json& aJSON ) try :
	mFirstName( CheckName( ValueFromRequiredJSONKey<std::string>( aJSON, JSON_FIRST_NAME ), "name" ) ),
	mSurnames( CheckName( ValueFromRequiredJSONKey<std::string>( aJSON, JSON_SURNAMES ), "surnames" ) ),
	mKnownName( ValueFromOptionalJSONKey<std::string>( aJSON, JSON_KNOWN_NAME, mSurnames ) ),
	mAge( ValueFromRequiredJSONKey<unsigned short>( aJSON, JSON_AGE ) ),
	mNationality( ToNationality( ValueFromRequiredJSONKey<std::string_view>( aJSON, JSON_NATIONALITY ) ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player from JSON." )

CPerson::json CPerson::JSON() const noexcept
{
	json result;

	result[ JSON_FIRST_NAME ] = mFirstName;
	result[ JSON_SURNAMES ] = mSurnames;
	if( mKnownName != mSurnames )
		result[ JSON_KNOWN_NAME ] = mKnownName;
	result[ JSON_AGE ] = mAge;
	result[ JSON_NATIONALITY ] = ToString( mNationality );

	return result;
}

const std::string_view CPerson::GetFirstName() const noexcept
{
	return mFirstName;
}

const std::string_view CPerson::GetSurnames() const noexcept
{
	return mSurnames;
}

const std::string_view CPerson::GetKnownName() const noexcept
{
	return mKnownName;
}

const unsigned short& CPerson::GetAge() const noexcept
{
	return mAge;
}

const E_NATIONALITY& CPerson::GetNationality() const noexcept
{
	return mNationality;
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

} // anonymous namespace

}  // futsim namespace