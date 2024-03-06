#include "football/CGoalDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "NumberUtils.h"
#include "ProbabilityUtils.h"

namespace futsim::football
{

CGoalDrawConfiguration::CGoalDrawConfiguration(
	const stat& aAverageGoals,
	const stat& aAveragePenaltyGoals,
	const stat& aAverageDirectFreeKickGoals,
	const stat& aAverageIndirectFreeKickGoals,
	const stat& aAverageCornerGoals,
	const stat& aAverageFarShotGoals,
	const stat& a1vs1GKGoalProbability,
	const stat& a1vs1DFGoalProbability,
	const stat& aExtraCornerProbability
) try :
	mAverageGoals( CheckNonNegativeness( aAverageGoals, "average number of goals" ) ),
	mAveragePenaltyGoals( CheckNonNegativeness( aAveragePenaltyGoals, "average number of penalty goals" ) ),
	mAverageDirectFreeKickGoals( CheckNonNegativeness( aAverageDirectFreeKickGoals, "average number of direct free kick goals" ) ),
	mAverageIndirectFreeKickGoals( CheckNonNegativeness( aAverageIndirectFreeKickGoals, "average number of indirect free kick goals" ) ),
	mAverageCornerGoals( CheckNonNegativeness( aAverageCornerGoals, "average number of corner kick goals" ) ),
	mAverageFarShotGoals( CheckNonNegativeness( aAverageFarShotGoals, "average number of far shot goals" ) ),
	m1vs1GKGoalProbability( CheckProbability( a1vs1GKGoalProbability, "probability to score in a 1 on 1 vs GK chance" ) ),
	m1vs1DFGoalProbability( CheckProbability( a1vs1DFGoalProbability, "probability to score in a 1 on 1 vs DF chance" ) ),
	mExtraCornerProbability( CheckProbability( aExtraCornerProbability, "probability to be awarded an extra corner" ) )
{
	CheckProbability( mExtraCornerProbability + m1vs1GKGoalProbability,
		"joint probability of getting an extra corner or scoring in a 1 on 1 vs GK chance" );
	CheckProbability( mExtraCornerProbability + m1vs1DFGoalProbability,
		"joint probability of getting an extra corner or scoring in a 1 on 1 vs DF chance" );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the goal draw configuration." )

const CGoalDrawConfiguration::stat& CGoalDrawConfiguration::GetAverageGoals() const noexcept
{
	return mAverageGoals;
}

const CGoalDrawConfiguration::stat& CGoalDrawConfiguration::GetAveragePenaltyGoals() const noexcept
{
	return mAveragePenaltyGoals;
}

const CGoalDrawConfiguration::stat& CGoalDrawConfiguration::GetAverageDirectFreeKickGoals() const noexcept
{
	return mAverageDirectFreeKickGoals;
}

const CGoalDrawConfiguration::stat& CGoalDrawConfiguration::GetAverageIndirectFreeKickGoals() const noexcept
{
	return mAverageIndirectFreeKickGoals;
}

const CGoalDrawConfiguration::stat& CGoalDrawConfiguration::GetAverageCornerGoals() const noexcept
{
	return mAverageCornerGoals;
}

const CGoalDrawConfiguration::stat& CGoalDrawConfiguration::GetAverageFarShotGoals() const noexcept
{
	return mAverageFarShotGoals;
}

const CGoalDrawConfiguration::probability& CGoalDrawConfiguration::Get1vs1GKGoalProbability() const noexcept
{
	return m1vs1GKGoalProbability;
}

const CGoalDrawConfiguration::probability& CGoalDrawConfiguration::Get1vs1DFGoalProbability() const noexcept
{
	return m1vs1DFGoalProbability;
}

const CGoalDrawConfiguration::probability& CGoalDrawConfiguration::GetExtraCornerProbability() const noexcept
{
	return mExtraCornerProbability;
}

} //futsim::football namespace