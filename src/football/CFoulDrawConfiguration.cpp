#include "football/CFoulDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "NumberUtils.h"

namespace futsim::football
{

CFoulDrawConfiguration::CFoulDrawConfiguration(
	const stat& aAverageFouls,
	const stat& aAverageYellowCards,
	const stat& aAverageRedCards
) try :
	mAverageFouls( CheckNonNegativeness( aAverageFouls, "average number of fouls" ) ),
	mAverageYellowCards( CheckNonNegativeness( aAverageYellowCards, "average number of yellow cards" ) ),
	mAverageRedCards( CheckNonNegativeness( aAverageRedCards, "average number of red cards" ) )
{
	CheckNonNegativeness( mAverageFouls - mAverageYellowCards - mAverageRedCards, "average number of fouls minus the average number of yellow and red cards" );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the foul draw configuration." )

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