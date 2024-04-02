#pragma once

#include "IJsonable.h"

#include "football/types/CChanceState.h"
#include "football/types/CGoalDrawConfiguration.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a chance.
*/
class CChanceState : public IJsonable
{
protected:
	using chance_type = types::CChanceState::chance_type;
	using optional_name = types::CChanceState::optional_name;
	using E_CHANCE_OUTCOME = types::CGoalDrawConfiguration::E_CHANCE_OUTCOME;

public:
	//! Retrieves the \copybrief mChanceType
	const chance_type& GetChanceType() const noexcept;

	//! Retrieves the \copybrief mOutcome
	const E_CHANCE_OUTCOME& GetChanceOutcome() const noexcept;

	/**
	 * @brief Retrieves the given actor, if any.
	 * @tparam tPlayerSkill Skill used by the actor.
	*/
	template <E_PLAYER_SKILL tPlayerSkill> const optional_name& GetActor() const noexcept;

	//! \copydoc GetActor
	template <E_PLAYER_SKILL tPlayerSkill> optional_name& Actor() const noexcept;

private:
	//! Chance type draw outcome.
	chance_type mChanceType;
	//! Chance outcome.
	E_CHANCE_OUTCOME mOutcome;
	//! Player that made the save, if any.
	optional_name mStopper;
	//! Player that made the tackle, if any.
	optional_name mTackler;
	//! Player that made the pass, if any.
	optional_name mPasser;
	//! Player that made the shot, if any.
	optional_name mShooter;
};

} // futsim::football namespace