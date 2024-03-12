#include "football/CTacticConfiguration.h"

namespace futsim::football
{

const CTacticConfiguration::skill_bonus& CTacticConfiguration::GetTkBonus() const noexcept
{
	return mTkBonus;
}

const CTacticConfiguration::skill_bonus& CTacticConfiguration::GetPsBonus() const noexcept
{
	return mPsBonus;
}

const CTacticConfiguration::ids& CTacticConfiguration::GetFavourableTactics() const noexcept
{
	return mFavourableTactics;
}

const CTacticConfiguration::skill_bonuses& CTacticConfiguration::GetPositionPenalties() const noexcept
{
	return mPositionPenalties;
}

} // futsim::football namespace