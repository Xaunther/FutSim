#pragma once

#include <string_view>

namespace futsim
{

/**
 * @brief Checks correctness of the name.
 * @param aName Name.
 * @param aNameString String with the name label to add to the error message.
*/
std::string_view CheckName( const std::string_view aName, const std::string_view aNameString );

} // futsim namespace