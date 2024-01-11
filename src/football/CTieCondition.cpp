#include "football/CTieCondition.h"

#include <utility>

#include "ExceptionUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Checks correctness of the home team goals
 * @param aHomeTeamGoals Home team goals.
 * @param aHomeTeamLead Home team lead.
*/
const CTieConditionTypes::optional_goal_count& CheckHomeTeamGoals(
	const CTieConditionTypes::optional_goal_count& aHomeTeamGoals,
	const CTieConditionTypes::goal_difference aHomeTeamLead );

} // anonymous namespace

CTieCondition::CTieCondition(
	const goal_difference aHomeTeamLead,
	const optional_goal_count& aHomeTeamGoals
) try :
	mHomeTeamLead( aHomeTeamLead ),
	mHomeTeamGoals( CheckHomeTeamGoals( aHomeTeamGoals, mHomeTeamLead ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tie conditions." )

namespace
{

const CTieConditionTypes::optional_goal_count& CheckHomeTeamGoals(
	const CTieConditionTypes::optional_goal_count& aHomeTeamGoals,
	const CTieConditionTypes::goal_difference aHomeTeamLead ) try
{
	if( aHomeTeamGoals && std::cmp_less( *aHomeTeamGoals, aHomeTeamLead ) )
		throw std::invalid_argument( "The home team goals cannot be smaller than the home team lead." );
	return aHomeTeamGoals;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the home team lead." )

} // anonymous namespace

} // futsim::football namespace