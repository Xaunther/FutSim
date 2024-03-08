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

/**
 * @brief Calculates the chance type distribution parameters.
 * @param aChancesDrawConfiguration Configuration of the chances draw.
 * @param aExtraCornerProbability Extra corner probability after a chance.
 * @param aFoulProbability Foul probability.
 * @param aSetPieceProbability Set piece probability.
 * @param aDefaultChanceProbability Default chance probability after keeping possession or launching a counter attack.
*/
CDrawConfigurationTypes::discrete_distribution::param_type CalculateChanceTypeDistributionParameters(
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const CDrawConfigurationTypes::probability& aExtraCornerProbability,
	const CDrawConfigurationTypes::probability& aFoulProbability,
	const CDrawConfigurationTypes::probability& aSetPieceProbability,
	const CDrawConfigurationTypes::probability& aDefaultChanceProbability );

/**
 * @brief Calculates the default goal probability from a penalty.
 * @param aAveragePenaltyGoals Average number of penalty goals per 90 minutes.
 * @param aAveragePenalties Average number of penalties per 90 minutes.
*/
CDrawConfigurationTypes::probability CalculateDefaultPenaltyGoalProbability(
	const CDrawConfigurationTypes::stat& aAveragePenaltyGoals,
	const CDrawConfigurationTypes::stat& aAveragePenalties );

/**
 * @brief Calculates the default goal probability from a direct free kick.
 * @param aAverageDirectFreeKickGoals Average number of direct free kick goals per 90 minutes.
 * @param aAverageDirectFreeKicks Average number of direct free kick per 90 minutes.
*/
CDrawConfigurationTypes::probability CalculateDefaultDirectFreeKickGoalProbability(
	const CDrawConfigurationTypes::stat& aAverageDirectFreeKickGoals,
	const CDrawConfigurationTypes::stat& aAverageDirectFreeKicks );

/**
* @brief Calculates the default goal probability from an indirect free kick.
* @param aAverageIndirectFreeKickGoals Average number of direct free kick goals per 90 minutes.
* @param aChancesDrawConfiguration Configuration of the chances draw.
*/
CDrawConfigurationTypes::probability CalculateDefaultIndirectFreeKickGoalProbability(
	const CDrawConfigurationTypes::stat& aAverageIndirectFreeKickGoals,
	const CChancesDrawConfiguration& aChancesDrawConfiguration );

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
		mSetPieceDistributionParameters.p() ) ),
	mChanceTypeDistributionParameters( CalculateChanceTypeDistributionParameters( mChancesDrawConfiguration,
		mGoalDrawConfiguration.GetExtraCornerProbability(), mFoulDrawConfiguration.GetFoulProbability(),
		mSetPieceDistributionParameters.p(), mDefaultChanceDistributionParameters.p() ) ),
	mDefaultPenaltyGoalProbability( CalculateDefaultPenaltyGoalProbability(
		mGoalDrawConfiguration.GetAveragePenaltyGoals(), mChancesDrawConfiguration.GetAveragePenalties() ) ),
	mDefaultDirectFreeKickGoalProbability( CalculateDefaultDirectFreeKickGoalProbability(
		mGoalDrawConfiguration.GetAverageDirectFreeKickGoals(), mChancesDrawConfiguration.GetAverageDirectFreeKicks() ) ),
	mDefaultIndirectFreeKickGoalProbability( CalculateDefaultIndirectFreeKickGoalProbability(
		mGoalDrawConfiguration.GetAverageIndirectFreeKickGoals(), mChancesDrawConfiguration ) )
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
		mSetPieceDistributionParameters.p() ) ),
	mChanceTypeDistributionParameters( CalculateChanceTypeDistributionParameters( mChancesDrawConfiguration,
		mGoalDrawConfiguration.GetExtraCornerProbability(), mFoulDrawConfiguration.GetFoulProbability(),
		mSetPieceDistributionParameters.p(), mDefaultChanceDistributionParameters.p() ) ),
	mDefaultPenaltyGoalProbability( CalculateDefaultPenaltyGoalProbability(
		mGoalDrawConfiguration.GetAveragePenaltyGoals(), mChancesDrawConfiguration.GetAveragePenalties() ) ),
	mDefaultDirectFreeKickGoalProbability( CalculateDefaultDirectFreeKickGoalProbability(
		mGoalDrawConfiguration.GetAverageDirectFreeKickGoals(), mChancesDrawConfiguration.GetAverageDirectFreeKicks() ) ),
	mDefaultIndirectFreeKickGoalProbability( CalculateDefaultIndirectFreeKickGoalProbability(
		mGoalDrawConfiguration.GetAverageIndirectFreeKickGoals(), mChancesDrawConfiguration ) )
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

CDrawConfiguration::discrete_distribution CDrawConfiguration::CreateSetPieceTypeDistribution() const noexcept
{
	return mChancesDrawConfiguration.CreateSetPieceTypeDistribution();
}

CDrawConfiguration::discrete_distribution CDrawConfiguration::CreateChanceTypeDistribution() const noexcept
{
	return discrete_distribution{ mChanceTypeDistributionParameters };
}

