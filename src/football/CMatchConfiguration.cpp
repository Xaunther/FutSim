#include "football/CMatchConfiguration.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Checks that a penalty shootout configuration exists to break tie condition.
 * @param aTieCondition Tie condition.
 * @param aPenaltyShootoutConfiguration Penalty shootout configuration.
*/
const CMatchConfigurationTypes::optional_tie_condition& CheckTieCondition(
	const CMatchConfigurationTypes::optional_tie_condition& aTieCondition,
	const CMatchConfigurationTypes::optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration );

} // anonymous namespace

CMatchConfiguration::CMatchConfiguration(
	const CPlayTime& aPlayTime,
	const benched_count& aBenchedPlayersCount,
	const bool aApplyAmbientFactor,
	const optional_tie_condition& aTieCondition,
	const optional_extra_time& aExtraTime,
	const optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration
) try :
	mPlayTime( aPlayTime ),
	mBenchedPlayersCount( aBenchedPlayersCount ),
	mApplyAmbientFactor( aApplyAmbientFactor ),
	mTieCondition( CheckTieCondition( aTieCondition, aPenaltyShootoutConfiguration ) ),
	mExtraTime( aExtraTime ),
	mPenaltyShootoutConfiguration( aPenaltyShootoutConfiguration )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match configuration." )

namespace
{

const CMatchConfigurationTypes::optional_tie_condition& CheckTieCondition(
	const CMatchConfigurationTypes::optional_tie_condition& aTieCondition,
	const CMatchConfigurationTypes::optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration ) try
{
	if( aTieCondition && !aPenaltyShootoutConfiguration )
		throw std::invalid_argument( "There cannot be a tie condition without a penalty shootout configuration." );
	return aTieCondition;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the tie condition." )

} // anonymous namespace

} // futsim::football namespace