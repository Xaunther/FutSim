#pragma once

#include "IJsonable.h"

#include "CTieConditionTypes.h"

#include <optional>

namespace futsim::football
{

/**
 * @brief Class that defines a tie condition for a match.
 * @details A match resulting in a tie condition should go on to undo the tie.
*/
class CTieCondition : public IJsonable
{
	using goal_difference = CTieConditionTypes::goal_difference;
	using optional_goal_count = CTieConditionTypes::optional_goal_count;

public:
	/**
	 * @brief Member constructor.
	 * @param aHomeTeamLead \ref mHomeTeamLead
	 * @param aHomeTeamGoals \ref mHomeTeamGoals
	*/
	explicit CTieCondition(
		const goal_difference aHomeTeamLead = 0,
		const optional_goal_count& aHomeTeamGoals = {} );

private:
	//! Home team goal lead that results in a tie.
	goal_difference mHomeTeamLead;
	//! Number of goals of the home team that results in a tie.
	optional_goal_count mHomeTeamGoals;
};

} // futsim::football namespace