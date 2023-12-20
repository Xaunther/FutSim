#include "NationalityConversionMaps.h"

#include <unordered_map>

namespace futsim
{

const std::string& ToString( const E_NATIONALITY& aNationality ) noexcept
{
	return TO_STRING_CONVERSION_MAP.at( aNationality );
}

const E_NATIONALITY& ToNationality( const std::string_view aNationality )
{
	return TO_NATIONALITY_CONVERSION_MAP.at( aNationality.data() );
}

} // futsim namespace
