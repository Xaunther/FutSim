#pragma once

#include "IJsonable.h"

#include "football/CChancesDrawConfiguration.h"
#include "football/CFoulDrawConfiguration.h"
#include "football/CGoalDrawConfiguration.h"
#include "football/CPossessionDrawConfiguration.h"

namespace futsim::football
{

/**
 * @brief Class that configures the draws of a match.
*/
class CDrawConfiguration : public IJsonable
{
protected:
	using discrete_distribution = CDrawConfigurationTypes::discrete_distribution;
	using effective_skill = CDrawConfigurationTypes::effective_skill;

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
	 * @details The list of outcomes is {keep possession, foul, counter attack}.
	 * @param aEffectiveDFSkill Effective DF skill of the defending team.
	 * @param aEffectiveMFSkill Effective MF skill of the attacking team.
	 * @pre All effective skills must be positive.
	*/
	discrete_distribution CreatePossessionDistribution(
		const effective_skill& aEffectiveDFSkill,
		const effective_skill& aEffectiveMFSkill ) const noexcept;

	//! \copydoc CFoulDrawConfiguration::CreateFoulDistribution
	discrete_distribution CreateFoulDistribution() const noexcept;

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
	discrete_distribution CreateSetPieceTypeDistribution() const noexcept;

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
};

} // futsim namespace