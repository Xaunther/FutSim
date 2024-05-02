#pragma once

#include <vector>

namespace futsim::football
{

class CPlayState;

namespace types::CPeriodState
{

//! Pair with a play and whether it is assigned to the home team.
using play = std::pair<bool, CPlayState>;

//! Container for the plays in a period.
using plays = std::vector<play>;

} // types::CPeriodState namespace

} // futsim::football namespace