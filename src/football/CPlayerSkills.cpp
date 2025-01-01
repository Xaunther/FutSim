#include "football/CPlayerSkills.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

#include <iostream>

namespace futsim::football
{

using namespace types::CPlayerSkills;

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
	CheckSkill( GetSkill( E_PLAYER_SKILL::St ), SKILL_KEY<E_PLAYER_SKILL::St> );
	CheckSkill( GetSkill( E_PLAYER_SKILL::Tk ), SKILL_KEY<E_PLAYER_SKILL::Tk> );
	CheckSkill( GetSkill( E_PLAYER_SKILL::Ps ), SKILL_KEY<E_PLAYER_SKILL::Ps> );
	CheckSkill( GetSkill( E_PLAYER_SKILL::Sh ), SKILL_KEY<E_PLAYER_SKILL::Sh> );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player skills." )

CPlayerSkills::CPlayerSkills( const json& aJSON ) try :
	mSkills( { CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, SKILL_KEY<E_PLAYER_SKILL::St> ), SKILL_KEY<E_PLAYER_SKILL::St> ),
		CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, SKILL_KEY<E_PLAYER_SKILL::Tk> ), SKILL_KEY<E_PLAYER_SKILL::Tk> ),
		CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, SKILL_KEY<E_PLAYER_SKILL::Ps> ), SKILL_KEY<E_PLAYER_SKILL::Ps> ),
		CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, SKILL_KEY<E_PLAYER_SKILL::Sh> ), SKILL_KEY<E_PLAYER_SKILL::Sh> )
		} ),
	mExperiences( { ValueFromRequiredJSONKey<xp_type>( aJSON, XP_KEY<E_PLAYER_SKILL::St> ),
		ValueFromRequiredJSONKey<xp_type>( aJSON, XP_KEY<E_PLAYER_SKILL::Tk> ),
		ValueFromRequiredJSONKey<xp_type>( aJSON, XP_KEY<E_PLAYER_SKILL::Ps> ),
		ValueFromRequiredJSONKey<xp_type>( aJSON, XP_KEY<E_PLAYER_SKILL::Sh> )
		} )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player skills from JSON." )

void CPlayerSkills::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, GetSkill( E_PLAYER_SKILL::St ), SKILL_KEY<E_PLAYER_SKILL::St> );
	AddToJSONKey( aJSON, GetSkill( E_PLAYER_SKILL::Tk ), SKILL_KEY<E_PLAYER_SKILL::Tk> );
	AddToJSONKey( aJSON, GetSkill( E_PLAYER_SKILL::Ps ), SKILL_KEY<E_PLAYER_SKILL::Ps> );
	AddToJSONKey( aJSON, GetSkill( E_PLAYER_SKILL::Sh ), SKILL_KEY<E_PLAYER_SKILL::Sh> );
	AddToJSONKey( aJSON, GetExperience( E_PLAYER_SKILL::St ), XP_KEY<E_PLAYER_SKILL::St> );
	AddToJSONKey( aJSON, GetExperience( E_PLAYER_SKILL::Tk ), XP_KEY<E_PLAYER_SKILL::Tk> );
	AddToJSONKey( aJSON, GetExperience( E_PLAYER_SKILL::Ps ), XP_KEY<E_PLAYER_SKILL::Ps> );
	AddToJSONKey( aJSON, GetExperience( E_PLAYER_SKILL::Sh ), XP_KEY<E_PLAYER_SKILL::Sh> );
}

const skill_type& CPlayerSkills::GetSkill( const E_PLAYER_SKILL& aPlayerSkill ) const noexcept
{
	return mSkills[ static_cast<std::size_t>( aPlayerSkill ) ];
}

const xp_type& CPlayerSkills::GetExperience( const E_PLAYER_SKILL& aPlayerSkill ) const noexcept
{
	return mExperiences[ static_cast<std::size_t>( aPlayerSkill ) ];
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
