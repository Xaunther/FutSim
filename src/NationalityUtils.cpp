#include "NationalityConversionMaps.h"

#include "ExceptionUtils.h"

#include <unordered_map>

namespace futsim
{

const std::string& ToString( const E_NATIONALITY& aNationality ) noexcept
{
	return TO_STRING_CONVERSION_MAP.at( aNationality );
}

const E_NATIONALITY& ToNationality( const std::string_view aNationality ) try
{
	return TO_NATIONALITY_CONVERSION_MAP.at( aNationality.data() );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::out_of_range, "No nationality matching the code '" << aNationality << "'." )

} // futsim namespace
