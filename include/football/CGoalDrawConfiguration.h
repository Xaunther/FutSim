#pragma once

#include "IJsonable.h"

#include "football/CGoalDrawConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that configures the draws of the outcomes of every chance.
*/
class CGoalDrawConfiguration : public IJsonable
{
protected:
	using probability = CGoalDrawConfigurationTypes::probability;
	using stat = CGoalDrawConfigurationTypes::stat;

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
	static inline constexpr stat DEFAULT_AVERAGE_FAR_SHOT_GOALS = stat{ 147 } / 380;
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