#include "football/CMatchConfiguration.h"

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
	const benched_count& aBenchedPlayersCount,
	const bool aApplyAmbientFactor,
	const optional_tie_condition& aTieCondition,
	const optional_extra_time& aExtraTime,
	const optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration,
	const CDrawConfiguration& aDrawConfiguration
) try :
	mPlayTime( aPlayTime ),
	mBenchedPlayersCount( aBenchedPlayersCount ),
	mApplyAmbientFactor( aApplyAmbientFactor ),
	mTieCondition( CheckTieCondition( aTieCondition, aPenaltyShootoutConfiguration ) ),
	mExtraTime( aExtraTime ),
	mPenaltyShootoutConfiguration( aPenaltyShootoutConfiguration ),
	mDrawConfiguration( aDrawConfiguration )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match configuration." )

CMatchConfiguration::CMatchConfiguration( const json& aJSON ) try :
	mPlayTime( ValueFromRequiredJSONKey<CPlayTime>( aJSON ) ),
	mBenchedPlayersCount( ValueFromOptionalJSONKey<benched_count>( aJSON, JSON_BENCHED_PLAYERS, {} ) ),
	mApplyAmbientFactor( ValueFromRequiredJSONKey<bool>( aJSON, JSON_APPLY_AMBIENT_FACTOR ) ),
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
	if( mBenchedPlayersCount )
		AddToJSONKey( aJSON, *mBenchedPlayersCount, JSON_BENCHED_PLAYERS );
	AddToJSONKey( aJSON, mApplyAmbientFactor, JSON_APPLY_AMBIENT_FACTOR );
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

const CMatchConfiguration::benched_count& CMatchConfiguration::GetBenchedPlayersCount() const noexcept
{
	return mBenchedPlayersCount;
}

bool CMatchConfiguration::AppliesAmbientFactor() const noexcept
{
	return mApplyAmbientFactor;
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