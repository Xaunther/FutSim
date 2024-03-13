#include "football/CLineup.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

CLineup::CLineup( const position_names& aPlayersLineup ) try :
	mPlayersLineup( aPlayersLineup )
{
	CheckPlayersLineup();
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup." )

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