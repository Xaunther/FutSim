#include "football/CFoulDrawConfiguration.h"

namespace futsim::football
{

const CFoulDrawConfiguration::stat& CFoulDrawConfiguration::GetAverageFouls() const noexcept
{
	return mAverageFouls;
}

const CFoulDrawConfiguration::stat& CFoulDrawConfiguration::GetAverageYellowCards() const noexcept
{
	return mAverageYellowCards;
}

const CFoulDrawConfiguration::stat& CFoulDrawConfiguration::GetAverageRedCards() const noexcept
{
	return mAverageRedCards;
}

} // futsim::football namespace