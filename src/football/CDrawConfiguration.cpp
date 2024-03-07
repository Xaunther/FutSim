#include "football/CDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "ProbabilityUtils.h"

namespace futsim::football
{

CDrawConfiguration::CDrawConfiguration(
	const CPossessionDrawConfiguration& aPossessionDrawConfiguration,
	const CFoulDrawConfiguration& aFoulDrawConfiguration,
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const CGoalDrawConfiguration& aGoalDrawConfiguration
) try :
	mPossessionDrawConfiguration( aPossessionDrawConfiguration ),
	mFoulDrawConfiguration( aFoulDrawConfiguration ),
	mChancesDrawConfiguration( aChancesDrawConfiguration ),
	mGoalDrawConfiguration( aGoalDrawConfiguration )
{
	CheckProbability( mPossessionDrawConfiguration.GetKeepPossessionProbability() + mFoulDrawConfiguration.GetFoulProbability(),
		"joint probability of keeping possession or receiving a foul" );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the draw configuration." )

CDrawConfiguration::CDrawConfiguration( const json& aJSON ) try :
	mPossessionDrawConfiguration( ValueFromOptionalJSONKey<CPossessionDrawConfiguration>( aJSON ) ),
	mFoulDrawConfiguration( ValueFromOptionalJSONKey<CFoulDrawConfiguration>( aJSON ) ),
	mChancesDrawConfiguration( ValueFromOptionalJSONKey<CChancesDrawConfiguration>( aJSON ) ),
	mGoalDrawConfiguration( ValueFromOptionalJSONKey<CGoalDrawConfiguration>( aJSON ) )
{
	CheckProbability( mPossessionDrawConfiguration.GetKeepPossessionProbability() + mFoulDrawConfiguration.GetFoulProbability(),
		"joint probability of keeping possession or receiving a foul" );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the draw configuration from JSON." )

void CDrawConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mPossessionDrawConfiguration );
	AddToJSONKey( aJSON, mFoulDrawConfiguration );
	AddToJSONKey( aJSON, mChancesDrawConfiguration );
	AddToJSONKey( aJSON, mGoalDrawConfiguration );
}

const CPossessionDrawConfiguration& CDrawConfiguration::GetPossessionDrawConfiguration() const noexcept
{
	return mPossessionDrawConfiguration;
}

const CFoulDrawConfiguration& CDrawConfiguration::GetFoulDrawConfiguration() const noexcept
{
	return mFoulDrawConfiguration;
}

const CChancesDrawConfiguration& CDrawConfiguration::GetChancesDrawConfiguration() const noexcept
{
	return mChancesDrawConfiguration;
}

const CGoalDrawConfiguration& CDrawConfiguration::GetGoalDrawConfiguration() const noexcept
{
	return mGoalDrawConfiguration;
}

CDrawConfiguration::discrete_distribution CDrawConfiguration::CreatePossessionDistribution(
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveMFSkill ) const noexcept
{
	const auto& modifiedKeepPossessionProbability = ModifiedProbability(
		1 - mFoulDrawConfiguration.GetFoulProbability(),
		mPossessionDrawConfiguration.GetKeepPossessionProbability(),
		aEffectiveDFSkill, aEffectiveMFSkill );
	return discrete_distribution{
		modifiedKeepPossessionProbability,
		mFoulDrawConfiguration.GetFoulProbability(),
		1 - modifiedKeepPossessionProbability - mFoulDrawConfiguration.GetFoulProbability()
	};
}

} // futsim::football namespace