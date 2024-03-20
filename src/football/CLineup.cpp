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

const CLineup::position_names& CLineup::GetPlayers() const noexcept
{
	return mPlayersLineup;
}

template <E_PLAYER_POSITION tPlayerPosition>
std::span<const CLineup::names::value_type> CLineup::GetPlayers() const noexcept
{
	return mPlayersLineup[ static_cast< position_names::size_type >( tPlayerPosition ) ];
}

template std::span<const CLineup::names::value_type> CLineup::GetPlayers<E_PLAYER_POSITION::GK>() const noexcept;
template std::span<const CLineup::names::value_type> CLineup::GetPlayers<E_PLAYER_POSITION::DF>() const noexcept;
template std::span<const CLineup::names::value_type> CLineup::GetPlayers<E_PLAYER_POSITION::DM>() const noexcept;
template std::span<const CLineup::names::value_type> CLineup::GetPlayers<E_PLAYER_POSITION::MF>() const noexcept;
template std::span<const CLineup::names::value_type> CLineup::GetPlayers<E_PLAYER_POSITION::AM>() const noexcept;
template std::span<const CLineup::names::value_type> CLineup::GetPlayers<E_PLAYER_POSITION::FW>() const noexcept;

std::span<const CLineup::names::value_type> CLineup::GetSubs() const noexcept
{
	return mPlayersLineup.back();
}

void CLineup::CheckPlayersLineup() const try
{
	if( GetPlayers< E_PLAYER_POSITION::GK >().size() != 1 )
		throw std::invalid_argument{ "There has to be exactly 1 GK." };
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the players lineup." )

} // futsim::football namespace