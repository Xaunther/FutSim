#include "football/CGoalDrawConfiguration.h"

namespace futsim::football
{

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