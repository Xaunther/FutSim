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
		aJSON, json_traits<CChancesDrawConfiguration>::AVERAGE_CHANCES, default_traits<CChancesDrawConfiguration>::AVERAGE_CHANCES ), "average number of chances" ) ),
	mAverageCornerKicks( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, json_traits<CChancesDrawConfiguration>::AVERAGE_CORNER_KICKS, default_traits<CChancesDrawConfiguration>::AVERAGE_CORNER_KICKS ), "average number of corner kicks" ) ),
	mAverage1vs1GKs( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, json_traits<CChancesDrawConfiguration>::AVERAGE_1VS1_GKS, default_traits<CChancesDrawConfiguration>::AVERAGE_1VS1_GKS ), "average number of 1 on 1 vs GK chances" ) ),
	mAverage1vs1DFs( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, json_traits<CChancesDrawConfiguration>::AVERAGE_1VS1_DFS, default_traits<CChancesDrawConfiguration>::AVERAGE_1VS1_DFS ), "average number of 1 on 1 vs DF chances" ) ),
	mAverageNearShots( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, json_traits<CChancesDrawConfiguration>::AVERAGE_NEAR_SHOTS, default_traits<CChancesDrawConfiguration>::AVERAGE_NEAR_SHOTS ), "average number of near shots" ) ),
	mAverageSetPieces( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, json_traits<CChancesDrawConfiguration>::AVERAGE_SET_PIECES, default_traits<CChancesDrawConfiguration>::AVERAGE_SET_PIECES ), "average number of set pieces" ) ),
	mAveragePenalties( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, json_traits<CChancesDrawConfiguration>::AVERAGE_PENALTIES, default_traits<CChancesDrawConfiguration>::AVERAGE_PENALTIES ), "average number of penalties" ) ),
	mAverageDirectFreeKicks( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, json_traits<CChancesDrawConfiguration>::AVERAGE_DIRECT_FREE_KICKS, default_traits<CChancesDrawConfiguration>::AVERAGE_DIRECT_FREE_KICKS ), "average number of direct free kicks" ) ),
	mSetPieceTypeDistributionParameters( { mAveragePenalties, mAverageDirectFreeKicks, CheckNonNegativeness(
		mAverageSetPieces - mAveragePenalties - mAverageDirectFreeKicks,
		"average number of set pieces minus the average number of penalties and direct free kicks" ) } )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the chances draw configuration from JSON." )

void CChancesDrawConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mAverageChances, json_traits<CChancesDrawConfiguration>::AVERAGE_CHANCES );
	AddToJSONKey( aJSON, mAverageCornerKicks, json_traits<CChancesDrawConfiguration>::AVERAGE_CORNER_KICKS );
	AddToJSONKey( aJSON, mAverage1vs1GKs, json_traits<CChancesDrawConfiguration>::AVERAGE_1VS1_GKS );
	AddToJSONKey( aJSON, mAverage1vs1DFs, json_traits<CChancesDrawConfiguration>::AVERAGE_1VS1_DFS );
	AddToJSONKey( aJSON, mAverageNearShots, json_traits<CChancesDrawConfiguration>::AVERAGE_NEAR_SHOTS );
	AddToJSONKey( aJSON, mAverageSetPieces, json_traits<CChancesDrawConfiguration>::AVERAGE_SET_PIECES );
	AddToJSONKey( aJSON, mAveragePenalties, json_traits<CChancesDrawConfiguration>::AVERAGE_PENALTIES );
	AddToJSONKey( aJSON, mAverageDirectFreeKicks, json_traits<CChancesDrawConfiguration>::AVERAGE_DIRECT_FREE_KICKS );
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