#pragma once

#include "IJsonable.h"

#include "football/types/CDrawConfiguration.h"
#include "football/types/CGoalDrawConfiguration.h"

#include "football/EPlayerSkill.h"
#include "DefaultTraits.h"

namespace futsim
{

namespace football
{
class CGoalDrawConfiguration;
}

template <> struct default_traits<football::CGoalDrawConfiguration>
{
protected:
	using stat = football::types::CDrawConfiguration::stat;
public:
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageGoals
	static inline constexpr stat AVERAGE_GOALS = stat{ 1039 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAveragePenaltyGoals
	static inline constexpr stat AVERAGE_PENALTY_GOALS = stat{ 74 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageDirectFreeKickGoals
	static inline constexpr stat AVERAGE_DIRECT_FREE_KICK_GOALS = stat{ 17 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageIndirectFreeKickGoals
	static inline constexpr stat AVERAGE_INDIRECT_FREE_KICK_GOALS = stat{ 38 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageCornerGoals
	static inline constexpr stat AVERAGE_CORNER_GOALS = stat{ 151 } / 380;
	//! Default \copybrief football::CGoalDrawConfiguration::mAverageFarShotGoals
	static inline constexpr stat AVERAGE_FAR_SHOT_GOALS = stat{ 147 } / 380 - AVERAGE_DIRECT_FREE_KICK_GOALS;
	//! Default \copybrief football::CGoalDrawConfiguration::m1vs1GKGoalProbability
	static inline constexpr stat ONE_VS_ONE_GK_GOAL_PROBABILITY = 0.35;
	//! Default \copybrief football::CGoalDrawConfiguration::m1vs1DFGoalProbability
	static inline constexpr stat ONE_VS_ONE_DF_GOAL_PROBABILITY = 0.2;
	//! Default \copybrief football::CGoalDrawConfiguration::mExtraCornerProbability
	static inline constexpr stat EXTRA_CORNER_PROBABILITY = 0.25;
};

template <> struct json_traits<football::CGoalDrawConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Goal draw configuration";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageGoals
	static inline constexpr std::string_view AVERAGE_GOALS_KEY = "Average goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAveragePenaltyGoals
	static inline constexpr std::string_view AVERAGE_PENALTY_GOALS_KEY = "Average penalty goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageDirectFreeKickGoals
	static inline constexpr std::string_view AVERAGE_DIRECT_FREE_KICK_GOALS_KEY = "Average direct free kick goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageIndirectFreeKickGoals
	static inline constexpr std::string_view AVERAGE_INDIRECT_FREE_KICK_GOALS_KEY = "Average indirect free kick goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageCornerGoals
	static inline constexpr std::string_view AVERAGE_CORNER_GOALS_KEY = "Average corner goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mAverageFarShotGoals
	static inline constexpr std::string_view AVERAGE_FAR_SHOT_GOALS_KEY = "Average far shot goals";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::m1vs1GKGoalProbability
	static inline constexpr std::string_view ONE_VS_ONE_GK_GOAL_PROBABILITY_KEY = "1 on 1 vs GK chance goal probability";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::m1vs1DFGoalProbability
	static inline constexpr std::string_view ONE_VS_ONE_DF_GOAL_PROBABILITY_KEY = "1 on 1 vs DF chance goal probability";
	//! JSON key for the \copybrief football::CGoalDrawConfiguration::mExtraCornerProbability
	static inline constexpr std::string_view EXTRA_CORNER_PROBABILITY_KEY = "Extra corner probability";
};

namespace football
{

/**
 * @brief Class that configures the draws of the outcomes of every chance.
*/
class CGoalDrawConfiguration : public IJsonable, protected default_traits<CGoalDrawConfiguration>, protected json_traits<CGoalDrawConfiguration>
{
protected:
	using probability = types::CDrawConfiguration::probability;
	using stat = types::CDrawConfiguration::stat;
	using effective_skill = types::CDrawConfiguration::effective_skill;
	using goal_draw_distribution = types::CGoalDrawConfiguration::goal_draw_distribution;
	using position_draw_distribution = types::CGoalDrawConfiguration::position_draw_distribution;

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
		const stat& aAverageGoals = AVERAGE_GOALS,
		const stat& aAveragePenaltyGoals = AVERAGE_PENALTY_GOALS,
		const stat& aAverageDirectFreeKickGoals = AVERAGE_DIRECT_FREE_KICK_GOALS,
		const stat& aAverageIndirectFreeKickGoals = AVERAGE_INDIRECT_FREE_KICK_GOALS,
		const stat& aAverageCornerGoals = AVERAGE_CORNER_GOALS,
		const stat& aAverageFarShotGoals = AVERAGE_FAR_SHOT_GOALS,
		const stat& a1vs1GKGoalProbability = ONE_VS_ONE_GK_GOAL_PROBABILITY,
		const stat& a1vs1DFGoalProbability = ONE_VS_ONE_DF_GOAL_PROBABILITY,
		const stat& aExtraCornerProbability = EXTRA_CORNER_PROBABILITY
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

	/**
	 * @brief Create the position draw distribution for a given player skill.
	 * @tparam tPlayerSkill Player skill.
	*/
	template <E_PLAYER_SKILL tPlayerSkill>
	position_draw_distribution CreatePositionDrawDistribution() const noexcept;

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

} // football namespace

} // futsim namespace
