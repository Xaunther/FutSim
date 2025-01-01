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
	names{ ValueFromRequiredJSONKey<name>( aJSON, POSITION_KEY<E_PLAYER_POSITION::GK> ) },
	ValueFromOptionalJSONKey<names>( aJSON, POSITION_KEY<E_PLAYER_POSITION::DF> ),
	ValueFromOptionalJSONKey<names>( aJSON, POSITION_KEY<E_PLAYER_POSITION::DM> ),
	ValueFromOptionalJSONKey<names>( aJSON, POSITION_KEY<E_PLAYER_POSITION::MF> ),
	ValueFromOptionalJSONKey<names>( aJSON, POSITION_KEY<E_PLAYER_POSITION::AM> ),
	ValueFromOptionalJSONKey<names>( aJSON, POSITION_KEY<E_PLAYER_POSITION::FW> ),
	ValueFromOptionalJSONKey<names>( aJSON, SUBS_KEY ),
		} )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup from JSON." )

void CLineup::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, GetPlayers< E_PLAYER_POSITION::GK >(), POSITION_KEY<E_PLAYER_POSITION::GK> );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::DF >(); !players.empty() )
		AddToJSONKey( aJSON, players, POSITION_KEY<E_PLAYER_POSITION::DF> );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::DM >(); !players.empty() )
		AddToJSONKey( aJSON, players, POSITION_KEY<E_PLAYER_POSITION::DM> );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::MF >(); !players.empty() )
		AddToJSONKey( aJSON, players, POSITION_KEY<E_PLAYER_POSITION::MF> );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::AM >(); !players.empty() )
		AddToJSONKey( aJSON, players, POSITION_KEY<E_PLAYER_POSITION::AM> );
	if( const auto& players = GetPlayers< E_PLAYER_POSITION::FW >(); !players.empty() )
		AddToJSONKey( aJSON, players, POSITION_KEY<E_PLAYER_POSITION::FW> );
	if( const auto& players = GetSubs(); !players.empty() )
		AddToJSONKey( aJSON, players, SUBS_KEY );
}

template <E_PLAYER_POSITION tPlayerPosition>
CLineup::players<tPlayerPosition> CLineup::GetPlayers() const noexcept
{
	if constexpr( tPlayerPosition == E_PLAYER_POSITION::GK )
		return mPlayersLineup.front().front();
	else
		return mPlayersLineup[ static_cast<position_names::size_type>( tPlayerPosition ) ];
}
FOR_EACH_PLAYER_POSITION( EXPLICIT_INSTANTIATE_GET_PLAYERS )

std::span<const CLineup::name> CLineup::GetSubs() const noexcept
{
	return mPlayersLineup.back();
}

} // futsim::football namespace
