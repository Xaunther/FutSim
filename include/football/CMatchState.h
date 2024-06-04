#pragma once

#include "IJsonable.h"

#include "types/CMatchState.h"

#include "football/CPeriodStates.h"
#include "football/CPenaltyShootoutState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a match.
*/
class CMatchState : public IJsonable
{
protected:
	using optional_period_states = types::CMatchState::optional_period_states;
	using optional_penalty_shootout_state = types::CMatchState::optional_penalty_shootout_state;

private:
	//! Mandatory play time of the match.
	CPeriodStates mMandatoryPlayTimeState;
	//! Optional extra time state.
	optional_period_states mExtraTimeState;
	//! Optional penalty shootout state.
	optional_penalty_shootout_state mPenaltyShootoutState;
};

} // futsim::football namespace
