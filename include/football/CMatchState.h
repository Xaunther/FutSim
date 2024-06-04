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

public:
	//! Retrieves the \copybrief mMandatoryPlayTimeState
	const CPeriodStates& GetMandatoryPlayTimeState() const noexcept;

	//! Retrieves the \copybrief mExtraTimeState
	const optional_period_states& GetExtraTimeState() const noexcept;

	//! Retrieves the \copybrief mPenaltyShootoutState
	const optional_penalty_shootout_state& GetPenaltyShootoutState() const noexcept;

private:
	//! Mandatory play time of the match.
	CPeriodStates mMandatoryPlayTimeState;
	//! Optional extra time state.
	optional_period_states mExtraTimeState;
	//! Optional penalty shootout state.
	optional_penalty_shootout_state mPenaltyShootoutState;
};

} // futsim::football namespace
