#include "football/CTacticConfiguration.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

CTacticConfiguration::CTacticConfiguration(
	const skill_bonus& aTkBonus,
	const skill_bonus& aPsBonus,
	const ids& aFavourableTactics,
	const skill_bonuses& aPositionPenalties
) try :
	mTkBonus( aTkBonus ),
	mPsBonus( aPsBonus ),
	mFavourableTactics( aFavourableTactics ),
	mPositionPenalties( aPositionPenalties )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tactic configuration." )

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