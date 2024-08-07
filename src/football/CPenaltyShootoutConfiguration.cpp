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
	mPenaltySequence( ValueFromOptionalJSONKey<E_PENALTY_SEQUENCE>( aJSON, json_traits<CPenaltyShootoutConfiguration>::SEQUENCE, default_traits<CPenaltyShootoutConfiguration>::PENALTY_SEQUENCE ) ),
	mMinPenaltyCount( ValueFromOptionalJSONKey<penalty_count>( aJSON, json_traits<CPenaltyShootoutConfiguration>::MIN_PENALTY_COUNT, default_traits<CPenaltyShootoutConfiguration>::PENALTY_COUNT ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the penalty shootout configuration from JSON." )

void CPenaltyShootoutConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mPenaltySequence, json_traits<CPenaltyShootoutConfiguration>::SEQUENCE );
	AddToJSONKey( aJSON, mMinPenaltyCount, json_traits<CPenaltyShootoutConfiguration>::MIN_PENALTY_COUNT );
}

const E_PENALTY_SEQUENCE& CPenaltyShootoutConfiguration::GetPenaltySequence() const noexcept
{
	return mPenaltySequence;
}

const types::CPenaltyShootoutConfiguration::penalty_count& CPenaltyShootoutConfiguration::GetMinPenaltyCount() const noexcept
{
	return mMinPenaltyCount;
}

} // futsim::football namespace