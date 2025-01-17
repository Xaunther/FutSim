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
	mFirstName( CheckName( ValueFromRequiredJSONKey<std::string>( aJSON, FIRST_NAME_KEY ), "name" ) ),
	mSurnames( CheckName( ValueFromRequiredJSONKey<std::string>( aJSON, SURNAMES_KEY ), "surnames" ) ),
	mKnownName( ValueFromOptionalJSONKey<std::string>( aJSON, KNOWN_NAME_KEY, mSurnames ) ),
	mAge( ValueFromRequiredJSONKey<unsigned short>( aJSON, AGE_KEY ) ),
	mNationality( ValueFromRequiredJSONKey<E_NATIONALITY>( aJSON, NATIONALITY_KEY ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player from JSON." )

void CPerson::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mFirstName, FIRST_NAME_KEY );
	AddToJSONKey( aJSON, mSurnames, SURNAMES_KEY );
	AddToOptionalJSONKey( aJSON, mKnownName, KNOWN_NAME_KEY, mSurnames );
	AddToJSONKey( aJSON, mAge, AGE_KEY );
	AddToJSONKey( aJSON, mNationality, NATIONALITY_KEY );
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
