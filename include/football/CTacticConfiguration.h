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
	using skill_bonuses = CTacticConfigurationTypes::skill_bonuses;
	using id = CTacticConfigurationTypes::id;
	using ids = CTacticConfigurationTypes::ids;

public:
	//! Retrieves the \copybrief mTkBonus
	const skill_bonus& GetTkBonus() const noexcept;

	//! Retrieves the \copybrief mPsBonus
	const skill_bonus& GetPsBonus() const noexcept;

	//! Retrieves the \copybrief mFavourableTactics
	const ids& GetFavourableTactics() const noexcept;

	//! Retrieves the \copybrief mPositionPenalties
	const skill_bonuses& GetPositionPenalties() const noexcept;

private:
	//! Tk bonus.
	skill_bonus mTkBonus;
	//! Ps bonus.
	skill_bonus mPsBonus;
	//! Favourable tactic matchings.
	ids mFavourableTactics;
	//! Penalizers to unmatched skill in a position.
	skill_bonuses mPositionPenalties;
};

} // futsim namespace