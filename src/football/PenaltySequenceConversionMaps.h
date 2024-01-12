#include "football/EPenaltySequence.h"

#include <string>
#include <unordered_map>

namespace futsim::football
{

//! Map to convert penalty sequence to string.
const std::unordered_map<E_PENALTY_SEQUENCE, std::string> TO_STRING_CONVERSION_MAP{
	{E_PENALTY_SEQUENCE::AB,"AB"},
	{E_PENALTY_SEQUENCE::ABBA,"ABBA"},
};
//! Map to convert string to penalty sequence.
const std::unordered_map<std::string, E_PENALTY_SEQUENCE> TO_PENALTY_SEQUENCE_CONVERSION_MAP{
	{"AB",E_PENALTY_SEQUENCE::AB},
	{"ABBA",E_PENALTY_SEQUENCE::ABBA},
};

} // futsim::football namespace
