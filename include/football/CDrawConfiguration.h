#pragma once

#include "IJsonable.h"
#include "football/traits/CDrawConfiguration.h"

#include "football/types/CPossessionDrawConfiguration.h"

#include "football/CChancesDrawConfiguration.h"
#include "football/CFoulDrawConfiguration.h"
#include "football/CGoalDrawConfiguration.h"
#include "football/CPossessionDrawConfiguration.h"

namespace futsim::football
{

/**
 * @brief Class that configures the draws of a match.
*/
class CDrawConfiguration : public IJsonable, protected json_traits<CDrawConfiguration>
{
protected:
	using effective_skill = types::CDrawConfiguration::effective_skill;
	using probability = types::CDrawConfiguration::probability;
	using possession_draw_distribution = types::CPossessionDrawConfiguration::possession_draw_distribution;
	using chance_type_draw_distribution = types::CChancesDrawConfiguration::chance_type_draw_distribution;
	using goal_draw_distribution = types::CGoalDrawConfiguration::goal_draw_distribution;

public:
	/**
	 * @brief Member constructor.
	 * @param aPossessionDrawConfiguration \ref mPossessionDrawConfiguration
	 * @param aFoulDrawConfiguration \ref mFoulDrawConfiguration
	 * @param aChancesDrawConfiguration \ref mChancesDrawConfiguration
	 * @param aGoalDrawConfiguration \ref mGoalDrawConfiguration
	*/
	explicit CDrawConfiguration(
		const CPossessionDrawConfiguration& aPossessionDrawConfiguration = CPossessionDrawConfiguration{},
		const CFoulDrawConfiguration& aFoulDrawConfiguration = CFoulDrawConfiguration{},
		const CChancesDrawConfiguration& aChancesDrawConfiguration = CChancesDrawConfiguration{},
		const CGoalDrawConfiguration& aGoalDrawConfiguration = CGoalDrawConfiguration{}
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CDrawConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPossessionDrawConfiguration
	const CPossessionDrawConfiguration& GetPossessionDrawConfiguration() const noexcept;

	//! Retrieves the \copybrief mFoulDrawConfiguration
	const CFoulDrawConfiguration& GetFoulDrawConfiguration() const noexcept;

	//! Retrieves the \copybrief mChancesDrawConfiguration
	const CChancesDrawConfiguration& GetChancesDrawConfiguration() const noexcept;

	//! Retrieves the \copybrief mGoalDrawConfiguration
	const CGoalDrawConfiguration& GetGoalDrawConfiguration() const noexcept;

	/**
	 * @brief Creates the possession draw distribution.
	 * @param aEffectiveDFSkill Effective DF skill of the defending team.
	 * @param aEffectiveMFSkill Effective MF skill of the attacking team.
	 * @pre All effective skills must be positive.
	*/
	possession_draw_distribution CreatePossessionDistribution(
		const effective_skill& aEffectiveDFSkill,
		const effective_skill& aEffectiveMFSkill ) const noexcept;

	//! \copydoc CFoulDrawConfiguration::CreateFoulDistribution
	types::CFoulDrawConfiguration::foul_draw_distribution CreateFoulDistribution() const noexcept;

	/**
	 * @brief Creates the set piece draw distribution.
	 * @details The list of outcomes is {set piece, no set piece}.
	*/
	std::bernoulli_distribution CreateSetPieceDistribution() const noexcept;

	/**
	 * @brief Creates the chance draw distribution.
	 * @details The list of outcomes is {chance, no chance}.
	 * @param aEffectiveDFSkill Effective DF skill of the defending team.
	 * @param aEffectiveFWSkill Effective FW skill of the attacking team.
	 * @pre All effective skills must be positive.
	*/
	std::bernoulli_distribution CreateChanceDistribution(
		const effective_skill& aEffectiveDFSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

	//! \copydoc CChancesDrawConfiguration::CreateSetPieceTypeDistribution
	types::CChancesDrawConfiguration::set_piece_type_draw_distribution CreateSetPieceTypeDistribution() const noexcept;

	//! Creates the chance type draw distribution.
	chance_type_draw_distribution CreateChanceTypeDistribution() const noexcept;

	/**
	 * @brief Creates the penalty chance outcome distribution.
	 * @param aEffectiveGKSkill Effective GK skill of the goalkeeper.
	 * @param aEffectiveFWSkill Effective FW skill of the shot taker.
	 * @pre All effective skills must be positive.
	*/
	goal_draw_distribution CreatePenaltyOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill, const effective_skill& aEffectiveFWSkill ) const noexcept;

	/**
	 * @brief Creates the direct free kick chance outcome distribution.
	 * @param aEffectiveGKSkill Effective GK skill of the goalkeeper.
	 * @param aEffectiveFWSkill Effective FW skill of the shot taker.
	 * @pre All effective skills must be positive.
	*/
	goal_draw_distribution CreateDirectFreeKickOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill, const effective_skill& aEffectiveFWSkill ) const noexcept;

