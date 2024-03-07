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

	//! Retrieves the \copybrief mPossessionDrawConfiguration
	const CPossessionDrawConfiguration& GetPossessionDrawConfiguration() const noexcept;

	//! Retrieves the \copybrief mFoulDrawConfiguration
	const CFoulDrawConfiguration& GetFoulDrawConfiguration() const noexcept;

	//! Retrieves the \copybrief mChancesDrawConfiguration
	const CChancesDrawConfiguration& GetChancesDrawConfiguration() const noexcept;

	//! Retrieves the \copybrief mGoalDrawConfiguration
	const CGoalDrawConfiguration& GetGoalDrawConfiguration() const noexcept;

private:
	//! Possession draw configuration.
	CPossessionDrawConfiguration mPossessionDrawConfiguration;
	//! Foul draw configuration.
	CFoulDrawConfiguration mFoulDrawConfiguration;
	//! Chances draw configuration.
	CChancesDrawConfiguration mChancesDrawConfiguration;
	//! Goal draw configuration.
	CGoalDrawConfiguration mGoalDrawConfiguration;
};

} // futsim namespace