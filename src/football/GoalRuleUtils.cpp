#include "football/GoalRuleUtils.h"

#include "GoalRuleConversionMaps.h"

#include "ExceptionUtils.h"

#include <unordered_map>

namespace futsim::football
{

const std::string& ToString( const E_GOAL_RULE& aGoalRule ) noexcept
{
	return TO_STRING_CONVERSION_MAP.at( aGoalRule );
}

const E_GOAL_RULE& ToGoalRule( const std::string_view aGoalRule ) try
{
	return TO_PENALTY_SEQUENCE_CONVERSION_MAP.at( aGoalRule.data() );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::out_of_range, "No goal rule matching the string '" << aGoalRule << "'." )

} // futsim::football namespace
