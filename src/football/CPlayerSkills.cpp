#include "football/CPlayerSkills.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

#include <iostream>

namespace futsim::football
{

using namespace CPlayerSkillsTypes;

namespace
{

/**
 * @brief Checks correctness of the ability
 * @param aSkill Skill value.
 * @param aNameString String with the name label to add to the error message.
*/
const skill_type& CheckSkill( const skill_type& aSkill, const std::string_view aNameString );

} // anonymous namespace

CPlayerSkills::CPlayerSkills(
	const skills& aSkills,
	const experiences& aExperiences
) try :
	mSkills( aSkills ),
	mExperiences( aExperiences )
{
	CheckSkill( GetSkill( E_PLAYER_SKILL::St ), JSON_ST_SKILL );
	CheckSkill( GetSkill( E_PLAYER_SKILL::Tk ), JSON_TK_SKILL );
	CheckSkill( GetSkill( E_PLAYER_SKILL::Ps ), JSON_PS_SKILL );
	CheckSkill( GetSkill( E_PLAYER_SKILL::Sh ), JSON_SH_SKILL );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player skills." )

CPlayerSkills::CPlayerSkills( const json& aJSON ) try :
	mSkills( { CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_ST_SKILL ), JSON_ST_SKILL ),
		CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_TK_SKILL ), JSON_TK_SKILL ),
		CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_PS_SKILL ), JSON_PS_SKILL ),
		CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_SH_SKILL ), JSON_SH_SKILL )
		} ),
	mExperiences( { ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_ST_XP ),
		ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_TK_XP ),
		ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_PS_XP ),
		ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_SH_XP )
		} )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player skills from JSON." )

void CPlayerSkills::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, GetSkill( E_PLAYER_SKILL::St ), JSON_ST_SKILL );
	AddToJSONKey( aJSON, GetSkill( E_PLAYER_SKILL::Tk ), JSON_TK_SKILL );
	AddToJSONKey( aJSON, GetSkill( E_PLAYER_SKILL::Ps ), JSON_PS_SKILL );
	AddToJSONKey( aJSON, GetSkill( E_PLAYER_SKILL::Sh ), JSON_SH_SKILL );
	AddToJSONKey( aJSON, GetExperience( E_PLAYER_SKILL::St ), JSON_ST_XP );
	AddToJSONKey( aJSON, GetExperience( E_PLAYER_SKILL::Tk ), JSON_TK_XP );
	AddToJSONKey( aJSON, GetExperience( E_PLAYER_SKILL::Ps ), JSON_PS_XP );
	AddToJSONKey( aJSON, GetExperience( E_PLAYER_SKILL::Sh ), JSON_SH_XP );
}

const skill_type& CPlayerSkills::GetSkill( const E_PLAYER_SKILL& aPlayerSkill ) const noexcept
{
	return mSkills[ static_cast< std::size_t >( aPlayerSkill ) ];
}

const xp_type& CPlayerSkills::GetExperience( const E_PLAYER_SKILL& aPlayerSkill ) const noexcept
{
	return mExperiences[ static_cast< std::size_t >( aPlayerSkill ) ];
}

namespace
{

const skill_type& CheckSkill( const skill_type& aSkill, const std::string_view aNameString ) try
{
	if( aSkill == 0 )
		throw std::domain_error( "The " + std::string{ aNameString } + " value must be greater than 0." );
	return aSkill;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Invalid skill value." )

} // anonymous namespace

} // futsim::football namespace