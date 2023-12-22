#include "football/CPlayer.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NationalityUtils.h"

#include <iostream>

namespace futsim
{

namespace football
{

CPlayer::CPlayer(
	const std::string_view aFirstName,
	const std::string_view aSurnames,
	const std::string_view aKnownName,
	const unsigned short& aAge,
	const E_NATIONALITY& aNationality,
	const CPlayerSkills& aPlayerSkills
) try :
	CPerson( aFirstName, aSurnames, aKnownName, aAge, aNationality ),
	mPlayerSkills( aPlayerSkills )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player." )

CPlayer::CPlayer( const json& aJSON ) try :
	CPerson( aJSON ),
	mPlayerSkills( ValueFromRequiredJSONKey<CPlayerSkills>( aJSON ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player from JSON." )

void CPlayer::JSON( json& aJSON ) const noexcept
{
	CPerson::JSON( aJSON );
	AddToJSONKey( aJSON, mPlayerSkills );
}

const CPlayerSkills CPlayer::GetPlayerSkills() const noexcept
{
	return mPlayerSkills;
}

} // football namespace

}  // futsim namespace