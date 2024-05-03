#pragma once

#include "IJsonable.h"

#include "types/CPenaltyShootoutState.h"

#include "football/CChanceState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a penalty shootout.
*/
class CPenaltyShootoutState : public IJsonable
{
protected:
	using penalty_states = types::CPenaltyShootoutState::penalty_states;

public:
	//! Retrieves the \copybrief mPenalties
	const penalty_states& GetPenalties() const noexcept;

private:
	//! Penalties.
	penalty_states mPenalties;
};

} // futsim::football namespace