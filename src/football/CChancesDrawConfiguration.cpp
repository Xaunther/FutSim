#include "football/CChancesDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NumberUtils.h"

namespace futsim::football
{

CChancesDrawConfiguration::CChancesDrawConfiguration(
	const stat& aAverageChances,
	const stat& aAverageCornerKicks,
	const stat& aAverage1vs1GKs,
	const stat& aAverage1vs1DFs,
	const stat& aAverageNearShots,
	const stat& aAverageSetPieces,
	const stat& aAveragePenalties,
	const stat& aAverageDirectFreeKicks
) try :
	mAverageChances( CheckNonNegativeness( aAverageChances, "average number of chances" ) ),
	mAverageCornerKicks( CheckNonNegativeness( aAverageCornerKicks, "average number of corner kicks" ) ),
	mAverage1vs1GKs( CheckNonNegativeness( aAverage1vs1GKs, "average number of 1 on 1 vs GK chances" ) ),
	mAverage1vs1DFs( CheckNonNegativeness( aAverage1vs1DFs, "average number of 1 on 1 vs DF chances" ) ),
	mAverageNearShots( CheckNonNegativeness( aAverageNearShots, "average number of near shots" ) ),
	mAverageSetPieces( CheckNonNegativeness( aAverageSetPieces, "average number of set pieces" ) ),
	mAveragePenalties( CheckNonNegativeness( aAveragePenalties, "average number of penalties" ) ),
	mAverageDirectFreeKicks( CheckNonNegativeness( aAverageDirectFreeKicks, "average number of direct free kicks" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the chances draw configuration." )

CChancesDrawConfiguration::CChancesDrawConfiguration( const json& aJSON ) try :
	mAverageChances( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_CHANCES, DEFAULT_AVERAGE_CHANCES ), "average number of chances" ) ),
	mAverageCornerKicks( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_CORNER_KICKS, DEFAULT_AVERAGE_CORNER_KICKS ), "average number of corner kicks" ) ),
	mAverage1vs1GKs( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_1VS1_GKS, DEFAULT_AVERAGE_1VS1_GKS ), "average number of 1 on 1 vs GK chances" ) ),
	mAverage1vs1DFs( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_1VS1_DFS, DEFAULT_AVERAGE_1VS1_DFS ), "average number of 1 on 1 vs DF chances" ) ),
	mAverageNearShots( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_NEAR_SHOTS, DEFAULT_AVERAGE_NEAR_SHOTS ), "average number of near shots" ) ),
	mAverageSetPieces( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_SET_PIECES, DEFAULT_AVERAGE_SET_PIECES ), "average number of set pieces" ) ),
	mAveragePenalties( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_PENALTIES, DEFAULT_AVERAGE_PENALTIES ), "average number of penalties" ) ),
	mAverageDirectFreeKicks( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, JSON_AVERAGE_DIRECT_FREE_KICKS, DEFAULT_AVERAGE_DIRECT_FREE_KICKS ), "average number of direct free kicks" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the chances draw configuration from JSON." )

const CChancesDrawConfiguration::stat& CChancesDrawConfiguration::GetAverageChances() const noexcept
{
	return mAverageChances;
}

const CChancesDrawConfiguration::stat& CChancesDrawConfiguration::GetAverageCornerKicks() const noexcept
{
	return mAverageCornerKicks;
}

const CChancesDrawConfiguration::stat& CChancesDrawConfiguration::GetAverage1vs1GKs() const noexcept
{
	return mAverage1vs1GKs;
}

const CChancesDrawConfiguration::stat& CChancesDrawConfiguration::GetAverage1vs1DFs() const noexcept
{
	return mAverage1vs1DFs;
}

const CChancesDrawConfiguration::stat& CChancesDrawConfiguration::GetAverageNearShots() const noexcept
{
	return mAverageNearShots;
}

const CChancesDrawConfiguration::stat& CChancesDrawConfiguration::GetAverageSetPieces() const noexcept
{
	return mAverageSetPieces;
}

const CChancesDrawConfiguration::stat& CChancesDrawConfiguration::GetAveragePenalties() const noexcept
{
	return mAveragePenalties;
}

const CChancesDrawConfiguration::stat& CChancesDrawConfiguration::GetAverageDirectFreeKicks() const noexcept
{
	return mAverageDirectFreeKicks;
}

} // futsim::football namespace