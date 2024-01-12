#include "football/PenaltySequenceUtils.h"

#include "PenaltySequenceConversionMaps.h"

#include "ExceptionUtils.h"

#include <unordered_map>

namespace futsim::football
{

const std::string& ToString( const E_PENALTY_SEQUENCE& aPenaltySequence ) noexcept
{
	return TO_STRING_CONVERSION_MAP.at( aPenaltySequence );
}

const E_PENALTY_SEQUENCE& ToPenaltySequence( const std::string_view aPenaltySequence ) try
{
	return TO_PENALTY_SEQUENCE_CONVERSION_MAP.at( aPenaltySequence.data() );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::out_of_range, "No penalty sequence matching the string '" << aPenaltySequence << "'." )

} // futsim::football namespace
