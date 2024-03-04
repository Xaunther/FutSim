#include "football/CChancesDrawConfiguration.h"

#include "ExceptionUtils.h"
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