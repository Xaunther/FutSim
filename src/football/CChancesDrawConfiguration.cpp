#include "football/CChancesDrawConfiguration.h"

namespace futsim::football
{

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