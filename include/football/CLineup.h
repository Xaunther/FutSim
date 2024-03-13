#pragma once

#include "IJsonable.h"

#include "football/CLineupTypes.h"

namespace futsim::football
{

/**
 * @brief Class that defines a lineup.
*/
class CLineup : public IJsonable
{
protected:
	using names = CLineupTypes::names;
	using position_names = CLineupTypes::position_names;

public:
	/**
	 * @brief Retrieves the players at a certain position.
	 * @param aPlayerPosition Position.
	*/
	const names& GetPlayers( const E_PLAYER_POSITION& aPlayerPosition ) const noexcept;

	//! Retrieves the substitute players.
	const names& GetSubs() const noexcept;

private:
	//! Lined up players by position.
	position_names mPlayersLineup;
};

} // futsim namespace