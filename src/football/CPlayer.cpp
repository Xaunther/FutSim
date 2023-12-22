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
	mPlayerSkills( ValueFromJSON<CPlayerSkills>( aJSON ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player from JSON." )

CPlayer::json CPlayer::JSON() const noexcept
{
	json result = CPerson::JSON();
	result[ CPlayerSkills::JSON_KEY ] = mPlayerSkills.ToJSON();

	return result;
}

const CPlayerSkills CPlayer::GetPlayerSkills() const noexcept
{
	return mPlayerSkills;
}

} // football namespace

}  // futsim namespace