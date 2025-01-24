#pragma once

#include "IJsonable.h"

#include "football/types/CPlayerState.h"
#include "football/traits/CPlayerState.h"

namespace futsim::football
{

class CFoulState;

/**
 * @brief Class encapsulating the state of a football player.
*/
class CPlayerState : public IJsonable, protected json_traits<football::CPlayerState>
{
protected:
	using counter = types::CPlayerState::counter;

	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	/**
	 * @brief Addition operators.
	 * @param aOther Other state to add to this one.
	 * @{
	 */
	CPlayerState operator+( const CPlayerState& aOther ) const noexcept;
	CPlayerState& operator+=( const CPlayerState& aOther ) noexcept;
	/**
	 * @}
	 */

	//! Retrieves the \copybrief mMinutesPlayed
	const counter& GetMinutesPlayed() const noexcept;

	//! Retrieves the \copybrief mSaves
	const counter& GetSaves() const noexcept;

	//! Retrieves the \copybrief mTackles
	const counter& GetTackles() const noexcept;

	//! Retrieves the \copybrief mPasses
	const counter& GetPasses() const noexcept;

	//! Retrieves the \copybrief mShots
	const counter& GetShots() const noexcept;

	//! Retrieves the \copybrief mAssists
	const counter& GetAssists() const noexcept;

	//! Retrieves the \copybrief mGoals
	const counter& GetGoals() const noexcept;

	//! Retrieves the \copybrief mFoulsCommitted
	const counter& GetFoulsCommitted() const noexcept;

	//! Retrieves the \copybrief mYellowCards
	const counter& GetYellowCards() const noexcept;

	//! Retrieves the \copybrief mRedCards
	const counter& GetRedCards() const noexcept;

	//! Adds a minute of play.
	void AddMinutePlayed() noexcept;

	/**
	 * @brief Adds a foul.
	 * @param aFoulState State of the foul to be added.
	 */
	void AddFoul( const CFoulState& aFoulState ) noexcept;

private:
	//! Minutes played.
	counter mMinutesPlayed = 0;
	//! Saves made.
	counter mSaves = 0;
	//! Tackles made.
	counter mTackles = 0;
	//! Passes made.
	counter mPasses = 0;
	//! Shots made.
	counter mShots = 0;
	//! Assists made.
	counter mAssists = 0;
	//! Goals scored.
	counter mGoals = 0;
	//! Fouls committed.
	counter mFoulsCommitted = 0;
	//! Yellow cards received.
	counter mYellowCards = 0;
	//! Red cards received.
	counter mRedCards = 0;
};

} // futsim::football namespace
