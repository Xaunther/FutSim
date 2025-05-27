#pragma once

#include <optional>

namespace futsim::football
{

class CPenaltyShootoutState;
class CPeriodStates;

namespace types::CMatchState
{

//! Optional period states.
using optional_period_states = std::optional<CPeriodStates>;

//! Optional state for the penalty shootout.
using optional_penalty_shootout_state = std::optional<CPenaltyShootoutState>;

} // types::CChanceState namespace

} //futsim::football namespace
