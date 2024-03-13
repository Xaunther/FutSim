#include "football/CLineup.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

CLineup::CLineup( const position_names& aPlayersLineup ) try :
	mPlayersLineup( aPlayersLineup )
{
	CheckPlayersLineup();
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup." )

CLineup::CLineup( const json& aJSON ) try :
	mPlayersLineup( {
		ValueFromRequiredJSONKey<names>( aJSON, CLineup::JSON_GK ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_DFS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_DMS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_MFS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_AMS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_FWS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_SUBS ),
		} )
{
	CheckPlayersLineup();
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup from JSON." )

const CLineup::names& CLineup::GetPlayers( const E_PLAYER_POSITION& aPlayerPosition ) const noexcept
{
	return mPlayersLineup[ static_cast< position_names::size_type >( aPlayerPosition ) ];
}

const CLineup::names& CLineup::GetSubs() const noexcept
{
	return mPlayersLineup.back();
}

void CLineup::CheckPlayersLineup() const try
{
	if( GetPlayers( E_PLAYER_POSITION::GK ).size() != 1 )
		throw std::invalid_argument{ "There has to be exactly 1 GK." };
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the players lineup." )

} // futsim::football namespace