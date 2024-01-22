#include "football/EGoalRule.h"

#include <string>
#include <unordered_map>

namespace futsim::football
{

//! Map to convert goal rule to string.
const std::unordered_map<E_GOAL_RULE, std::string> TO_STRING_CONVERSION_MAP{
	{E_GOAL_RULE::NO,"No"},
	{E_GOAL_RULE::SILVER_GOAL,"Silver goal"},
	{E_GOAL_RULE::GOLDEN_GOAL,"Golden goal"},
};
//! Map to convert string to goal rule.
const std::unordered_map<std::string, E_GOAL_RULE> TO_PENALTY_SEQUENCE_CONVERSION_MAP{
	{"No",E_GOAL_RULE::NO},
	{"Silver goal",E_GOAL_RULE::SILVER_GOAL},
	{"Golden goal",E_GOAL_RULE::GOLDEN_GOAL},
};

} // futsim::football namespace
