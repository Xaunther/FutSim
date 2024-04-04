#include "football/CLineup.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

//! Macro to explicitly instantiate GetPlayers method.
#define EXPLICIT_INSTANTIATE_GET_PLAYERS(name, ... ) \
	template CLineup::players<E_PLAYER_POSITION::name> CLineup::GetPlayers<E_PLAYER_POSITION::name>() const noexcept; \

CLineup::CLineup(
	const std::string_view aGK,
	const std::span<const name> aDFs,
	const std::span<const name> aDMs,
	const std::span<const name> aMFs,
	const std::span<const name> aAMs,
	const std::span<const name> aFWs,
	const std::span<const name> aSubs
) try :
	mPlayersLineup{
		names{ aGK.data() },
		{ aDFs.begin(), aDFs.end() },
		{ aDMs.begin(), aDMs.end() },
		{ aMFs.begin(), aMFs.end() },
		{ aAMs.begin(), aAMs.end() },
		{ aFWs.begin(), aFWs.end() },
		{ aSubs.begin(), aSubs.end() },
}
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup." )

CLineup::CLineup( const json& aJSON ) try :
	mPlayersLineup( {
		names{ ValueFromRequiredJSONKey<name>( aJSON, CLineup::JSON_GK ) },
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_DFS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_DMS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_MFS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_AMS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_FWS ),
		ValueFromOptionalJSONKey<names>( aJSON, CLineup::JSON_SUBS ),
		} )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup from JSON." )

void CLineup::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, GetPlayers< E_PLAYER_POSITION::GK >(), JSON_GK );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::DF >(); !players.empty() )
		AddToJSONKey( aJSON, players, JSON_DFS );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::DM >(); !players.empty() )
		AddToJSONKey( aJSON, players, JSON_DMS );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::MF >(); !players.empty() )
		AddToJSONKey( aJSON, players, JSON_MFS );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::AM >(); !players.empty() )
		AddToJSONKey( aJSON, players, JSON_AMS );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::FW >(); !players.empty() )
		AddToJSONKey( aJSON, players, JSON_FWS );
	if( const auto& players = GetSubs(); !players.empty() )
		AddToJSONKey( aJSON, players, JSON_SUBS );
}

template <E_PLAYER_POSITION tPlayerPosition>
CLineup::players<tPlayerPosition> CLineup::GetPlayers() const noexcept
{
	if constexpr( tPlayerPosition == E_PLAYER_POSITION::GK )
		return mPlayersLineup.front().front();
	else
		return mPlayersLineup[ static_cast< position_names::size_type >( tPlayerPosition ) ];
}
FOR_EACH_PLAYER_POSITION( EXPLICIT_INSTANTIATE_GET_PLAYERS )

std::span<const CLineup::name> CLineup::GetSubs() const noexcept
{
	return mPlayersLineup.back();
}

} // futsim::football namespace