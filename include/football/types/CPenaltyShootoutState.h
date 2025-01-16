#pragma once

#include <vector>

namespace futsim::football
{

class CPenaltyState;

namespace types::CPenaltyShootoutState
{

//! Aggregate with a penalty and whether it is assigned to the home team.
template <typename T = football::CPenaltyState> struct penalty
{
	static_assert( std::is_same_v<T, football::CPenaltyState>,
		"The penalty aggregate can only be instantiated with futsim::football::CPenaltyState type." );
	//! Whether the penalty is assigned to the home team.
	bool homeTeam;
	//! Penalty state.
	T state;
};

//! Type for the penalty states.
using penalty_states = std::vector<penalty<>>;

//! Aggregate for a score.
struct score
{
	//! Home score.
	unsigned int home = 0;
	//! Away score.
	unsigned int away = 0;
};

} // types::CPenaltyShootoutState namespace

} // futsim::football namespace
