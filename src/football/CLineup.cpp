#include "football/CLineup.h"

namespace futsim::football
{

const CLineup::names& CLineup::GetPlayers( const E_PLAYER_POSITION& aPlayerPosition ) const noexcept
{
	return mPlayersLineup[ static_cast< position_names::size_type >( aPlayerPosition ) ];
}

const CLineup::names& CLineup::GetSubs() const noexcept
{
	return mPlayersLineup.back();
}

} // futsim::football namespace