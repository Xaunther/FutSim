#pragma once

#include <vector>

namespace futsim::football
{

class CMatchConfiguration;
class CPlayState;

namespace types::CPeriodState
{

//! Aggregate with a play and whether it is assigned to the home team.
template <typename T = football::CPlayState> struct play
{
	static_assert( std::is_same_v<T, football::CPlayState>,
		"The play aggregate can only be instantiated with futsim::football::CPlayState type." );
	//! Whether the play is assigned to the home team.
	bool homeTeam;
	//! Play state.
	T state;
};

//! Container for the plays in a period.
using plays = std::vector<play<>>;

//! Concept for a period play policy
template<typename T> concept period_play_policy =
	requires ( T aPolicy, const plays & aPlays, const football::CMatchConfiguration & aMatchConfiguration )
{
	{ aPolicy( aPlays, aMatchConfiguration ) } -> std::same_as<bool>;
};

} // types::CPeriodState namespace

} // futsim::football namespace