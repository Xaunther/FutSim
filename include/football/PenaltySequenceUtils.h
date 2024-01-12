#pragma once

#include "EPenaltySequence.h"

#include <string>

namespace futsim::football
{

/**
 * @brief Converts the penalty sequence enum into a string.
 * @param aPenaltySequence Penalty sequence enum.
*/
const std::string& ToString( const E_PENALTY_SEQUENCE& aPenaltySequence ) noexcept;

/**
 * @brief Converts the penalty sequence string into enum.
 * @param aPenaltySequence Penalty sequence string.
*/
const E_PENALTY_SEQUENCE& ToPenaltySequence( const std::string_view aPenaltySequence );


} // futsim::football namespace