CDrawConfiguration::discrete_distribution CDrawConfiguration::CreatePenaltyOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill, const effective_skill& aEffectiveFWSkill ) const noexcept
{
	const auto modifiedProbability = ModifiedProbability( 1 - mGoalDrawConfiguration.GetExtraCornerProbability(),
		mDefaultPenaltyGoalProbability, aEffectiveGKSkill, aEffectiveFWSkill );
	return discrete_distribution{ modifiedProbability,
		mGoalDrawConfiguration.GetExtraCornerProbability(),
		( 1 - modifiedProbability - mGoalDrawConfiguration.GetExtraCornerProbability() ) / 2,
		( 1 - modifiedProbability - mGoalDrawConfiguration.GetExtraCornerProbability() ) / 2
	};
}

CDrawConfiguration::discrete_distribution CDrawConfiguration::CreateDirectFreeKickOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill, const effective_skill& aEffectiveFWSkill ) const noexcept
{
	const auto modifiedProbability = ModifiedProbability( 1 - mGoalDrawConfiguration.GetExtraCornerProbability(),
		mDefaultDirectFreeKickGoalProbability, aEffectiveGKSkill, aEffectiveFWSkill );
	return discrete_distribution{ modifiedProbability,
		mGoalDrawConfiguration.GetExtraCornerProbability(),
		( 1 - modifiedProbability - mGoalDrawConfiguration.GetExtraCornerProbability() ) / 2,
		( 1 - modifiedProbability - mGoalDrawConfiguration.GetExtraCornerProbability() ) / 2
	};
}

CDrawConfiguration::discrete_distribution CDrawConfiguration::CreateIndirectFreeKickOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	const auto modifiedProbability = ModifiedProbability( 1 - mGoalDrawConfiguration.GetExtraCornerProbability(),
		mDefaultIndirectFreeKickGoalProbability, aEffectiveGKSkill + aEffectiveDFSkill, aEffectiveMFSkill + aEffectiveFWSkill );
	return discrete_distribution{ modifiedProbability,
		mGoalDrawConfiguration.GetExtraCornerProbability(),
		( 1 - modifiedProbability - mGoalDrawConfiguration.GetExtraCornerProbability() ) / 2,
		( 1 - modifiedProbability - mGoalDrawConfiguration.GetExtraCornerProbability() ) / 2
	};
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

CDrawConfigurationTypes::discrete_distribution::param_type CalculateChanceTypeDistributionParameters(
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const CDrawConfigurationTypes::probability& aExtraCornerProbability,
	const CDrawConfigurationTypes::probability& aFoulProbability,
	const CDrawConfigurationTypes::probability& aSetPieceProbability,
	const CDrawConfigurationTypes::probability& aDefaultChanceProbability ) try
{
	const auto averageExtraCorners = CFoulDrawConfiguration::MATCH_MINUTES * ( aExtraCornerProbability / ( 1 - aExtraCornerProbability ) )
		* ( aDefaultChanceProbability * ( 1 - aFoulProbability ) + aFoulProbability * aSetPieceProbability );
	const auto averageOpenPlayChances = aChancesDrawConfiguration.GetAverageChances() - averageExtraCorners - aChancesDrawConfiguration.GetAverageSetPieces();

	std::array<double, 5> result{
		CheckProbability( ( ( ( 1 - aExtraCornerProbability ) * ( aChancesDrawConfiguration.GetAverageCornerKicks() / CFoulDrawConfiguration::MATCH_MINUTES ) - aExtraCornerProbability * aFoulProbability * aSetPieceProbability )
		/ ( aDefaultChanceProbability * ( 1 - aFoulProbability ) ) - aExtraCornerProbability ) / ( 1 - aExtraCornerProbability ), "corner probability" ),
		CheckProbability( aChancesDrawConfiguration.GetAverage1vs1GKs() / averageOpenPlayChances, "1 on 1 vs GK probability" ),
		CheckProbability( aChancesDrawConfiguration.GetAverage1vs1DFs() / averageOpenPlayChances, "1 on 1 vs DF probability" ),
		CheckProbability( aChancesDrawConfiguration.GetAverageNearShots() / averageOpenPlayChances, "near shot probability" )
	};
	result.back() = CheckProbability( 1 - std::accumulate( result.cbegin(), result.cend(), 0. ), "far shot probability" );
	return CDrawConfigurationTypes::discrete_distribution::param_type{ result.cbegin(), result.cend() };
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error calculating the chance type draw distribution." )

CDrawConfigurationTypes::probability CalculateDefaultPenaltyGoalProbability(
	const CDrawConfigurationTypes::stat& aAveragePenaltyGoals,
	const CDrawConfigurationTypes::stat& aAveragePenalties )
{
	return CheckProbability( aAveragePenaltyGoals / aAveragePenalties, "penalty goal probability" );
}

CDrawConfigurationTypes::probability CalculateDefaultDirectFreeKickGoalProbability(
	const CDrawConfigurationTypes::stat& aAverageDirectFreeKickGoals,
	const CDrawConfigurationTypes::stat& aAverageDirectFreeKicks )
{
	return CheckProbability( aAverageDirectFreeKickGoals / aAverageDirectFreeKicks, "direct free kick goal probability" );
}

CDrawConfigurationTypes::probability CalculateDefaultIndirectFreeKickGoalProbability(
	const CDrawConfigurationTypes::stat& aAverageIndirectFreeKickGoals,
	const CChancesDrawConfiguration& aChancesDrawConfiguration )
{
	return CheckProbability( aAverageIndirectFreeKickGoals / ( aChancesDrawConfiguration.GetAverageSetPieces()
		- aChancesDrawConfiguration.GetAveragePenalties() - aChancesDrawConfiguration.GetAverageDirectFreeKicks() ),
		"indirect free kick goal probability" );
}

} // anonymous namespace

} // futsim::football namespace