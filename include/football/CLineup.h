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
	 * @brief Member constructor.
	 * @param aPlayersLineup \ref mPlayersLineup
	*/
	explicit CLineup( const position_names& aPlayersLineup );

	/**
	 * @brief Retrieves the players at a certain position.
	 * @param aPlayerPosition Position.
	*/
	const names& GetPlayers( const E_PLAYER_POSITION& aPlayerPosition ) const noexcept;

	//! Retrieves the substitute players.
	const names& GetSubs() const noexcept;

private:
	/**
	 * @brief Checks the validity of the players lineup.
	 * @param aPlayersLineup Players lineup.
	*/
	void CheckPlayersLineup() const;

	//! Lined up players by position.
	position_names mPlayersLineup;
};

} // futsim namespace