#pragma once

#include "IJsonable.h"

#include "football/types/CDrawConfiguration.h"
#include "football/types/CGoalDrawConfiguration.h"

namespace futsim::football
{

/**
 * @brief Class that configures the draws of the outcomes of every chance.
*/
class CGoalDrawConfiguration : public IJsonable
{
protected:
	using probability = types::CDrawConfiguration::probability;
	using stat = types::CDrawConfiguration::stat;
	using effective_skill = types::CDrawConfiguration::effective_skill;
	using goal_draw_distribution = types::CGoalDrawConfiguration::goal_draw_distribution;

public:
	/**
	 * @brief Member constructor.
	 * @param aAverageGoals \ref mAverageGoals
	 * @param aAveragePenaltyGoals \ref mAveragePenaltyGoals
	 * @param aAverageDirectFreeKickGoals \ref mAverageDirectFreeKickGoals
	 * @param aAverageIndirectFreeKickGoals \ref mAverageIndirectFreeKickGoals
	 * @param aAverageCornerGoals \ref mAverageCornerGoals
	 * @param aAverageFarShotGoals \ref mAverageFarShotGoals
	 * @param a1vs1GKGoalProbability \ref m1vs1GKGoalProbability
	 * @param a1vs1DFGoalProbability \ref m1vs1DFGoalProbability
	 * @param aExtraCornerProbability \ref mExtraCornerProbability
	*/
	explicit CGoalDrawConfiguration(
		const stat& aAverageGoals = DEFAULT_AVERAGE_GOALS,
		const stat& aAveragePenaltyGoals = DEFAULT_AVERAGE_PENALTY_GOALS,
		const stat& aAverageDirectFreeKickGoals = DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS,
		const stat& aAverageIndirectFreeKickGoals = DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS,
		const stat& aAverageCornerGoals = DEFAULT_AVERAGE_CORNER_GOALS,
		const stat& aAverageFarShotGoals = DEFAULT_AVERAGE_FAR_SHOT_GOALS,
		const stat& a1vs1GKGoalProbability = DEFAULT_1VS1_GK_GOAL_PROBABILITY,
		const stat& a1vs1DFGoalProbability = DEFAULT_1VS1_DF_GOAL_PROBABILITY,
		const stat& aExtraCornerProbability = DEFAULT_EXTRA_CORNER_PROBABILITY
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CGoalDrawConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mAverageGoals
	const stat& GetAverageGoals() const noexcept;

	//! Retrieves the \copybrief mAveragePenaltyGoals
	const stat& GetAveragePenaltyGoals() const noexcept;

	//! Retrieves the \copybrief mAverageDirectFreeKickGoals
	const stat& GetAverageDirectFreeKickGoals() const noexcept;

	//! Retrieves the \copybrief mAverageIndirectFreeKickGoals
	const stat& GetAverageIndirectFreeKickGoals() const noexcept;

	//! Retrieves the \copybrief mAverageCornerGoals
	const stat& GetAverageCornerGoals() const noexcept;

	//! Retrieves the \copybrief mAverageFarShotGoals
	const stat& GetAverageFarShotGoals() const noexcept;

	//! Retrieves the \copybrief m1vs1GKGoalProbability
	const probability& Get1vs1GKGoalProbability() const noexcept;

	//! Retrieves the \copybrief m1vs1DFGoalProbability
	const probability& Get1vs1DFGoalProbability() const noexcept;

	//! Retrieves the \copybrief mExtraCornerProbability
	const probability& GetExtraCornerProbability() const noexcept;

	/**
	 * @brief Creates the 1 on 1 vs GK chance outcome draw distribution.
	 * @param aEffectiveGKSkill Effective GK skill of the goalkeeper.
	 * @param aEffectiveMFSkill Effective MF skill of the assister.
	 * @param aEffectiveFWSkill Effective FW skill of the shot taker.
	 * @pre All effective skills must be positive.
	*/
	goal_draw_distribution Create1vs1GKOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill,
		const effective_skill& aEffectiveMFSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

	/**
	 * @brief Creates the 1 on 1 vs DF chance outcome draw distribution.
	 * @param aEffectiveGKSkill Effective GK skill of the goalkeeper.
	 * @param aEffectiveDFSkill Effective DF skill of the defender.
	 * @param aEffectiveMFSkill Effective MF skill of the assister.
	 * @param aEffectiveFWSkill Effective FW skill of the shot taker.
	 * @pre All effective skills must be positive.
	*/
	goal_draw_distribution Create1vs1DFOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill,
		const effective_skill& aEffectiveDFSkill,
		const effective_skill& aEffectiveMFSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

	/**
	 * @brief Creates a generic chance outcome draw distribution.
	 * @param aDefaultGoalProbability Goal probability when defender and attacker skills are equal.
	 * @param aEffectiveDFSkill Effective DF skill of the defender.
	 * @param aEffectiveDefenceSkill Effective defence skill.
	 * @param aEffectiveAttackSkill Effective attacking skill.
	 * @pre All effective skills must be positive.
	 * @pre The default goal probability must be smaller than the \copybrief mExtraCornerProbability
	*/
	goal_draw_distribution CreateChanceOutcomeDistribution(
		const probability& aDefaultGoalProbability,
		const effective_skill& aEffectiveDFSkill,
		const effective_skill& aEffectiveDefenceSkill,
		const effective_skill& aEffectiveAttackSkill ) const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Goal draw configuration";
	//! JSON key for the \copybrief mAverageGoals
	static inline constexpr std::string_view JSON_AVERAGE_GOALS = "Average goals";
	//! JSON key for the \copybrief mAveragePenaltyGoals
	static inline constexpr std::string_view JSON_AVERAGE_PENALTY_GOALS = "Average penalty goals";
	//! JSON key for the \copybrief mAverageDirectFreeKickGoals
	static inline constexpr std::string_view JSON_AVERAGE_DIRECT_FREE_KICK_GOALS = "Average direct free kick goals";
	//! JSON key for the \copybrief mAverageIndirectFreeKickGoals
	static inline constexpr std::string_view JSON_AVERAGE_INDIRECT_FREE_KICK_GOALS = "Average indirect free kick goals";
	//! JSON key for the \copybrief mAverageCornerGoals
	static inline constexpr std::string_view JSON_AVERAGE_CORNER_GOALS = "Average corner goals";
	//! JSON key for the \copybrief mAverageFarShotGoals
	static inline constexpr std::string_view JSON_AVERAGE_FAR_SHOT_GOALS = "Average far shot goals";
	//! JSON key for the \copybrief m1vs1GKGoalProbability
	static inline constexpr std::string_view JSON_1VS1_GK_GOAL_PROBABILITY = "1 on 1 vs GK chance goal probability";
	//! JSON key for the \copybrief m1vs1DFGoalProbability
	static inline constexpr std::string_view JSON_1VS1_DF_GOAL_PROBABILITY = "1 on 1 vs DF chance goal probability";
	//! JSON key for the \copybrief mExtraCornerProbability
	static inline constexpr std::string_view JSON_EXTRA_CORNER_PROBABILITY = "Extra corner probability";

	//! Default \copybrief mAverageGoals
	static inline constexpr stat DEFAULT_AVERAGE_GOALS = stat{ 1039 } / 380;
	//! Default \copybrief mAveragePenaltyGoals
	static inline constexpr stat DEFAULT_AVERAGE_PENALTY_GOALS = stat{ 74 } / 380;
	//! Default \copybrief mAverageDirectFreeKickGoals
	static inline constexpr stat DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS = stat{ 17 } / 380;
	//! Default \copybrief mAverageIndirectFreeKickGoals
	static inline constexpr stat DEFAULT_AVERAGE_INDIRECT_FREE_KICK_GOALS = stat{ 38 } / 380;
	//! Default \copybrief mAverageCornerGoals
	static inline constexpr stat DEFAULT_AVERAGE_CORNER_GOALS = stat{ 151 } / 380;
	//! Default \copybrief mAverageFarShotGoals
	static inline constexpr stat DEFAULT_AVERAGE_FAR_SHOT_GOALS = stat{ 147 } / 380 - DEFAULT_AVERAGE_DIRECT_FREE_KICK_GOALS;
	//! Default \copybrief m1vs1GKGoalProbability
	static inline constexpr stat DEFAULT_1VS1_GK_GOAL_PROBABILITY = 0.35;
	//! Default \copybrief m1vs1DFGoalProbability
	static inline constexpr stat DEFAULT_1VS1_DF_GOAL_PROBABILITY = 0.2;
	//! Default \copybrief mExtraCornerProbability
	static inline constexpr stat DEFAULT_EXTRA_CORNER_PROBABILITY = 0.25;

private:
	//! Average number of goals per 90 minutes.
	stat mAverageGoals;

	//! Average number of penalty goals per 90 minutes.
	stat mAveragePenaltyGoals;
	//! Average number of direct free kick goals per 90 minutes.
	stat mAverageDirectFreeKickGoals;
	//! Average number of indirect free kick goals per 90 minutes.
	stat mAverageIndirectFreeKickGoals;
	//! Average number of corner kick goals per 90 minutes.
	stat mAverageCornerGoals;
	//! Average number of far shot goals per 90 minutes.
	stat mAverageFarShotGoals;

	//! Probability to score a goal in a 1 on 1 vs GK chance.
	probability m1vs1GKGoalProbability;
	//! Probability to score a goal in a 1 on 1 vs DF chance.
	probability m1vs1DFGoalProbability;

	//! Probability to get an extra corner after any chance.
	probability mExtraCornerProbability;
};

} // futsim namespace