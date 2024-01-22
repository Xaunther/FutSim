#include "football/CPenaltyShootoutConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

CPenaltyShootoutConfiguration::CPenaltyShootoutConfiguration(
	const E_PENALTY_SEQUENCE& aPenaltySequence,
	const penalty_count& aMinPenaltyCount
) noexcept :
	mPenaltySequence( aPenaltySequence ),
	mMinPenaltyCount( aMinPenaltyCount )
{
}

CPenaltyShootoutConfiguration::CPenaltyShootoutConfiguration( const json& aJSON ) try :
	mPenaltySequence( ValueFromRequiredJSONKey<E_PENALTY_SEQUENCE>( aJSON, JSON_SEQUENCE ) ),
	mMinPenaltyCount( ValueFromRequiredJSONKey<penalty_count>( aJSON, JSON_MIN_PENALTY_COUNT ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the penalty shootout configuration from JSON." )

void CPenaltyShootoutConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mPenaltySequence, JSON_SEQUENCE );
	AddToJSONKey( aJSON, mMinPenaltyCount, JSON_MIN_PENALTY_COUNT );
}

const E_PENALTY_SEQUENCE& CPenaltyShootoutConfiguration::GetPenaltySequence() const noexcept
{
	return mPenaltySequence;
}

const CPenaltyShootoutConfigurationTypes::penalty_count& CPenaltyShootoutConfiguration::GetMinPenaltyCount() const noexcept
{
	return mMinPenaltyCount;
}

} // futsim::football namespace