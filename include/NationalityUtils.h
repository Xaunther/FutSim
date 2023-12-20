#pragma once

#include "ENationality.h"

namespace futsim
{

/**
 * @brief Converts the nationality enum into a string.
 * @param aNationality Nationality enum.
*/
const std::string& ToString( const E_NATIONALITY& aNationality ) noexcept;

/**
 * @brief Converts the nationality string into enum.
 * @param aNationality Nationality string.
*/
const E_NATIONALITY& ToNationality( const std::string_view aNationality );


} // futsim namespace
