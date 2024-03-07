#include "football/CDrawConfiguration.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

CDrawConfiguration::CDrawConfiguration(
	const CPossessionDrawConfiguration& aPossessionDrawConfiguration,
	const CFoulDrawConfiguration& aFoulDrawConfiguration,
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const CGoalDrawConfiguration& aGoalDrawConfiguration
) try :
	mPossessionDrawConfiguration( aPossessionDrawConfiguration ),
	mFoulDrawConfiguration( aFoulDrawConfiguration ),
	mChancesDrawConfiguration( aChancesDrawConfiguration ),
	mGoalDrawConfiguration( aGoalDrawConfiguration )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the draw configuration." )

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