#include "football/CFoulDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NumberUtils.h"
#include "ProbabilityUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Calculates the foul probability per minute.
 * @param aAverageFouls Average number of fouls per 90 minutes.
*/
types::CDrawConfiguration::probability CalculateFoulProbability( const types::CDrawConfiguration::stat& aAverageFouls );

} // anonymous namespace

CFoulDrawConfiguration::CFoulDrawConfiguration(
	const stat& aAverageFouls,
	const stat& aAverageYellowCards,
	const stat& aAverageRedCards
) try :
	mAverageFouls( CheckNonNegativeness( aAverageFouls, "average number of fouls" ) ),
	mAverageYellowCards( CheckNonNegativeness( aAverageYellowCards, "average number of yellow cards" ) ),
	mAverageRedCards( CheckNonNegativeness( aAverageRedCards, "average number of red cards" ) ),
	mFoulProbability( CalculateFoulProbability( mAverageFouls ) ),
	mFoulDistributionParameters( { mAverageYellowCards, mAverageRedCards, CheckNonNegativeness(
		mAverageFouls - mAverageYellowCards - mAverageRedCards, "average number of fouls minus the average number of yellow and red cards" ) } )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the foul draw configuration." )

CFoulDrawConfiguration::CFoulDrawConfiguration( const json& aJSON ) try :
	mAverageFouls( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_FOULS_KEY, AVERAGE_FOULS ), "average number of fouls" ) ),
	mAverageYellowCards( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_YELLOW_CARDS_KEY, AVERAGE_YELLOW_CARDS ), "average number of yellow cards" ) ),
	mAverageRedCards( CheckNonNegativeness( ValueFromOptionalJSONKey<stat>(
		aJSON, AVERAGE_RED_CARDS_KEY, AVERAGE_RED_CARDS ), "average number of red cards" ) ),
	mFoulProbability( CalculateFoulProbability( mAverageFouls ) ),
	mFoulDistributionParameters( { mAverageYellowCards, mAverageRedCards, CheckNonNegativeness(
		mAverageFouls - mAverageYellowCards - mAverageRedCards, "average number of fouls minus the average number of yellow and red cards" ) } )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the foul draw configuration from JSON." )

void CFoulDrawConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mAverageFouls, AVERAGE_FOULS_KEY );
	AddToJSONKey( aJSON, mAverageYellowCards, AVERAGE_YELLOW_CARDS_KEY );
	AddToJSONKey( aJSON, mAverageRedCards, AVERAGE_RED_CARDS_KEY );
}

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

const CFoulDrawConfiguration::probability& CFoulDrawConfiguration::GetFoulProbability() const noexcept
{
	return mFoulProbability;
}

CFoulDrawConfiguration::foul_draw_distribution CFoulDrawConfiguration::CreateFoulDistribution() const noexcept
{
	return foul_draw_distribution{ mFoulDistributionParameters };
}

namespace
{

types::CDrawConfiguration::probability CalculateFoulProbability( const types::CDrawConfiguration::stat& aAverageFouls )
{
	return CheckProbability( aAverageFouls / CFoulDrawConfiguration::MATCH_MINUTES, "foul probability" );
}

} // anonymous namespace

} // futsim::football namespace
