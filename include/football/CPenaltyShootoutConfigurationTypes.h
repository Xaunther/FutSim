#pragma once

namespace futsim::football::CPenaltyShootoutConfigurationTypes
{

//! Enumeration for the penalty sequence.
enum class E_SEQUENCE {
	AB,
	ABBA
};
//! Type for the number of penalties.
using penalty_count = unsigned int;

} // futsim::football::CPenaltyShootoutConfigurationTypes namespace