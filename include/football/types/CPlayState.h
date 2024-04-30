#pragma once

#include <optional>
#include <vector>

namespace futsim::football
{

class CChanceState;
class CFoulState;

namespace types::CPlayState
{

//! Optional foul state.
using optional_foul_state = std::optional<CFoulState>;

//! Container with the chances states.
using chances_states = std::vector<CChanceState>;

} // types::CPlayState namespace

} // futsim::football::types::CPlayState namespace