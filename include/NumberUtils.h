#pragma once

#include "ExceptionUtils.h"

namespace futsim
{

/**
 * @brief Checks non-negativeness of a number.
 * @param aNumber Number to check.
 * @param aNumberDescription Number description to add to the error message.
*/
const auto& CheckNonNegativeness( const auto& aNumber, const std::string_view aNumberDescription ) try
{
	if( aNumber < decltype( aNumber ){} )
		throw std::invalid_argument{ "The " + std::string( aNumberDescription.data() ) + " cannot be negative." };
	return aNumber;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aNumberDescription << "." )

} // futsim namespace