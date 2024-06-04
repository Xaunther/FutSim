#pragma once

#include "IJsonable.h"

#include "football/types/CPeriodStates.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of series of match periods.
 * @details The periods have the same play policy and alternate the team that kicks off.
*/
class CPeriodStates : public IJsonable
{
protected:
	using period_states = types::CPeriodStates::period_states;

public:
	//! Retrieves the \copybrief mStates
	const period_states& GetStates() const noexcept;

private:
	//! Period states.
	period_states mStates;
};

} // futsim::football namespace