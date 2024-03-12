#include "football/CTacticConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

CTacticConfiguration::CTacticConfiguration(
	const skill_bonus& aTkBonus,
	const skill_bonus& aPsBonus,
	const ids& aFavourableTactics,
	const position_penalties& aPositionPenalties
) try :
	mTkBonus( aTkBonus ),
	mPsBonus( aPsBonus ),
	mFavourableTactics( aFavourableTactics ),
	mPositionPenalties( aPositionPenalties )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tactic configuration." )

CTacticConfiguration::CTacticConfiguration( const json& aJSON ) try :
	mTkBonus( ValueFromRequiredJSONKey<skill_bonus>( aJSON, JSON_TK_BONUS ) ),
	mPsBonus( ValueFromRequiredJSONKey<skill_bonus>( aJSON, JSON_PS_BONUS ) ),
	mFavourableTactics( ValueFromOptionalJSONKey<ids>( aJSON, JSON_FAVOURABLE_TACTICS, {} ) ),
	mPositionPenalties( ValueFromOptionalJSONKey<position_penalties>( aJSON, JSON_POSITION_PENALTIES, DEFAULT_POSITION_PENALTIES ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tactic configuration from JSON." )

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

const CTacticConfiguration::position_penalties& CTacticConfiguration::GetPositionPenalties() const noexcept
{
	return mPositionPenalties;
}

} // futsim::football namespace