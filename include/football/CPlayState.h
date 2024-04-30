#pragma once

#include "IJsonable.h"

#include "football/types/CPlayState.h"

#include "football/CChanceState.h"
#include "football/CFoulState.h"
#include "football/CPossessionState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a single play.
*/
class CPlayState : public IJsonable
{
protected:
	using optional_foul_state = types::CPlayState::optional_foul_state;
	using chances_states = types::CPlayState::chances_states;

public:
	//! Retrieves the \copybrief mPossessionState
	const CPossessionState& GetPossessionState() const noexcept;

	//! Retrieves the \copybrief mFoulState
	const optional_foul_state& GetFoulState() const noexcept;

	//! Retrieves the \copybrief mChancesStates
	const chances_states& GetChancesStates() const noexcept;

private:
	//! Possession state.
	CPossessionState mPossessionState;
	//! Foul state, if any.
	optional_foul_state mFoulState;
	//! Chances states.
	chances_states mChancesStates;
};

} // futsim::football namespace
