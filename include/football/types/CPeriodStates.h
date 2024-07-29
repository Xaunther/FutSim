#pragma once

#include <vector>

namespace futsim::football
{

class CPeriodState;

namespace types::CPeriodStates
{

//! Container for the periods.
using period_states = std::vector<football::CPeriodState>;

} // types::CPeriodStates namespace

} // futsim::football namespace