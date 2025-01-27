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

public:
	//! Default constructor.
	explicit CPlayerState() = default;

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPlayerState( const json& aJSON );	

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	/**
	 * @brief Indicates if the player has played
	 */
	explicit operator bool() const noexcept;

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

	/**
	 * @brief Adds a minute of play.
	 * @return The object itself.
	 */
	CPlayerState& AddMinutePlayed() noexcept;

	/**
	 * @brief Adds a foul.
	 * @param aFoulState State of the foul to be added.
	 */
	CPlayerState& AddFoul( const CFoulState& aFoulState ) noexcept;

	/**
	 * @brief Adds a save.
	 * @return The object itself.
	 */
	CPlayerState& AddSave() noexcept;

	/**
	 * @brief Adds a tackle.
	 * @return The object itself.
	 */
	CPlayerState& AddTackle() noexcept;

	/**
	 * @brief Adds a pass.
	 * @param aIsAssist If the pass is an assist.
	 */
	CPlayerState& AddPass( bool aIsAssist ) noexcept;

	/**
	 * @brief Adds a shot.
	 * @param aIsGoal If the shot is a goal.
	 */
	CPlayerState& AddShot( bool aIsGoal ) noexcept;

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
