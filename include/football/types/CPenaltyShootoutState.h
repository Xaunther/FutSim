#pragma once

#include <vector>

namespace futsim::football
{

class CPenaltyState;

namespace types::CPenaltyShootoutState
{

//! Pair with a penalty and whether it is assigned to the home team.
using penalty = std::pair<bool, CPenaltyState>;

//! Type for the penalty states.
using penalty_states = std::vector<penalty>;

} // types::CPenaltyShootoutState namespace

} // futsim::football namespace