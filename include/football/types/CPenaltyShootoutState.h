#pragma once

#include <vector>

#include "football/types/CTieCondition.h"

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
	inline constexpr score operator+( const score& aOther ) const noexcept
	{
		return score{ *this } += aOther;
	}

	inline constexpr score& operator+=( const score& aOther ) noexcept
	{
		home += aOther.home;
		away += aOther.away;
		return *this;
	}

	//! Home score.
	types::CTieCondition::goal_count home = 0;
	//! Away score.
	types::CTieCondition::goal_count away = 0;
};

} // types::CPenaltyShootoutState namespace

} // futsim::football namespace
