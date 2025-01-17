#pragma once

#include "IJsonable.h"

#include "football/types/CPlayerState.h"

namespace futsim::football
{

/**
 * @brief Class encapsulating the state of a football player.
*/
class CPlayerState : public IJsonable
{
protected:
	using counter = types::CPlayerState::counter;

public:
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
