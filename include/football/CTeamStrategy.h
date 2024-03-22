#pragma once

#include "IJsonable.h"

#include "football/CLineup.h"
#include "football/types/CTacticConfiguration.h"

namespace futsim::football
{

class CMatch;
class CMatchConfiguration;

/**
 * @brief Class that defines a team strategy.
*/
class CTeamStrategy : public IJsonable
{
protected:
	using id = types::CTacticConfiguration::id;
	using skill_bonus = types::CTacticConfiguration::skill_bonus;

public:
	/**
	 * @brief Member constructor.
	 * @param aTacticID \ref mTacticID
	 * @param aLineup \ref mLineup
	*/
	explicit CTeamStrategy(
		const std::string_view aTacticID,
		const CLineup& aLineup
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CTeamStrategy( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mTacticID
	std::string_view GetTacticID() const noexcept;

	//! Retrieves the \copybrief mLineup
	const CLineup& GetLineup() const noexcept;

	/**
	 * @brief Applies the given predicate to the effective skill of each player.
	 * @param aPlayerSkill Player skill to consider.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aIsHomeTeam Whether the team is the home team.
	 * @param aOtherStrategy Rival team's strategy.
	 * @param aPredicate Predicate to evaluate.
	 * @pre The current team strategy must pass \ref CMatchConfiguration::CheckTeamStrategy.
	 * @pre The current team strategy must pass \ref CMatch::CheckTeamStrategy.
	*/
	void ForEachPlayerSkill( const E_PLAYER_SKILL& aPlayerSkill, const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration, const bool aIsHomeTeam, const CTeamStrategy& aOtherStrategy,
		const std::function<void( const skill_bonus& )>& aPredicate ) const;

public:
	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Team strategy";
	//! JSON key for the \copybrief mTacticID
	static inline constexpr std::string_view JSON_TACTIC = "Tactic";

private:
	//! Used tactic ID.
	id mTacticID;
	//! Lineup.
	CLineup mLineup;
};

} // futsim::football namespace