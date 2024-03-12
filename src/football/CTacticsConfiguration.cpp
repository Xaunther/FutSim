#include "football/CTacticsConfiguration.h"

namespace futsim::football
{

const CTacticsConfiguration::tactic_configurations& CTacticsConfiguration::GetTacticConfigurations() const noexcept
{
	return mTacticConfigurations;
}

const CTacticsConfiguration::skill_bonus& CTacticsConfiguration::GetFavourableTacticSkillBonus() const noexcept
{
	return mFavourableTacticSkillBonus;
}

} // futsim::football namespace