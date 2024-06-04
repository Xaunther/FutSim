#include "football/CPeriodStates.h"

namespace futsim::football
{

bool CPeriodStates::SDefaultPeriodPolicy::operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPeriodStates.size() < aMatchConfiguration.GetPlayTime().GetPeriodCount();
}

const CPeriodStates::period_states& CPeriodStates::GetStates() const noexcept
{
	return mStates;
}

} // futsim::football namespace