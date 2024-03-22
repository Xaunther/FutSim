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
std::bernoulli_distribution::param_type CalculateSetPieceDistributionParameters( const types::CDrawConfiguration::stat& aAverageSetPieces,
	const types::CDrawConfiguration::stat& aAverageFouls );

/**
 * @brief Calculates the default chance distribution parameters after keeping possession or launching a counter attack.
 * @param aExtraCornerProbability Extra corner probability after a chance.
 * @param aAverageChances Average number of chances per 90 minutes.
 * @param aFoulProbability Foul probability.
 * @param aSetPieceProbability Set piece probability.
*/
std::bernoulli_distribution::param_type CalculateDefaultChanceDistributionParameters(
	const types::CDrawConfiguration::probability& aExtraCornerProbability,
	const types::CDrawConfiguration::stat& aAverageChances,
	const types::CDrawConfiguration::probability& aFoulProbability,
	const types::CDrawConfiguration::probability& aSetPieceProbability );

/**
 * @brief Calculates the chance type distribution parameters.
 * @param aChancesDrawConfiguration Configuration of the chances draw.
 * @param aExtraCornerProbability Extra corner probability after a chance.
 * @param aFoulProbability Foul probability.
 * @param aSetPieceProbability Set piece probability.
 * @param aDefaultChanceProbability Default chance probability after keeping possession or launching a counter attack.
*/
types::CChancesDrawConfiguration::chance_type_draw_distribution::param_type CalculateChanceTypeDistributionParameters(
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const types::CDrawConfiguration::probability& aExtraCornerProbability,
	const types::CDrawConfiguration::probability& aFoulProbability,
	const types::CDrawConfiguration::probability& aSetPieceProbability,
	const types::CDrawConfiguration::probability& aDefaultChanceProbability );

/**
 * @brief Calculates the default goal probability from a penalty.
 * @param aAveragePenaltyGoals Average number of penalty goals per 90 minutes.
 * @param aAveragePenalties Average number of penalties per 90 minutes.
*/
types::CDrawConfiguration::probability CalculateDefaultPenaltyGoalProbability(
	const types::CDrawConfiguration::stat& aAveragePenaltyGoals,
	const types::CDrawConfiguration::stat& aAveragePenalties );

/**
 * @brief Calculates the default goal probability from a direct free kick.
 * @param aAverageDirectFreeKickGoals Average number of direct free kick goals per 90 minutes.
 * @param aAverageDirectFreeKicks Average number of direct free kick per 90 minutes.
*/
types::CDrawConfiguration::probability CalculateDefaultDirectFreeKickGoalProbability(
	const types::CDrawConfiguration::stat& aAverageDirectFreeKickGoals,
	const types::CDrawConfiguration::stat& aAverageDirectFreeKicks );

/**
* @brief Calculates the default goal probability from an indirect free kick.
* @param aAverageIndirectFreeKickGoals Average number of direct free kick goals per 90 minutes.
* @param aChancesDrawConfiguration Configuration of the chances draw.
*/
types::CDrawConfiguration::probability CalculateDefaultIndirectFreeKickGoalProbability(
	const types::CDrawConfiguration::stat& aAverageIndirectFreeKickGoals,
	const CChancesDrawConfiguration& aChancesDrawConfiguration );

/**
 * @brief Calculates the default goal probability from a corner kick.
 * @param aAverageCornerGoals Average number of corner goals per 90 minutes.
 * @param aAverageCorners Average number of corner per 90 minutes.
*/
types::CDrawConfiguration::probability CalculateDefaultCornerGoalProbability(
	const types::CDrawConfiguration::stat& aAverageCornerGoals,
	const types::CDrawConfiguration::stat& aAverageCorners );

/**
 * @brief Calculates the default goal probability from a far shot.
 * @param aAverageFarShotGoals Average number of far shot goals per 90 minutes.
 * @param aDefaultChanceProbability Default chance probability after keeping possession or launching a counter attack.
 * @param aFarShotProbability Far shot probability when drawing a chance.
 * @param aFoulProbability Foul probability.
*/
types::CDrawConfiguration::probability CalculateDefaultFarShotGoalProbability(
	const types::CDrawConfiguration::stat& aAverageFarShotGoals,
	const types::CDrawConfiguration::probability& aDefaultChanceProbability,
	const types::CDrawConfiguration::probability& aFarShotProbability,
	const types::CDrawConfiguration::probability& aFoulProbability );

