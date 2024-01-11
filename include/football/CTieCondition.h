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
	using json = IJsonableTypes::json;
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

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CTieCondition( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Tie condition";
	//! JSON key for the \copybrief mHomeTeamLead
	static inline constexpr std::string_view JSON_HOME_TEAM_LEAD = "Home team lead";
	//! JSON key for the \copybrief mHomeTeamGoals
	static inline constexpr std::string_view JSON_HOME_TEAM_GOALS = "Home team goals";

private:
	//! Home team goal lead that results in a tie.
	goal_difference mHomeTeamLead;
	//! Number of goals of the home team that results in a tie.
	optional_goal_count mHomeTeamGoals;
};

} // futsim::football namespace