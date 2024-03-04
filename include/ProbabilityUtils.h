#pragma once

#include "ExceptionUtils.h"
#include "NumberUtils.h"

namespace futsim
{

/**
 * @brief Checks if the value can represent a probability.
 * @param aValue Value.
 * @param aNameString String with the name label to add to the error message.
*/
const auto& CheckProbability( const auto& aValue, const std::string_view aNameString ) try
{
	CheckNonNegativeness( aValue, aNameString );
	if( aValue > 1 )
		throw std::invalid_argument{ "The " + std::string( aNameString.data() ) + " cannot be greater than 1." };
	return aValue;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " + std::string( aNameString.data() ) + "." )

} // futsim namespace