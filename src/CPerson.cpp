#include "CPerson.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NameUtils.h"

namespace futsim
{

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
	mNationality( ValueFromRequiredJSONKey<E_NATIONALITY>( aJSON, JSON_NATIONALITY ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player from JSON." )

void CPerson::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mFirstName, JSON_FIRST_NAME );
	AddToJSONKey( aJSON, mSurnames, JSON_SURNAMES );
	if( mKnownName != mSurnames )
		AddToJSONKey( aJSON, mKnownName, JSON_KNOWN_NAME );
	AddToJSONKey( aJSON, mAge, JSON_AGE );
	AddToJSONKey( aJSON, mNationality, JSON_NATIONALITY );
}

std::string_view CPerson::GetFirstName() const noexcept
{
	return mFirstName;
}

std::string_view CPerson::GetSurnames() const noexcept
{
	return mSurnames;
}

std::string_view CPerson::GetKnownName() const noexcept
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

}  // futsim namespace