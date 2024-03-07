#include "football/CDrawConfiguration.h"

namespace futsim::football
{

const CPossessionDrawConfiguration& CDrawConfiguration::GetPossessionDrawConfiguration() const noexcept
{
	return mPossessionDrawConfiguration;
}

const CFoulDrawConfiguration& CDrawConfiguration::GetFoulDrawConfiguration() const noexcept
{
	return mFoulDrawConfiguration;
}

const CChancesDrawConfiguration& CDrawConfiguration::GetChancesDrawConfiguration() const noexcept
{
	return mChancesDrawConfiguration;
}

const CGoalDrawConfiguration& CDrawConfiguration::GetGoalDrawConfiguration() const noexcept
{
	return mGoalDrawConfiguration;
}

} // futsim::football namespace