#include "football/CGoalDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
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

CGoalDrawConfiguration::CGoalDrawConfiguration( const json& aJSON ) try :
	mAverageGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_GOALS, DEFAULT_AVERAGE_GOALS ), "average number of goals" ) ),
	mAveragePenaltyGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_PENALTY_GOALS, DEFAULT_AVERAGE_PENALTY_GOALS ), "average number of penalty goals" ) ),
	mAverageDirectFreeKickGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_DIRECT_FREE_KICK_GOALS, DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS ), "average number of direct free kick goals" ) ),
	mAverageIndirectFreeKickGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_INDIRECT_FREE_KICK_GOALS, DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS ), "average number of indirect free kick goals" ) ),
	mAverageCornerGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_CORNER_GOALS, DEFAULT_AVERAGE_CORNER_GOALS ), "average number of corner kick goals" ) ),
	mAverageFarShotGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_FAR_SHOT_GOALS, DEFAULT_AVERAGE_FAR_SHOT_GOALS ), "average number of far shot goals" ) ),
	m1vs1GKGoalProbability( CheckProbability( ValueFromOptionalJSONKey<probability>(
		aJSON, JSON_1VS1_GK_GOAL_PROBABILITY, DEFAULT_1VS1_GK_GOAL_PROBABILITY ), "probability to score in a 1 on 1 vs GK chance" ) ),
	m1vs1DFGoalProbability( CheckProbability( ValueFromOptionalJSONKey<probability>(
		aJSON, JSON_1VS1_DF_GOAL_PROBABILITY, DEFAULT_1VS1_DF_GOAL_PROBABILITY ), "probability to score in a 1 on 1 vs DF chance" ) ),
	mExtraCornerProbability( CheckProbability( ValueFromOptionalJSONKey<probability>(
		aJSON, JSON_EXTRA_CORNER_PROBABILITY, DEFAULT_EXTRA_CORNER_PROBABILITY ), "probability to be awarded an extra corner" ) )
{
	CheckProbability( mExtraCornerProbability + m1vs1GKGoalProbability,
		"joint probability of getting an extra corner or scoring in a 1 on 1 vs GK chance" );
	CheckProbability( mExtraCornerProbability + m1vs1DFGoalProbability,
		"joint probability of getting an extra corner or scoring in a 1 on 1 vs DF chance" );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the goal draw configuration." )

void CGoalDrawConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mAverageGoals, JSON_AVERAGE_GOALS );
	AddToJSONKey( aJSON, mAveragePenaltyGoals, JSON_AVERAGE_PENALTY_GOALS );
	AddToJSONKey( aJSON, mAverageDirectFreeKickGoals, JSON_AVERAGE_DIRECT_FREE_KICK_GOALS );
	AddToJSONKey( aJSON, mAverageIndirectFreeKickGoals, JSON_AVERAGE_INDIRECT_FREE_KICK_GOALS );
	AddToJSONKey( aJSON, mAverageCornerGoals, JSON_AVERAGE_CORNER_GOALS );
	AddToJSONKey( aJSON, mAverageFarShotGoals, JSON_AVERAGE_FAR_SHOT_GOALS );
	AddToJSONKey( aJSON, m1vs1GKGoalProbability, JSON_1VS1_GK_GOAL_PROBABILITY );
	AddToJSONKey( aJSON, m1vs1DFGoalProbability, JSON_1VS1_DF_GOAL_PROBABILITY );
	AddToJSONKey( aJSON, mExtraCornerProbability, JSON_EXTRA_CORNER_PROBABILITY );
}

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

CGoalDrawConfiguration::chance_outcome_distribution CGoalDrawConfiguration::Create1vs1GKOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	const auto& modifiedGoalProbability = ModifiedProbability( 1 - mExtraCornerProbability, m1vs1GKGoalProbability,
		2 * aEffectiveGKSkill, aEffectiveFWSkill + aEffectiveMFSkill );
	return chance_outcome_distribution{ {
		modifiedGoalProbability,
		mExtraCornerProbability,
		( 1 - modifiedGoalProbability - mExtraCornerProbability ) / 2,
		( 1 - modifiedGoalProbability - mExtraCornerProbability ) / 2
	} };
}

CGoalDrawConfiguration::chance_outcome_distribution CGoalDrawConfiguration::Create1vs1DFOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	const auto& modifiedGoalProbability = ModifiedProbability( 1 - mExtraCornerProbability, m1vs1DFGoalProbability,
		aEffectiveGKSkill + aEffectiveDFSkill, aEffectiveFWSkill + aEffectiveMFSkill );
	return chance_outcome_distribution{ {
		modifiedGoalProbability,
		mExtraCornerProbability,
		( 1 - modifiedGoalProbability - mExtraCornerProbability ) / 2,
		( 1 - modifiedGoalProbability - mExtraCornerProbability ) / 2
	} };
}

} //futsim::football namespace