	/**
	 * @brief Creates the indirect free kick chance outcome distribution.
	 * @param aEffectiveGKSkill Effective GK skill of the goalkeeper.
	 * @param aEffectiveDFSkill Effective DF skill of the defender.
	 * @param aEffectiveMFSkill Effective MF skill of the foul kicker.
	 * @param aEffectiveFWSkill Effective FW skill of the shot taker.
	 * @pre All effective skills must be positive.
	*/
	goal_draw_distribution CreateIndirectFreeKickOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill,
		const effective_skill& aEffectiveDFSkill,
		const effective_skill& aEffectiveMFSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

	/**
	 * @brief Creates the corner chance outcome distribution.
	 * @param aEffectiveGKSkill Effective GK skill of the goalkeeper.
	 * @param aEffectiveDFSkill Effective DF skill of the defender.
	 * @param aEffectiveMFSkill Effective MF skill of the corner kicker.
	 * @param aEffectiveFWSkill Effective FW skill of the shot taker.
	 * @pre All effective skills must be positive.
	*/
	goal_draw_distribution CreateCornerOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill,
		const effective_skill& aEffectiveDFSkill,
		const effective_skill& aEffectiveMFSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

	/**
	 * @brief Creates the far shot chance outcome distribution.
	 * @param aEffectiveGKSkill Effective GK skill of the goalkeeper.
	 * @param aEffectiveFWSkill Effective FW skill of the shot taker.
	 * @pre All effective skills must be positive.
	*/
	goal_draw_distribution CreateFarShotOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

	//! \copybrief CGoalDrawConfiguration::Create1vs1GKOutcomeDistribution
	goal_draw_distribution Create1vs1GKOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill,
		const effective_skill& aEffectiveMFSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

	//! \copybrief CGoalDrawConfiguration::Create1vs1DFOutcomeDistribution
	goal_draw_distribution Create1vs1DFOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill,
		const effective_skill& aEffectiveDFSkill,
		const effective_skill& aEffectiveMFSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

	/**
	 * @brief Creates the near shot chance outcome distribution.
	 * @param aEffectiveGKSkill Effective GK skill of the goalkeeper.
	 * @param aEffectiveFWSkill Effective FW skill of the shot taker.
	 * @pre All effective skills must be positive.
	*/
	goal_draw_distribution CreateNearShotOutcomeDistribution(
		const effective_skill& aEffectiveGKSkill,
		const effective_skill& aEffectiveFWSkill ) const noexcept;

private:
	//! Possession draw configuration.
	CPossessionDrawConfiguration mPossessionDrawConfiguration;
	//! Foul draw configuration.
	CFoulDrawConfiguration mFoulDrawConfiguration;
	//! Chances draw configuration.
	CChancesDrawConfiguration mChancesDrawConfiguration;
	//! Goal draw configuration.
	CGoalDrawConfiguration mGoalDrawConfiguration;

	//! Set piece distribution parameters.
	std::bernoulli_distribution::param_type mSetPieceDistributionParameters;

	//! Default chance distribution parameters.
	std::bernoulli_distribution::param_type mDefaultChanceDistributionParameters;

	//! Chance type distribution parameters.
	chance_type_draw_distribution::param_type mChanceTypeDistributionParameters;

	//! Default goal probability from penalty.
	probability mDefaultPenaltyGoalProbability;
	//! Default goal probability from direct free kick.
	probability mDefaultDirectFreeKickGoalProbability;
	//! Default goal probability from indirect free kick.
	probability mDefaultIndirectFreeKickGoalProbability;
	//! Default goal probability from corner.
	probability mDefaultCornerGoalProbability;
	//! Default goal probability from far shot.
	probability mDefaultFarShotGoalProbability;
	//! Default goal probability from near shot.
	probability mDefaultNearShotGoalProbability;
};

} // futsim::football namespace
