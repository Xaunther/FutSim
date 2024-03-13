#include "football/CTieCondition.h"

#include <utility>

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Checks correctness of the home team goals.
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

CTieCondition::CTieCondition(
	const goal_count aHomeGoals,
	const goal_count aAwayGoals,
	bool aUseAwayGoalsRule
) noexcept :
	mHomeTeamLead( aHomeGoals - aAwayGoals ),
	mHomeTeamGoals( aUseAwayGoalsRule ? aHomeGoals : optional_goal_count{} )
{
}

CTieCondition::CTieCondition( const json& aJSON ) try :
	mHomeTeamLead( ValueFromOptionalJSONKey<goal_difference>( aJSON, JSON_HOME_TEAM_LEAD ) ),
	mHomeTeamGoals( CheckHomeTeamGoals( ValueFromOptionalJSONKey<optional_goal_count>( aJSON, JSON_HOME_TEAM_GOALS ), mHomeTeamLead ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tie conditions from JSON." )

void CTieCondition::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mHomeTeamLead, JSON_HOME_TEAM_LEAD );
	if( mHomeTeamGoals )
		AddToJSONKey( aJSON, *mHomeTeamGoals, JSON_HOME_TEAM_GOALS );
}

const CTieCondition::goal_difference& CTieCondition::GetHomeTeamLead() const noexcept
{
	return mHomeTeamLead;
}

const CTieCondition::optional_goal_count& CTieCondition::GetHomeTeamGoals() const noexcept
{
	return mHomeTeamGoals;
}

bool CTieCondition::operator() ( const goal_count aHomeGoals, const goal_count aAwayGoals ) const noexcept
{
	return std::cmp_equal( mHomeTeamLead + aAwayGoals, aHomeGoals )
		&& ( !mHomeTeamGoals || *mHomeTeamGoals == aHomeGoals );
}

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