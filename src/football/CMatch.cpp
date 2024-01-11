#include "football/CMatch.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NameUtils.h"

namespace futsim::football
{

CMatch::CMatch(
	const CTeam& aHomeTeam,
	const CTeam& aAwayTeam,
	const CStadium& aStadium,
	const std::string_view aReferee
) try :
	mHomeTeam( aHomeTeam ),
	mAwayTeam( aAwayTeam ),
	mStadium( aStadium ),
	mReferee( CheckName( aReferee, "referee name" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match." )

CMatch::CMatch( const json& aJSON ) try :
	mHomeTeam( ValueFromRequiredJSONKey<CTeam>( aJSON, JSON_HOME_TEAM ) ),
	mAwayTeam( ValueFromRequiredJSONKey<CTeam>( aJSON, JSON_AWAY_TEAM ) ),
	mStadium( ValueFromRequiredJSONKey<CStadium>( aJSON ) ),
	mReferee( CheckName( ValueFromRequiredJSONKey<name_type>( aJSON, JSON_REFEREE ), "referee name" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match from JSON." )

} // futsim::football namespace