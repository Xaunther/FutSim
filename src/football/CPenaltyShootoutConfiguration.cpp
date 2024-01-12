#include "football/CPenaltyShootoutConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "football/PenaltySequenceUtils.h"

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
	mPenaltySequence( ToPenaltySequence( ValueFromRequiredJSONKey<std::string_view>( aJSON, JSON_SEQUENCE ) ) ),
	mMinPenaltyCount( ValueFromRequiredJSONKey<penalty_count>( aJSON, JSON_MIN_PENALTY_COUNT ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the penalty shootout configuration from JSON." )

void CPenaltyShootoutConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, ToString( mPenaltySequence ), JSON_SEQUENCE );
	AddToJSONKey( aJSON, mMinPenaltyCount, JSON_MIN_PENALTY_COUNT );
}

} // futsim::football namespace