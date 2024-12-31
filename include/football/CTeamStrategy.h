#pragma once

#include "IJsonable.h"
#include "football/traits/CTeamStrategy.h"

#include "football/CLineup.h"
#include "football/types/CTacticConfiguration.h"

namespace futsim::football
{

class CMatch;
class CMatchConfiguration;

/**
 * @brief Class that defines a team strategy.
*/
class CTeamStrategy : public IJsonable, protected json_traits<CTeamStrategy>
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
	 * @brief Calculates the effective player skill.
	 * @param aPlayer Player to consider.
	 * @param aPlayerSkill Player skill to consider.
	 * @param aPlayerPosition Player position.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aIsHomeTeam Whether the team is the home team.
	 * @param aTacticID Tactic used.
	 * @param aOtherStrategy Rival team's strategy.
	 * @pre The current team strategy must pass \ref CMatchConfiguration::CheckTeamStrategy.
	 * @pre The current team strategy must pass \ref CMatch::CheckTeamStrategy.
	*/
	static skill_bonus CalculateEffectivePlayerSkill( const std::string_view aPlayer, const E_PLAYER_SKILL& aPlayerSkill,
		const E_PLAYER_POSITION& aPlayerPosition, const CMatch& aMatch, const CMatchConfiguration& aMatchConfiguration,
		const bool aIsHomeTeam, const std::string_view aTacticID, const CTeamStrategy& aOtherStrategy );

	/**
	 * @brief Calculates the ambient factor
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aIsHomeTeam Whether the team is the home team.
	*/
	static skill_bonus CalculateAmbientFactor( const CMatch& aMatch, const CMatchConfiguration& aMatchConfiguration,
		const bool aIsHomeTeam );

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

private:
	//! Used tactic ID.
	id mTacticID;
	//! Lineup.
	CLineup mLineup;
};

} // futsim::football namespace
