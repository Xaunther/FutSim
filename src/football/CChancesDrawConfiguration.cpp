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
	mAverageDirectFreeKicks( CheckNonNegativeness( aAverageDirectFreeKicks, "average number of direct free kicks" ) ),
	mSetPieceTypeDistributionParameters( { mAveragePenalties, mAverageDirectFreeKicks, CheckNonNegativeness(
		mAverageSetPieces - mAveragePenalties - mAverageDirectFreeKicks,
		"average number of set pieces minus the average number of penalties and direct free kicks" ) } )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the chances draw configuration." )

CChancesDrawConfiguration::CChancesDrawConfiguration( const json& aJSON ) try :
	mAverageChances( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_CHANCES_KEY, AVERAGE_CHANCES ), "average number of chances" ) ),
	mAverageCornerKicks( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_CORNER_KICKS_KEY, AVERAGE_CORNER_KICKS ), "average number of corner kicks" ) ),
	mAverage1vs1GKs( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_1VS1_GKS_KEY, AVERAGE_1VS1_GKS ), "average number of 1 on 1 vs GK chances" ) ),
	mAverage1vs1DFs( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_1VS1_DFS_KEY, AVERAGE_1VS1_DFS ), "average number of 1 on 1 vs DF chances" ) ),
	mAverageNearShots( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_NEAR_SHOTS_KEY, AVERAGE_NEAR_SHOTS ), "average number of near shots" ) ),
	mAverageSetPieces( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_SET_PIECES_KEY, AVERAGE_SET_PIECES ), "average number of set pieces" ) ),
	mAveragePenalties( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_PENALTIES_KEY, AVERAGE_PENALTIES ), "average number of penalties" ) ),
	mAverageDirectFreeKicks( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_DIRECT_FREE_KICKS_KEY, AVERAGE_DIRECT_FREE_KICKS ), "average number of direct free kicks" ) ),
	mSetPieceTypeDistributionParameters( { mAveragePenalties, mAverageDirectFreeKicks, CheckNonNegativeness(
		mAverageSetPieces - mAveragePenalties - mAverageDirectFreeKicks,
		"average number of set pieces minus the average number of penalties and direct free kicks" ) } )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the chances draw configuration from JSON." )

void CChancesDrawConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mAverageChances, AVERAGE_CHANCES_KEY );
	AddToJSONKey( aJSON, mAverageCornerKicks, AVERAGE_CORNER_KICKS_KEY );
	AddToJSONKey( aJSON, mAverage1vs1GKs, AVERAGE_1VS1_GKS_KEY );
	AddToJSONKey( aJSON, mAverage1vs1DFs, AVERAGE_1VS1_DFS_KEY );
	AddToJSONKey( aJSON, mAverageNearShots, AVERAGE_NEAR_SHOTS_KEY );
	AddToJSONKey( aJSON, mAverageSetPieces, AVERAGE_SET_PIECES_KEY );
	AddToJSONKey( aJSON, mAveragePenalties, AVERAGE_PENALTIES_KEY );
	AddToJSONKey( aJSON, mAverageDirectFreeKicks, AVERAGE_DIRECT_FREE_KICKS_KEY );
}

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

CChancesDrawConfiguration::set_piece_type_draw_distribution CChancesDrawConfiguration::CreateSetPieceTypeDistribution() const noexcept
{
	return set_piece_type_draw_distribution{ mSetPieceTypeDistributionParameters };
}

} // futsim::football namespace
