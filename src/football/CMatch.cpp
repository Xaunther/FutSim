#include "football/CMatch.h"

#include "ExceptionUtils.h"
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

} // futsim::football namespace