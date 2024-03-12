#pragma once

#include "IJsonable.h"

#include "football/CTacticConfiguration.h"
#include "football/CTacticsConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that configures the tactics.
*/
class CTacticsConfiguration : public IJsonable
{
protected:
	using tactic_configurations = CTacticsConfigurationTypes::tactic_configurations;
	using skill_bonus = CTacticConfigurationTypes::skill_bonus;

public:
	//! Retrieves the \copybrief mTacticConfigurations
	const tactic_configurations& GetTacticConfigurations() const noexcept;

	//! Retrieves the \copybrief mFavourableTacticSkillBonus
	const skill_bonus& GetFavourableTacticSkillBonus() const noexcept;

private:
	//! Tactic configurations.
	tactic_configurations mTacticConfigurations;
	//! Favourable tactic skill bonus.
	skill_bonus mFavourableTacticSkillBonus;
};

} // futsim namespace