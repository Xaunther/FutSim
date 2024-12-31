#pragma once

#include "IJsonable.h"
#include "traits/json.h"

#include "types/CTieCondition.h"

#include <optional>

namespace futsim
{

namespace football
{
class CTieCondition;
}

template <> struct json_traits<football::CTieCondition>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Tie condition";
	//! JSON key for the \copybrief football::CTieCondition::mHomeTeamLead
	static inline constexpr std::string_view HOME_TEAM_LEAD_KEY = "Home team lead";
	//! JSON key for the \copybrief football::CTieCondition::mHomeTeamGoals
	static inline constexpr std::string_view HOME_TEAM_GOALS_KEY = "Home team goals";
};

namespace football
{

/**
 * @brief Class that defines a tie condition for a match.
 * @details A match resulting in a tie condition should go on to undo the tie.
*/
class CTieCondition : public IJsonable, protected json_traits<CTieCondition>
{
protected:
	using goal_difference = types::CTieCondition::goal_difference;
	using goal_count = types::CTieCondition::goal_count;
	using optional_goal_count = types::CTieCondition::optional_goal_count;

public:
	/**
	 * @brief Member constructor.
	 * @param aHomeTeamLead \ref mHomeTeamLead
	 * @param aHomeTeamGoals \ref mHomeTeamGoals
	*/
	explicit CTieCondition(
		const goal_difference aHomeTeamLead = goal_difference{},
		const optional_goal_count& aHomeTeamGoals = {} );

	/**
	 * @brief Constructor from a previous match result.
	 * @details Assumes that the home team in the previous match now is the away team, and vice versa.
	 * @param aHomeGoals Home team goal tally in the previous match.
	 * @param aAwayGoals Away team goal tally in the previous match.
	 * @param aUseAwayGoalsRule Whether away goals rule applies.
	*/
	explicit CTieCondition(
		const goal_count aHomeGoals,
		const goal_count aAwayGoals,
		bool aUseAwayGoalsRule ) noexcept;

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
	//! Retrieves the \copybrief mHomeTeamLead
	const goal_difference& GetHomeTeamLead() const noexcept;

	//! Retrieves the \copybrief mHomeTeamGoals
	const optional_goal_count& GetHomeTeamGoals() const noexcept;

	/**
	 * @brief Evaluates the tie condition for a given match result.
	 * @param aHomeGoals Home team goal tally.
	 * @param aAwayGoals Away team goal tally.
	*/
	bool operator() ( const goal_count aHomeGoals, const goal_count aAwayGoals ) const noexcept;

private:
	//! Home team goal lead that results in a tie.
	goal_difference mHomeTeamLead;
	//! Number of goals of the home team that results in a tie.
	optional_goal_count mHomeTeamGoals;
};

} // football namespace

} // futsim namespace
