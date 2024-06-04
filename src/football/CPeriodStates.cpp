#include "football/CPeriodStates.h"

#include "JsonUtils.h"

namespace futsim::football
{

bool CPeriodStates::SDefaultPeriodPolicy::operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPeriodStates.size() < aMatchConfiguration.GetPlayTime().GetPeriodCount();
}

void CPeriodStates::JSON( json& aJSON ) const noexcept
{
	AddKeyArrayToJSON( aJSON, mStates );
}

const CPeriodStates::period_states& CPeriodStates::GetStates() const noexcept
{
	return mStates;
}

} // futsim::football namespace