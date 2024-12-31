#include "football/CMatchConfiguration.h"

#include "football/CTeamStrategy.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Checks that a penalty shootout configuration exists to break tie condition.
 * @param aTieCondition Tie condition.
 * @param aPenaltyShootoutConfiguration Penalty shootout configuration.
*/
const types::CMatchConfiguration::optional_tie_condition& CheckTieCondition(
	const types::CMatchConfiguration::optional_tie_condition& aTieCondition,
	const types::CMatchConfiguration::optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration );

/**
 * @brief Checks that the extra time is only configured with a tie condition.
 * @param aExtraTime Extra time configuration.
 * @param aTieCondition Tie condition.
*/
const types::CMatchConfiguration::optional_extra_time& CheckExtraTime(
	const types::CMatchConfiguration::optional_extra_time& aExtraTime,
	const types::CMatchConfiguration::optional_tie_condition& aTieCondition );

/**
 * @brief Checks that the penalty shootout is only configured with a tie condition.
 * @param aPenaltyShootoutConfiguration Penalty shootout configuration.
 * @param aTieCondition Tie condition.
*/
const types::CMatchConfiguration::optional_penalty_shootout_configuration& CheckPenaltyShootoutConfiguration(
	const types::CMatchConfiguration::optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration,
	const types::CMatchConfiguration::optional_tie_condition& aTieCondition );

} // anonymous namespace

CMatchConfiguration::CMatchConfiguration(
	const CPlayTime& aPlayTime,
	const CLineupConfiguration& aLineupConfiguration,
	const bool aApplyAmbientFactor,
	const CTacticsConfiguration& aTacticsConfiguration,
	const optional_tie_condition& aTieCondition,
	const optional_extra_time& aExtraTime,
	const optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration,
	const CDrawConfiguration& aDrawConfiguration
) try :
	mPlayTime( aPlayTime ),
	mLineupConfiguration( aLineupConfiguration ),
	mApplyAmbientFactor( aApplyAmbientFactor ),
	mTacticsConfiguration( aTacticsConfiguration ),
	mTieCondition( CheckTieCondition( aTieCondition, aPenaltyShootoutConfiguration ) ),
	mExtraTime( CheckExtraTime( aExtraTime, mTieCondition ) ),
	mPenaltyShootoutConfiguration( CheckPenaltyShootoutConfiguration( aPenaltyShootoutConfiguration, mTieCondition ) ),
	mDrawConfiguration( aDrawConfiguration )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match configuration." )

CMatchConfiguration::CMatchConfiguration( const json& aJSON ) try :
	mPlayTime( ValueFromOptionalJSONKey<CPlayTime>( aJSON ) ),
	mLineupConfiguration( ValueFromOptionalJSONKey<CLineupConfiguration>( aJSON ) ),
	mApplyAmbientFactor( ValueFromOptionalJSONKey<bool>( aJSON, APPLY_AMBIENT_FACTOR_KEY, APPLY_AMBIENT_FACTOR ) ),
	mTacticsConfiguration( ValueFromOptionalJSONKey<CTacticsConfiguration>( aJSON ) ),
	mTieCondition( ValueFromOptionalJSONKey<optional_tie_condition>( aJSON, json_traits<CTieCondition>::KEY, {} ) ),
	mExtraTime( CheckExtraTime( ValueFromOptionalJSONKey<optional_extra_time>( aJSON, json_traits<CExtraTime>::KEY, {} ), mTieCondition ) ),
	mPenaltyShootoutConfiguration( CheckPenaltyShootoutConfiguration(
		ValueFromOptionalJSONKey<optional_penalty_shootout_configuration>( aJSON, json_traits<CPenaltyShootoutConfiguration>::KEY, {} ), mTieCondition ) ),
	mDrawConfiguration( ValueFromOptionalJSONKey<CDrawConfiguration>( aJSON ) )
{
	CheckTieCondition( mTieCondition, mPenaltyShootoutConfiguration );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match configuration from JSON." )

void CMatchConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mPlayTime );
	AddToJSONKey( aJSON, mLineupConfiguration );
	AddToJSONKey( aJSON, mApplyAmbientFactor, APPLY_AMBIENT_FACTOR_KEY );
	AddToJSONKey( aJSON, mTacticsConfiguration );
	if( mTieCondition )
		AddToJSONKey( aJSON, *mTieCondition );
	if( mExtraTime )
		AddToJSONKey( aJSON, *mExtraTime );
	if( mPenaltyShootoutConfiguration )
		AddToJSONKey( aJSON, *mPenaltyShootoutConfiguration );
	AddToJSONKey( aJSON, mDrawConfiguration );
}

