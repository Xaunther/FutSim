#include "football/CMatch.h"

#include "football/CTeamStrategy.h"

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

void CMatch::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mHomeTeam, JSON_HOME_TEAM );
	AddToJSONKey( aJSON, mAwayTeam, JSON_AWAY_TEAM );
	AddToJSONKey( aJSON, mStadium );
	AddToJSONKey( aJSON, mReferee, JSON_REFEREE );
}

const CTeam& CMatch::GetHomeTeam() const noexcept
{
	return mHomeTeam;
}

const CTeam& CMatch::GetAwayTeam() const noexcept
{
	return mAwayTeam;
}

const CStadium& CMatch::GetStadium() const noexcept
{
	return mStadium;
}

std::string_view CMatch::GetReferee() const noexcept
{
	return mReferee;
}

template <bool tHomeTeam> const CTeamStrategy& CMatch::CheckTeamStrategy( const CTeamStrategy& aTeamStrategy ) const try
{
	if constexpr( tHomeTeam )
		mHomeTeam.CheckLineup( aTeamStrategy.GetLineup() );
	else
		mAwayTeam.CheckLineup( aTeamStrategy.GetLineup() );
	return aTeamStrategy;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the team strategy against the match definition." )

} // futsim::football namespace