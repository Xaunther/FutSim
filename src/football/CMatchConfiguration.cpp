#include "football/CMatchConfiguration.h"

#include "football/CMatchStrategy.h"

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
const CMatchConfigurationTypes::optional_tie_condition& CheckTieCondition(
	const CMatchConfigurationTypes::optional_tie_condition& aTieCondition,
	const CMatchConfigurationTypes::optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration );

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
	mExtraTime( aExtraTime ),
	mPenaltyShootoutConfiguration( aPenaltyShootoutConfiguration ),
	mDrawConfiguration( aDrawConfiguration )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match configuration." )

CMatchConfiguration::CMatchConfiguration( const json& aJSON ) try :
	mPlayTime( ValueFromOptionalJSONKey<CPlayTime>( aJSON ) ),
	mLineupConfiguration( ValueFromOptionalJSONKey<CLineupConfiguration>( aJSON ) ),
	mApplyAmbientFactor( ValueFromOptionalJSONKey<bool>( aJSON, JSON_APPLY_AMBIENT_FACTOR, DEFAULT_APPLY_AMBIENT_FACTOR ) ),
	mTacticsConfiguration( ValueFromOptionalJSONKey<CTacticsConfiguration>( aJSON ) ),
	mTieCondition( ValueFromOptionalJSONKey<optional_tie_condition>( aJSON, CTieCondition::JSON_KEY, {} ) ),
	mExtraTime( ValueFromOptionalJSONKey<optional_extra_time>( aJSON, CExtraTime::JSON_KEY, {} ) ),
	mPenaltyShootoutConfiguration( ValueFromOptionalJSONKey<optional_penalty_shootout_configuration>( aJSON, CPenaltyShootoutConfiguration::JSON_KEY, {} ) ),
	mDrawConfiguration( ValueFromOptionalJSONKey<CDrawConfiguration>( aJSON ) )
{
	CheckTieCondition( mTieCondition, mPenaltyShootoutConfiguration );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match configuration from JSON." )

void CMatchConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mPlayTime );
	AddToJSONKey( aJSON, mLineupConfiguration );
	AddToJSONKey( aJSON, mApplyAmbientFactor, JSON_APPLY_AMBIENT_FACTOR );
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

const CMatchStrategy& CMatchConfiguration::CheckMatchStrategy( const CMatchStrategy& aMatchStrategy ) const try
{
	if( !mTacticsConfiguration.GetTacticConfigurations().contains( aMatchStrategy.GetTacticID() ) )
		throw std::invalid_argument( "The tactic '" + aMatchStrategy.GetTacticID() + "' has not been configured." );
	mLineupConfiguration.CheckLineup( aMatchStrategy.GetLineup() );
	return aMatchStrategy;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the match strategy against the configuration." )

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