#pragma once

#include "IJsonable.h"

#include "types/CTacticConfiguration.h"
#include "DefaultTraits.h"

namespace futsim
{

namespace football
{
class CTacticConfiguration;
}

template <> struct default_traits<football::CTacticConfiguration>
{
protected:
	using position_penalties = football::types::CTacticConfiguration::position_penalties;
public:
	//! Default \copybrief football::CTacticConfiguration::mPositionPenalties
	static inline constexpr position_penalties POSITION_PENALTIES = { 0, -0.2, -0.4 };
};

template <> struct json_traits<football::CTacticConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Tactic configuration";
	//! JSON key for the \copybrief football::CTacticConfiguration::mTkBonus
	static inline constexpr std::string_view TK_BONUS_KEY = "Tk bonus";
	//! JSON key for the \copybrief football::CTacticConfiguration::mPsBonus
	static inline constexpr std::string_view PS_BONUS_KEY = "Ps bonus";
	//! JSON key for the \copybrief football::CTacticConfiguration::mFavourableTactics
	static inline constexpr std::string_view FAVOURABLE_TACTICS_KEY = "Favourable tactics";
	//! JSON key for the \copybrief football::CTacticConfiguration::mPositionPenalties
	static inline constexpr std::string_view POSITION_PENALTIES_KEY = "Position penalties";
};

namespace football
{

/**
 * @brief Class that configures a tactic.
*/
class CTacticConfiguration : public IJsonable, protected default_traits<CTacticConfiguration>, protected json_traits<CTacticConfiguration>
{
protected:
	using skill_bonus = types::CTacticConfiguration::skill_bonus;
	using position_penalties = types::CTacticConfiguration::position_penalties;
	using id = types::CTacticConfiguration::id;
	using ids = types::CTacticConfiguration::ids;
	using bonuses_table = types::CTacticConfiguration::bonuses_table;

public:
	/**
	 * @brief Member constructor.
	 * @param aPositionPenalties \ref mPositionPenalties
	 * @param aFavourableTactics \ref mFavourableTactics
	 * @param aTkBonus \ref mTkBonus
	 * @param aPsBonus \ref mPsBonus
	*/
	explicit CTacticConfiguration(
		const skill_bonus& aTkBonus,
		const skill_bonus& aPsBonus,
		const ids& aFavourableTactics = {},
		const position_penalties& aPositionPenalties = POSITION_PENALTIES
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CTacticConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mTkBonus
	const skill_bonus& GetTkBonus() const noexcept;

	//! Retrieves the \copybrief mPsBonus
	const skill_bonus& GetPsBonus() const noexcept;

	//! Retrieves the \copybrief mFavourableTactics
	const ids& GetFavourableTactics() const noexcept;

	//! Retrieves the \copybrief mPositionPenalties
	const position_penalties& GetPositionPenalties() const noexcept;

	/**
	 * @brief Retrieves the skill bonus for a skill in a position.
	 * @param aPlayerPosition Player position.
	 * @param aPlayerSkill Player skill.
	*/
	const skill_bonus& GetSkillBonus( const E_PLAYER_POSITION& aPlayerPosition, const E_PLAYER_SKILL& aPlayerSkill ) const noexcept;

private:
	//! \copydoc GetSkillBonus
	skill_bonus& SkillBonus( const E_PLAYER_POSITION& aPlayerPosition, const E_PLAYER_SKILL& aPlayerSkill ) noexcept;

	//! Calculates the bonuses table.
	void CalculateBonusesTable();

	//! Tk bonus.
	skill_bonus mTkBonus;
	//! Ps bonus.
	skill_bonus mPsBonus;
	//! Favourable tactic matchings.
	ids mFavourableTactics;
	//! Penalizers to unmatched skill in a position.
	position_penalties mPositionPenalties;

	//! Table containing the bonuses for each position and skill.
	bonuses_table mBonusesTable{};
};

} // football namespace

} // futsim namespace
