#pragma once

#include "IJsonable.h"

#include "CTacticConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that configures a tactic.
*/
class CTacticConfiguration : public IJsonable
{
protected:
	using skill_bonus = CTacticConfigurationTypes::skill_bonus;
	using position_penalties = CTacticConfigurationTypes::position_penalties;
	using id = CTacticConfigurationTypes::id;
	using ids = CTacticConfigurationTypes::ids;

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
		const position_penalties& aPositionPenalties = DEFAULT_POSITION_PENALTIES
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CTacticConfiguration( const json& aJSON );

	//! Retrieves the \copybrief mTkBonus
	const skill_bonus& GetTkBonus() const noexcept;

	//! Retrieves the \copybrief mPsBonus
	const skill_bonus& GetPsBonus() const noexcept;

	//! Retrieves the \copybrief mFavourableTactics
	const ids& GetFavourableTactics() const noexcept;

	//! Retrieves the \copybrief mPositionPenalties
	const position_penalties& GetPositionPenalties() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Tactic configuration";
	//! JSON key for the \copybrief mTkBonus
	static inline constexpr std::string_view JSON_TK_BONUS = "Tk bonus";
	//! JSON key for the \copybrief mPsBonus
	static inline constexpr std::string_view JSON_PS_BONUS = "Ps bonus";
	//! JSON key for the \copybrief mFavourableTactics
	static inline constexpr std::string_view JSON_FAVOURABLE_TACTICS = "Favourable tactics";
	//! JSON key for the \copybrief mPositionPenalties
	static inline constexpr std::string_view JSON_POSITION_PENALTIES = "Position penalties";

	//! Default \copybrief mPositionPenalties
	static inline constexpr position_penalties DEFAULT_POSITION_PENALTIES = { 0, -0.2, -0.4 };

private:
	//! Tk bonus.
	skill_bonus mTkBonus;
	//! Ps bonus.
	skill_bonus mPsBonus;
	//! Favourable tactic matchings.
	ids mFavourableTactics;
	//! Penalizers to unmatched skill in a position.
	position_penalties mPositionPenalties;
};

} // futsim namespace