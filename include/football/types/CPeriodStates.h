#pragma once

#include <vector>

namespace futsim::football
{

class CMatchConfiguration;
class CPeriodState;

namespace types::CPeriodStates
{

//! Container for the periods.
using period_states = std::vector<football::CPeriodState>;

//! Concept for a period play policy
template<typename T> concept period_policy =
	requires ( T aPolicy, const period_states & aPeriodStates, const football::CMatchConfiguration & aMatchConfiguration )
{
	{ aPolicy( aPeriodStates, aMatchConfiguration ) } -> std::same_as<bool>;
};

} // types::CPeriodStates namespace

} // futsim::football namespace