/**
 * @brief Calculates the default goal probability from a near shot.
 * @param aChancesDrawConfiguration Configuration of the chances draw.
 * @param aGoalDrawConfiguration Configuration of the goal draw.
 * @param aFoulProbability Foul probability.
 * @param aSetPieceProbability Set piece probability.
 * @param aDefaultChanceProbability Default chance probability after keeping possession or launching a counter attack.
 * @param aNearShotProbability Near shot probability when drawing a chance.
*/
types::CDrawConfiguration::probability CalculateDefaultNearShotGoalProbability(
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const CGoalDrawConfiguration& aGoalDrawConfiguration,
	const types::CDrawConfiguration::probability& aFoulProbability,
	const types::CDrawConfiguration::probability& aSetPieceProbability,
	const types::CDrawConfiguration::probability& aDefaultChanceProbability,
	const types::CDrawConfiguration::probability& aNearShotProbability );

/**
 * @brief Calculates the chance type distribution parameters.
 * @param aChancesDrawConfiguration Configuration of the chances draw.
 * @param aExtraCornerProbability Extra corner probability after a chance.
 * @param aFoulProbability Foul probability.
 * @param aSetPieceProbability Set piece probability.
 * @param aDefaultChanceProbability Default chance probability after keeping possession or launching a counter attack.
*/
types::CDrawConfiguration::stat CalculateAverageOpenPlayChances(
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const types::CDrawConfiguration::probability& aExtraCornerProbability,
	const types::CDrawConfiguration::probability& aFoulProbability,
	const types::CDrawConfiguration::probability& aSetPieceProbability,
	const types::CDrawConfiguration::probability& aDefaultChanceProbability );

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
		mGoalDrawConfiguration.GetAverageIndirectFreeKickGoals(), mChancesDrawConfiguration ) ),
	mDefaultCornerGoalProbability( CalculateDefaultCornerGoalProbability(
		mGoalDrawConfiguration.GetAverageCornerGoals(), mChancesDrawConfiguration.GetAverageCornerKicks() ) ),
	mDefaultFarShotGoalProbability( CalculateDefaultFarShotGoalProbability( mGoalDrawConfiguration.GetAverageFarShotGoals(),
		mDefaultChanceDistributionParameters.p(), mChanceTypeDistributionParameters.probabilities().back(),
		mFoulDrawConfiguration.GetFoulProbability() ) ),
	mDefaultNearShotGoalProbability( CalculateDefaultNearShotGoalProbability( mChancesDrawConfiguration, mGoalDrawConfiguration,
		mFoulDrawConfiguration.GetFoulProbability(), mSetPieceDistributionParameters.p(),
		mDefaultChanceDistributionParameters.p(), mChanceTypeDistributionParameters.probabilities()[ 3 ] ) )
{
	CheckProbability( mPossessionDrawConfiguration.GetKeepPossessionProbability() + mFoulDrawConfiguration.GetFoulProbability(),
		"joint probability of keeping possession or receiving a foul" );
	CheckProbability( mDefaultPenaltyGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a penalty" );
	CheckProbability( mDefaultDirectFreeKickGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a direct free kick" );
	CheckProbability( mDefaultIndirectFreeKickGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from an indirect free kick" );
	CheckProbability( mDefaultCornerGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a corner" );
	CheckProbability( mDefaultFarShotGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a far shot" );
	CheckProbability( mDefaultNearShotGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a near shot" );
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
		mGoalDrawConfiguration.GetAverageIndirectFreeKickGoals(), mChancesDrawConfiguration ) ),
	mDefaultCornerGoalProbability( CalculateDefaultCornerGoalProbability(
		mGoalDrawConfiguration.GetAverageCornerGoals(), mChancesDrawConfiguration.GetAverageCornerKicks() ) ),
	mDefaultFarShotGoalProbability( CalculateDefaultFarShotGoalProbability( mGoalDrawConfiguration.GetAverageFarShotGoals(),
		mDefaultChanceDistributionParameters.p(), mChanceTypeDistributionParameters.probabilities().back(),
		mFoulDrawConfiguration.GetFoulProbability() ) ),
	mDefaultNearShotGoalProbability( CalculateDefaultNearShotGoalProbability( mChancesDrawConfiguration, mGoalDrawConfiguration,
		mFoulDrawConfiguration.GetFoulProbability(), mSetPieceDistributionParameters.p(),
		mDefaultChanceDistributionParameters.p(), mChanceTypeDistributionParameters.probabilities()[ 3 ] ) )
{
	CheckProbability( mPossessionDrawConfiguration.GetKeepPossessionProbability() + mFoulDrawConfiguration.GetFoulProbability(),
		"joint probability of keeping possession or receiving a foul" );
	CheckProbability( mDefaultPenaltyGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a penalty" );
	CheckProbability( mDefaultDirectFreeKickGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a direct free kick" );
	CheckProbability( mDefaultIndirectFreeKickGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from an indirect free kick" );
	CheckProbability( mDefaultCornerGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a corner" );
	CheckProbability( mDefaultFarShotGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a far shot" );
	CheckProbability( mDefaultNearShotGoalProbability + mGoalDrawConfiguration.GetExtraCornerProbability(),
		"joint probability of scoring or getting an extra corner from a near shot" );
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

CPossessionDrawConfigurationTypes::possession_draw_distribution CDrawConfiguration::CreatePossessionDistribution(
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveMFSkill ) const noexcept
{
	const auto& modifiedKeepPossessionProbability = ModifiedProbability(
		1 - mFoulDrawConfiguration.GetFoulProbability(),
		mPossessionDrawConfiguration.GetKeepPossessionProbability(),
		aEffectiveDFSkill, aEffectiveMFSkill );
	return possession_draw_distribution{
		modifiedKeepPossessionProbability,
		mFoulDrawConfiguration.GetFoulProbability(),
		1 - modifiedKeepPossessionProbability - mFoulDrawConfiguration.GetFoulProbability()
	};
}

CFoulDrawConfigurationTypes::foul_draw_distribution CDrawConfiguration::CreateFoulDistribution() const noexcept
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

types::CChancesDrawConfiguration::set_piece_type_draw_distribution CDrawConfiguration::CreateSetPieceTypeDistribution() const noexcept
{
	return mChancesDrawConfiguration.CreateSetPieceTypeDistribution();
}

CDrawConfiguration::chance_type_draw_distribution CDrawConfiguration::CreateChanceTypeDistribution() const noexcept
{
	return chance_type_draw_distribution{ mChanceTypeDistributionParameters };
}

CDrawConfiguration::goal_draw_distribution CDrawConfiguration::CreatePenaltyOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill, const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return mGoalDrawConfiguration.CreateChanceOutcomeDistribution( mDefaultPenaltyGoalProbability, aEffectiveGKSkill, aEffectiveFWSkill );
}

CDrawConfiguration::goal_draw_distribution CDrawConfiguration::CreateDirectFreeKickOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill, const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return mGoalDrawConfiguration.CreateChanceOutcomeDistribution( mDefaultDirectFreeKickGoalProbability, aEffectiveGKSkill, aEffectiveFWSkill );
}

CDrawConfiguration::goal_draw_distribution CDrawConfiguration::CreateIndirectFreeKickOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return mGoalDrawConfiguration.CreateChanceOutcomeDistribution( mDefaultIndirectFreeKickGoalProbability,
		aEffectiveGKSkill + aEffectiveDFSkill, aEffectiveMFSkill + aEffectiveFWSkill );
}

CDrawConfiguration::goal_draw_distribution CDrawConfiguration::CreateCornerOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return mGoalDrawConfiguration.CreateChanceOutcomeDistribution( mDefaultCornerGoalProbability,
		aEffectiveGKSkill + aEffectiveDFSkill, aEffectiveMFSkill + aEffectiveFWSkill );
}

CDrawConfiguration::goal_draw_distribution CDrawConfiguration::CreateFarShotOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return mGoalDrawConfiguration.CreateChanceOutcomeDistribution( mDefaultFarShotGoalProbability,
		aEffectiveGKSkill, aEffectiveFWSkill );
}

CDrawConfiguration::goal_draw_distribution CDrawConfiguration::Create1vs1GKOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return mGoalDrawConfiguration.Create1vs1GKOutcomeDistribution( aEffectiveGKSkill, aEffectiveMFSkill, aEffectiveFWSkill );
}

CDrawConfiguration::goal_draw_distribution CDrawConfiguration::Create1vs1DFOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveDFSkill,
	const effective_skill& aEffectiveMFSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return mGoalDrawConfiguration.Create1vs1DFOutcomeDistribution( aEffectiveGKSkill, aEffectiveDFSkill, aEffectiveMFSkill, aEffectiveFWSkill );
}

CDrawConfiguration::goal_draw_distribution CDrawConfiguration::CreateNearShotOutcomeDistribution(
	const effective_skill& aEffectiveGKSkill,
	const effective_skill& aEffectiveFWSkill ) const noexcept
{
	return mGoalDrawConfiguration.CreateChanceOutcomeDistribution( mDefaultNearShotGoalProbability,
		aEffectiveGKSkill, aEffectiveFWSkill );
}

namespace
{

std::bernoulli_distribution::param_type CalculateSetPieceDistributionParameters( const types::CDrawConfiguration::stat& aAverageSetPieces,
	const types::CDrawConfiguration::stat& aAverageFouls )
{
	return std::bernoulli_distribution::param_type{ CheckProbability( aAverageSetPieces / aAverageFouls,
		"probability to get a set piece chance given a foul" ) };
}

std::bernoulli_distribution::param_type CalculateDefaultChanceDistributionParameters(
	const types::CDrawConfiguration::probability& aExtraCornerProbability,
	const types::CDrawConfiguration::stat& aAverageChances,
	const types::CDrawConfiguration::probability& aFoulProbability,
	const types::CDrawConfiguration::probability& aSetPieceProbability )
{
	return std::bernoulli_distribution::param_type{ CheckProbability(
		( ( 1 - aExtraCornerProbability ) * ( aAverageChances / CFoulDrawConfiguration::MATCH_MINUTES ) - aFoulProbability * aSetPieceProbability )
		/ ( 1 - aFoulProbability ), "probability to get a chance after keeping possession or launching a counter attack" ) };
}

types::CChancesDrawConfiguration::chance_type_draw_distribution::param_type CalculateChanceTypeDistributionParameters(
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const types::CDrawConfiguration::probability& aExtraCornerProbability,
	const types::CDrawConfiguration::probability& aFoulProbability,
	const types::CDrawConfiguration::probability& aSetPieceProbability,
	const types::CDrawConfiguration::probability& aDefaultChanceProbability ) try
{
	const auto averageOpenPlayChances = CalculateAverageOpenPlayChances( aChancesDrawConfiguration,
		aExtraCornerProbability, aFoulProbability, aSetPieceProbability, aDefaultChanceProbability );

	std::array<double, 5> result{
		CheckProbability( ( ( ( 1 - aExtraCornerProbability ) * ( aChancesDrawConfiguration.GetAverageCornerKicks() / CFoulDrawConfiguration::MATCH_MINUTES ) - aExtraCornerProbability * aFoulProbability * aSetPieceProbability )
		/ ( aDefaultChanceProbability * ( 1 - aFoulProbability ) ) - aExtraCornerProbability ) / ( 1 - aExtraCornerProbability ), "corner probability" ),
		CheckProbability( aChancesDrawConfiguration.GetAverage1vs1GKs() / averageOpenPlayChances, "1 on 1 vs GK probability" ),
		CheckProbability( aChancesDrawConfiguration.GetAverage1vs1DFs() / averageOpenPlayChances, "1 on 1 vs DF probability" ),
		CheckProbability( aChancesDrawConfiguration.GetAverageNearShots() / averageOpenPlayChances, "near shot probability" )
	};
	result.back() = CheckProbability( 1 - std::accumulate( result.cbegin(), result.cend(), 0. ), "far shot probability" );
	return types::CChancesDrawConfiguration::chance_type_draw_distribution::param_type{ result.cbegin(), result.cend() };
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error calculating the chance type draw distribution." )

types::CDrawConfiguration::probability CalculateDefaultPenaltyGoalProbability(
	const types::CDrawConfiguration::stat& aAveragePenaltyGoals,
	const types::CDrawConfiguration::stat& aAveragePenalties )
{
	return CheckProbability( aAveragePenaltyGoals / aAveragePenalties, "penalty goal probability" );
}

types::CDrawConfiguration::probability CalculateDefaultDirectFreeKickGoalProbability(
	const types::CDrawConfiguration::stat& aAverageDirectFreeKickGoals,
	const types::CDrawConfiguration::stat& aAverageDirectFreeKicks )
{
	return CheckProbability( aAverageDirectFreeKickGoals / aAverageDirectFreeKicks, "direct free kick goal probability" );
}

types::CDrawConfiguration::probability CalculateDefaultIndirectFreeKickGoalProbability(
	const types::CDrawConfiguration::stat& aAverageIndirectFreeKickGoals,
	const CChancesDrawConfiguration& aChancesDrawConfiguration )
{
	return CheckProbability( aAverageIndirectFreeKickGoals / ( aChancesDrawConfiguration.GetAverageSetPieces()
		- aChancesDrawConfiguration.GetAveragePenalties() - aChancesDrawConfiguration.GetAverageDirectFreeKicks() ),
		"indirect free kick goal probability" );
}

/**
 * @brief Calculates the default goal probability from a corner kick.
 * @param aAverageCornerGoals Average number of corner goals per 90 minutes.
 * @param aAverageCorners Average number of corner per 90 minutes.
*/
types::CDrawConfiguration::probability CalculateDefaultCornerGoalProbability(
	const types::CDrawConfiguration::stat& aAverageCornerGoals,
	const types::CDrawConfiguration::stat& aAverageCorners )
{
	return CheckProbability( aAverageCornerGoals / aAverageCorners, "corner goal probability" );
}

types::CDrawConfiguration::probability CalculateDefaultFarShotGoalProbability(
	const types::CDrawConfiguration::stat& aAverageFarShotGoals,
	const types::CDrawConfiguration::probability& aDefaultChanceProbability,
	const types::CDrawConfiguration::probability& aFarShotProbability,
	const types::CDrawConfiguration::probability& aFoulProbability )
{
	return CheckProbability( aAverageFarShotGoals /
		( CFoulDrawConfiguration::MATCH_MINUTES * aDefaultChanceProbability * aFarShotProbability * ( 1 - aFoulProbability ) ),
		"far shot goal probability" );
}

types::CDrawConfiguration::probability CalculateDefaultNearShotGoalProbability(
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const CGoalDrawConfiguration& aGoalDrawConfiguration,
	const types::CDrawConfiguration::probability& aFoulProbability,
	const types::CDrawConfiguration::probability& aSetPieceProbability,
	const types::CDrawConfiguration::probability& aDefaultChanceProbability,
	const types::CDrawConfiguration::probability& aNearShotProbability )
{
	const auto averageOpenPlayChances = CalculateAverageOpenPlayChances( aChancesDrawConfiguration, aGoalDrawConfiguration.GetExtraCornerProbability(),
		aFoulProbability, aSetPieceProbability, aDefaultChanceProbability );
	return CheckProbability( ( aGoalDrawConfiguration.GetAverageGoals() - aGoalDrawConfiguration.GetAveragePenaltyGoals()
		- aGoalDrawConfiguration.GetAverageDirectFreeKickGoals() - aGoalDrawConfiguration.GetAverageIndirectFreeKickGoals()
		- aGoalDrawConfiguration.GetAverageCornerGoals() - aGoalDrawConfiguration.GetAverageFarShotGoals()
		- aGoalDrawConfiguration.Get1vs1GKGoalProbability() * aChancesDrawConfiguration.GetAverage1vs1GKs()
		- aGoalDrawConfiguration.Get1vs1DFGoalProbability() * aChancesDrawConfiguration.GetAverage1vs1DFs() )
		/ ( averageOpenPlayChances * aNearShotProbability ),
		"near shot goal probability" );
}

types::CDrawConfiguration::stat CalculateAverageOpenPlayChances(
	const CChancesDrawConfiguration& aChancesDrawConfiguration,
	const types::CDrawConfiguration::probability& aExtraCornerProbability,
	const types::CDrawConfiguration::probability& aFoulProbability,
	const types::CDrawConfiguration::probability& aSetPieceProbability,
	const types::CDrawConfiguration::probability& aDefaultChanceProbability )
{
	const auto averageExtraCorners = CFoulDrawConfiguration::MATCH_MINUTES * ( aExtraCornerProbability / ( 1 - aExtraCornerProbability ) )
		* ( aDefaultChanceProbability * ( 1 - aFoulProbability ) + aFoulProbability * aSetPieceProbability );
	return aChancesDrawConfiguration.GetAverageChances() - averageExtraCorners - aChancesDrawConfiguration.GetAverageSetPieces();
}

} // anonymous namespace

} // futsim::football namespace