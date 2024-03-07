#include "football/CDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "ProbabilityUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Calculates the set piece distribution parameters given a foul.
 * @param aAverageSetPieces Average number of set pieces per 90 minutes.
 * @param aAverageFouls Average number of fouls per 90 minutes.
*/
std::bernoulli_distribution::param_type CalculateSetPieceDistributionParameters( const CDrawConfigurationTypes::stat& aAverageSetPieces,
	const CDrawConfigurationTypes::stat& aAverageFouls );

/**
 * @brief Calculates the default chance distribution parameters after keeping possession or launching a counter attack.
 * @param aExtraCornerProbability Extra corner probability after a chance.
 * @param aAverageChances Average number of chances per 90 minutes.
 * @param aFoulProbability Foul probability.
 * @param aSetPieceProbability Set piece probability.
*/
std::bernoulli_distribution::param_type CalculateDefaultChanceDistributionParameters(
	const CDrawConfigurationTypes::probability& aExtraCornerProbability,
	const CDrawConfigurationTypes::stat& aAverageChances,
	const CDrawConfigurationTypes::probability& aFoulProbability,
	const CDrawConfigurationTypes::probability& aSetPieceProbability );

} // anonymous namespace

CDrawConfiguration::CDrawConfiguration(
	const CPossessionDrawConfiguration& aPossessionDrawConfiguration,
	const CFoulDrawConfiguration& aFoulDrawConfiguration,
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const CGoalDrawConfiguration& aGoalDrawConfiguration
) try :
	mPossessionDrawConfiguration( aPossessionDrawConfiguration ),
	mFoulDrawConfiguration( aFoulDrawConfiguration ),
	mChancesDrawConfiguration( aChancesDrawConfiguration ),
	mGoalDrawConfiguration( aGoalDrawConfiguration ),
	mSetPieceDistributionParameters( CalculateSetPieceDistributionParameters(
		mChancesDrawConfiguration.GetAverageSetPieces(), mFoulDrawConfiguration.GetAverageFouls() ) ),
	mDefaultChanceDistributionParameters( CalculateDefaultChanceDistributionParameters( mGoalDrawConfiguration.GetExtraCornerProbability(),
		mChancesDrawConfiguration.GetAverageChances(), mFoulDrawConfiguration.GetFoulProbability(),
		mSetPieceDistributionParameters.p() ) )
{
	CheckProbability( mPossessionDrawConfiguration.GetKeepPossessionProbability() + mFoulDrawConfiguration.GetFoulProbability(),
		"joint probability of keeping possession or receiving a foul" );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the draw configuration." )

CDrawConfiguration::CDrawConfiguration( const json& aJSON ) try :
	mPossessionDrawConfiguration( ValueFromOptionalJSONKey<CPossessionDrawConfiguration>( aJSON ) ),
	mFoulDrawConfiguration( ValueFromOptionalJSONKey<CFoulDrawConfiguration>( aJSON ) ),
	mChancesDrawConfiguration( ValueFromOptionalJSONKey<CChancesDrawConfiguration>( aJSON ) ),
	mGoalDrawConfiguration( ValueFromOptionalJSONKey<CGoalDrawConfiguration>( aJSON ) ),
	mSetPieceDistributionParameters( CalculateSetPieceDistributionParameters(
		mChancesDrawConfiguration.GetAverageSetPieces(), mFoulDrawConfiguration.GetAverageFouls() ) ),
	mDefaultChanceDistributionParameters( CalculateDefaultChanceDistributionParameters( mGoalDrawConfiguration.GetExtraCornerProbability(),
		mChancesDrawConfiguration.GetAverageChances(), mFoulDrawConfiguration.GetFoulProbability(),
		mSetPieceDistributionParameters.p() ) )
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

CDrawConfiguration::discrete_distribution CDrawConfiguration::CreateFoulDistribution() const noexcept
{
	return mFoulDrawConfiguration.CreateFoulDistribution();
}

std::bernoulli_distribution CDrawConfiguration::CreateSetPieceDistribution() const noexcept
{
	return std::bernoulli_distribution{ mSetPieceDistributionParameters };
}

std::bernoulli_distribution CDrawConfiguration::CreateChanceDistribution(
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return std::bernoulli_distribution{ ModifiedProbability(
		1., mDefaultChanceDistributionParameters.p(), aEffectiveDFSkill, aEffectiveFWSkill ) };
}

namespace
{

std::bernoulli_distribution::param_type CalculateSetPieceDistributionParameters( const CDrawConfigurationTypes::stat& aAverageSetPieces,
	const CDrawConfigurationTypes::stat& aAverageFouls )
{
	return std::bernoulli_distribution::param_type{ CheckProbability( aAverageSetPieces / aAverageFouls,
		"probability to get a set piece chance given a foul" ) };
}

std::bernoulli_distribution::param_type CalculateDefaultChanceDistributionParameters(
	const CDrawConfigurationTypes::probability& aExtraCornerProbability,
	const CDrawConfigurationTypes::stat& aAverageChances,
	const CDrawConfigurationTypes::probability& aFoulProbability,
	const CDrawConfigurationTypes::probability& aSetPieceProbability )
{
	return std::bernoulli_distribution::param_type{ CheckProbability(
		( ( 1 - aExtraCornerProbability ) * ( aAverageChances / CFoulDrawConfiguration::MATCH_MINUTES ) - aFoulProbability * aSetPieceProbability )
		/ ( 1 - aFoulProbability ), "probability to get a chance after keeping possession or launching a counter attack" ) };
}

} // anonymous namespace

} // futsim::football namespace