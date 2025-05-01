#include "football/CTacticConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NumberUtils.h"

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
	CalculateBonusesTable();
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tactic configuration." )

CTacticConfiguration::CTacticConfiguration( const json& aJSON ) try :
	mTkBonus( ValueFromRequiredJSONKey<skill_bonus>( aJSON, TK_BONUS_KEY ) ),
	mPsBonus( ValueFromRequiredJSONKey<skill_bonus>( aJSON, PS_BONUS_KEY ) ),
	mFavourableTactics( ValueFromOptionalJSONKey<ids>( aJSON, FAVOURABLE_TACTICS_KEY, {} ) ),
	mPositionPenalties( ValueFromOptionalJSONKey<position_penalties>( aJSON, POSITION_PENALTIES_KEY, POSITION_PENALTIES ) )
{
	CalculateBonusesTable();
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tactic configuration from JSON." )

void CTacticConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mTkBonus, TK_BONUS_KEY );
	AddToJSONKey( aJSON, mPsBonus, PS_BONUS_KEY );
	if( !mFavourableTactics.empty() )
		AddToJSONKey( aJSON, mFavourableTactics, FAVOURABLE_TACTICS_KEY );
	AddToJSONKey( aJSON, mPositionPenalties, POSITION_PENALTIES_KEY );
}

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

const CTacticConfiguration::skill_bonus& CTacticConfiguration::GetSkillBonus(
	const E_PLAYER_POSITION& aPlayerPosition, const E_PLAYER_SKILL& aPlayerSkill ) const noexcept
{
	return mBonusesTable[ static_cast<bonuses_table::size_type>( aPlayerPosition ) ]
		[ static_cast<bonuses_table::value_type::size_type>( aPlayerSkill ) ]; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
}

CTacticConfiguration::skill_bonus& CTacticConfiguration::SkillBonus(
	const E_PLAYER_POSITION& aPlayerPosition, const E_PLAYER_SKILL& aPlayerSkill ) noexcept
{
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
	return const_cast<CTacticConfiguration::skill_bonus&>( GetSkillBonus( aPlayerPosition, aPlayerSkill ) );
}

void CTacticConfiguration::CalculateBonusesTable() try
{
	using enum E_PLAYER_POSITION;
	using enum E_PLAYER_SKILL;
	const auto shBonus = -mPsBonus - mTkBonus;
	SkillBonus( GK, St ) = 1;

	SkillBonus( DF, Ps ) = CheckNonNegativeness( 1 + mPsBonus / std::tuple_size_v<position_penalties>+mPositionPenalties[ 1 ], "Ps bonus for DF" );
	SkillBonus( DF, Sh ) = CheckNonNegativeness( 1 + shBonus / std::tuple_size_v<position_penalties>+mPositionPenalties[ 2 ], "Sh bonus for DF" );
	SkillBonus( DF, Tk ) = CheckNonNegativeness( std::tuple_size_v<position_penalties> -GetSkillBonus( DF, Ps ) - GetSkillBonus( DF, Sh ), "Tk bonus for DF" );

	SkillBonus( DM, Tk ) = CheckNonNegativeness( 1 + mTkBonus / std::tuple_size_v<position_penalties>+mPositionPenalties[ 0 ], "Tk bonus for DM" );
	SkillBonus( DM, Sh ) = CheckNonNegativeness( 1 + shBonus / std::tuple_size_v<position_penalties>+( mPositionPenalties[ 1 ] + mPositionPenalties[ 2 ] ) / 2, "Sh bonus for DM" );
	SkillBonus( DM, Ps ) = CheckNonNegativeness( std::tuple_size_v<position_penalties> -GetSkillBonus( DM, Tk ) - GetSkillBonus( DM, Sh ), "Ps bonus for DM" );

	SkillBonus( MF, Tk ) = CheckNonNegativeness( 1 + mTkBonus / std::tuple_size_v<position_penalties>+mPositionPenalties[ 1 ], "Tk bonus for MF" );
	SkillBonus( MF, Sh ) = CheckNonNegativeness( 1 + shBonus / std::tuple_size_v<position_penalties>+mPositionPenalties[ 1 ], "Sh bonus for MF" );
	SkillBonus( MF, Ps ) = CheckNonNegativeness( std::tuple_size_v<position_penalties> -GetSkillBonus( MF, Tk ) - GetSkillBonus( MF, Sh ), "Ps bonus for MF" );

	SkillBonus( AM, Tk ) = CheckNonNegativeness( 1 + mTkBonus / std::tuple_size_v<position_penalties>+( mPositionPenalties[ 1 ] + mPositionPenalties[ 2 ] ) / 2, "Tk bonus for AM" );
	SkillBonus( AM, Sh ) = CheckNonNegativeness( 1 + shBonus / std::tuple_size_v<position_penalties>+mPositionPenalties[ 0 ], "Sh bonus for AM" );
	SkillBonus( AM, Ps ) = CheckNonNegativeness( std::tuple_size_v<position_penalties> -GetSkillBonus( AM, Tk ) - GetSkillBonus( AM, Sh ), "Ps bonus for AM" );

	SkillBonus( FW, Tk ) = CheckNonNegativeness( 1 + mTkBonus / std::tuple_size_v<position_penalties>+mPositionPenalties[ 2 ], "Tk bonus for FW" );
	SkillBonus( FW, Ps ) = CheckNonNegativeness( 1 + mPsBonus / std::tuple_size_v<position_penalties>+mPositionPenalties[ 1 ], "Ps bonus for FW" );
	SkillBonus( FW, Sh ) = CheckNonNegativeness( std::tuple_size_v<position_penalties> -GetSkillBonus( FW, Tk ) - GetSkillBonus( FW, Ps ), "Sh bonus for FW" );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error calculating the bonuses table." )

} // futsim::football namespace
