#include "football/CGoalDrawConfiguration.h"

#include "CEnumDistribution.h"

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
		aJSON, AVERAGE_GOALS_KEY, AVERAGE_GOALS ), "average number of goals" ) ),
	mAveragePenaltyGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_PENALTY_GOALS_KEY, AVERAGE_PENALTY_GOALS ), "average number of penalty goals" ) ),
	mAverageDirectFreeKickGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_DIRECT_FREE_KICK_GOALS_KEY, AVERAGE_DIRECT_FREE_KICK_GOALS ), "average number of direct free kick goals" ) ),
	mAverageIndirectFreeKickGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_INDIRECT_FREE_KICK_GOALS_KEY, AVERAGE_INDIRECT_FREE_KICK_GOALS ), "average number of indirect free kick goals" ) ),
	mAverageCornerGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_CORNER_GOALS_KEY, AVERAGE_CORNER_GOALS ), "average number of corner kick goals" ) ),
	mAverageFarShotGoals( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_FAR_SHOT_GOALS_KEY, AVERAGE_FAR_SHOT_GOALS ), "average number of far shot goals" ) ),
	m1vs1GKGoalProbability( CheckProbability( ValueFromOptionalJSONKey<probability>(
		aJSON, ONE_VS_ONE_GK_GOAL_PROBABILITY_KEY, ONE_VS_ONE_GK_GOAL_PROBABILITY ), "probability to score in a 1 on 1 vs GK chance" ) ),
	m1vs1DFGoalProbability( CheckProbability( ValueFromOptionalJSONKey<probability>(
		aJSON, ONE_VS_ONE_DF_GOAL_PROBABILITY_KEY, ONE_VS_ONE_DF_GOAL_PROBABILITY ), "probability to score in a 1 on 1 vs DF chance" ) ),
	mExtraCornerProbability( CheckProbability( ValueFromOptionalJSONKey<probability>(
		aJSON, EXTRA_CORNER_PROBABILITY_KEY, EXTRA_CORNER_PROBABILITY ), "probability to be awarded an extra corner" ) )
{
	CheckProbability( mExtraCornerProbability + m1vs1GKGoalProbability,
		"joint probability of getting an extra corner or scoring in a 1 on 1 vs GK chance" );
	CheckProbability( mExtraCornerProbability + m1vs1DFGoalProbability,
		"joint probability of getting an extra corner or scoring in a 1 on 1 vs DF chance" );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the goal draw configuration." )

void CGoalDrawConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mAverageGoals, AVERAGE_GOALS_KEY );
	AddToJSONKey( aJSON, mAveragePenaltyGoals, AVERAGE_PENALTY_GOALS_KEY );
	AddToJSONKey( aJSON, mAverageDirectFreeKickGoals, AVERAGE_DIRECT_FREE_KICK_GOALS_KEY );
	AddToJSONKey( aJSON, mAverageIndirectFreeKickGoals, AVERAGE_INDIRECT_FREE_KICK_GOALS_KEY );
	AddToJSONKey( aJSON, mAverageCornerGoals, AVERAGE_CORNER_GOALS_KEY );
	AddToJSONKey( aJSON, mAverageFarShotGoals, AVERAGE_FAR_SHOT_GOALS_KEY );
	AddToJSONKey( aJSON, m1vs1GKGoalProbability, ONE_VS_ONE_GK_GOAL_PROBABILITY_KEY );
	AddToJSONKey( aJSON, m1vs1DFGoalProbability, ONE_VS_ONE_DF_GOAL_PROBABILITY_KEY );
	AddToJSONKey( aJSON, mExtraCornerProbability, EXTRA_CORNER_PROBABILITY_KEY );
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

CGoalDrawConfiguration::goal_draw_distribution CGoalDrawConfiguration::Create1vs1GKOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return CreateChanceOutcomeDistribution( m1vs1GKGoalProbability, 0, 2 * aEffectiveGKSkill, aEffectiveMFSkill + aEffectiveFWSkill );
}

CGoalDrawConfiguration::goal_draw_distribution CGoalDrawConfiguration::Create1vs1DFOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return CreateChanceOutcomeDistribution( m1vs1DFGoalProbability, aEffectiveDFSkill, aEffectiveGKSkill + aEffectiveDFSkill, aEffectiveMFSkill + aEffectiveFWSkill );
}

CGoalDrawConfiguration::goal_draw_distribution CGoalDrawConfiguration::CreateChanceOutcomeDistribution(
	const probability& aDefaultGoalProbability,
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveDefenceSkill,
	const effective_skill& aEffectiveAttackSkill ) const noexcept
{
	const auto& modifiedGoalProbability = ModifiedProbability( 1 - mExtraCornerProbability, aDefaultGoalProbability,
		aEffectiveDefenceSkill, aEffectiveAttackSkill );
	const auto& defenderActionProbability = aEffectiveDFSkill / aEffectiveDefenceSkill;
	return goal_draw_distribution{ {
			modifiedGoalProbability,
			mExtraCornerProbability * ( 1 - defenderActionProbability ),
			mExtraCornerProbability * defenderActionProbability,
			( 1 - modifiedGoalProbability - mExtraCornerProbability ) * ( 1 - defenderActionProbability ) / 2,
			( 1 - modifiedGoalProbability - mExtraCornerProbability ) * defenderActionProbability / 2,
			( 1 - modifiedGoalProbability - mExtraCornerProbability ) / 2
		} };
}

template <E_PLAYER_SKILL tPlayerSkill>
CGoalDrawConfiguration::position_draw_distribution CGoalDrawConfiguration::CreatePositionDrawDistribution() const noexcept
{
	if constexpr( tPlayerSkill == E_PLAYER_SKILL::St )
		return position_draw_distribution{ 1 };
	else if constexpr( tPlayerSkill == E_PLAYER_SKILL::Tk )
		return position_draw_distribution{ 0, 24, 8, 4, 3, 1 };
	else if constexpr( tPlayerSkill == E_PLAYER_SKILL::Ps )
		return position_draw_distribution{ 0, 1, 3, 8, 5, 3 };
	else if constexpr( tPlayerSkill == E_PLAYER_SKILL::Sh )
		return position_draw_distribution{ 0, 1, 3, 4, 8, 24 };
}

template CGoalDrawConfiguration::position_draw_distribution CGoalDrawConfiguration::CreatePositionDrawDistribution<E_PLAYER_SKILL::St>() const noexcept;
template CGoalDrawConfiguration::position_draw_distribution CGoalDrawConfiguration::CreatePositionDrawDistribution<E_PLAYER_SKILL::Tk>() const noexcept;
template CGoalDrawConfiguration::position_draw_distribution CGoalDrawConfiguration::CreatePositionDrawDistribution<E_PLAYER_SKILL::Ps>() const noexcept;
template CGoalDrawConfiguration::position_draw_distribution CGoalDrawConfiguration::CreatePositionDrawDistribution<E_PLAYER_SKILL::Sh>() const noexcept;

} //futsim::football namespace