const CPlayTime& CMatchConfiguration::GetPlayTime() const noexcept
{
	return mPlayTime;
}

const CLineupConfiguration& CMatchConfiguration::GetLineupConfiguration() const noexcept
{
	return mLineupConfiguration;
}

bool CMatchConfiguration::AppliesAmbientFactor() const noexcept
{
	return mApplyAmbientFactor;
}

const CTacticsConfiguration& CMatchConfiguration::GetTacticsConfiguration() const noexcept
{
	return mTacticsConfiguration;
}

const CMatchConfiguration::optional_tie_condition& CMatchConfiguration::GetTieCondition() const noexcept
{
	return mTieCondition;
}

const CMatchConfiguration::optional_extra_time& CMatchConfiguration::GetExtraTime() const noexcept
{
	return mExtraTime;
}

const CMatchConfiguration::optional_penalty_shootout_configuration& CMatchConfiguration::GetPenaltyShootoutConfiguration() const noexcept
{
	return mPenaltyShootoutConfiguration;
}

const CDrawConfiguration& CMatchConfiguration::GetDrawConfiguration() const noexcept
{
	return mDrawConfiguration;
}

const CTeamStrategy& CMatchConfiguration::CheckTeamStrategy( const CTeamStrategy& aTeamStrategy ) const try
{
	if( !mTacticsConfiguration.GetTacticConfigurations().contains( aTeamStrategy.GetTacticID().data() ) )
		throw std::invalid_argument( "The tactic '" + std::string{ aTeamStrategy.GetTacticID() } + "' has not been configured." );
	mLineupConfiguration.CheckLineup( aTeamStrategy.GetLineup() );
	return aTeamStrategy;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the team strategy against the configuration." )

namespace
{

const types::CMatchConfiguration::optional_tie_condition& CheckTieCondition(
	const types::CMatchConfiguration::optional_tie_condition& aTieCondition,
	const types::CMatchConfiguration::optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration ) try
{
	if( aTieCondition && !aPenaltyShootoutConfiguration )
		throw std::invalid_argument( "There cannot be a tie condition without a penalty shootout configuration." );
	return aTieCondition;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the tie condition." )

const types::CMatchConfiguration::optional_extra_time& CheckExtraTime(
	const types::CMatchConfiguration::optional_extra_time& aExtraTime,
	const types::CMatchConfiguration::optional_tie_condition& aTieCondition ) try
{
	if( aExtraTime && !aTieCondition )
		throw std::invalid_argument( "There cannot be extra time without a tie condition." );
	return aExtraTime;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the extra time configuration." )

const types::CMatchConfiguration::optional_penalty_shootout_configuration& CheckPenaltyShootoutConfiguration(
	const types::CMatchConfiguration::optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration,
	const types::CMatchConfiguration::optional_tie_condition& aTieCondition ) try
{
	if( aPenaltyShootoutConfiguration && !aTieCondition )
		throw std::invalid_argument( "There cannot be a penalty shootout without a tie condition." );
	return aPenaltyShootoutConfiguration;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the penalty shootout configuration." )

} // anonymous namespace

} // futsim::football namespace
