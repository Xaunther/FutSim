#pragma once

#include <exception>
#include <sstream>

namespace futsim
{

/**
 * @brief Catches any standard exception and rethrows it as a new exception type and appending the message in a new line.
 * @param EXCEPTION_TYPE Standard exception type to throw.
 * @param EXCEPTION_MESSAGE Exception message to append in a new line.
*/
#define FUTSIM_CATCH_AND_RETHROW_EXCEPTION( EXCEPTION_TYPE, EXCEPTION_MESSAGE )	\
catch( const std::exception& aException )										\
{																				\
	std::stringstream ss;														\
	ss << aException.what() << "\n" << EXCEPTION_MESSAGE;						\
	throw EXCEPTION_TYPE( ss.str() );											\
}

} // futsim namespace