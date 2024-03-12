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
	const skill_type& aStSkill,
	const skill_type& aTkSkill,
	const skill_type& aPsSkill,
	const skill_type& aShSkill,
	const xp_type& aStExperience,
	const xp_type& aTkExperience,
	const xp_type& aPsExperience,
	const xp_type& aShExperience
) try :
	mStSkill( CheckSkill( aStSkill, JSON_ST_SKILL ) ),
	mTkSkill( CheckSkill( aTkSkill, JSON_TK_SKILL ) ),
	mPsSkill( CheckSkill( aPsSkill, JSON_PS_SKILL ) ),
	mShSkill( CheckSkill( aShSkill, JSON_SH_SKILL ) ),
	mStExperience( aStExperience ),
	mTkExperience( aTkExperience ),
	mPsExperience( aPsExperience ),
	mShExperience( aShExperience )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player skills." )

CPlayerSkills::CPlayerSkills( const json& aJSON ) try :
	mStSkill( CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_ST_SKILL ), JSON_ST_SKILL ) ),
	mTkSkill( CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_TK_SKILL ), JSON_TK_SKILL ) ),
	mPsSkill( CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_PS_SKILL ), JSON_PS_SKILL ) ),
	mShSkill( CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_SH_SKILL ), JSON_SH_SKILL ) ),
	mStExperience( ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_ST_XP ) ),
	mTkExperience( ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_TK_XP ) ),
	mPsExperience( ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_PS_XP ) ),
	mShExperience( ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_SH_XP ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player skills from JSON." )

void CPlayerSkills::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mStSkill, JSON_ST_SKILL );
	AddToJSONKey( aJSON, mTkSkill, JSON_TK_SKILL );
	AddToJSONKey( aJSON, mPsSkill, JSON_PS_SKILL );
	AddToJSONKey( aJSON, mShSkill, JSON_SH_SKILL );
	AddToJSONKey( aJSON, mStExperience, JSON_ST_XP );
	AddToJSONKey( aJSON, mTkExperience, JSON_TK_XP );
	AddToJSONKey( aJSON, mPsExperience, JSON_PS_XP );
	AddToJSONKey( aJSON, mShExperience, JSON_SH_XP );
}

const skill_type& CPlayerSkills::GetStSkill() const noexcept
{
	return mStSkill;
}

const skill_type& CPlayerSkills::GetTkSkill() const noexcept
{
	return mTkSkill;
}

const skill_type& CPlayerSkills::GetPsSkill() const noexcept
{
	return mPsSkill;
}

const skill_type& CPlayerSkills::GetShSkill() const noexcept
{
	return mShSkill;
}

const skill_type& CPlayerSkills::GetStExperience() const noexcept
{
	return mStExperience;
}

const skill_type& CPlayerSkills::GetTkExperience() const noexcept
{
	return mTkExperience;
}

const skill_type& CPlayerSkills::GetPsExperience() const noexcept
{
	return mPsExperience;
}

const skill_type& CPlayerSkills::GetShExperience() const noexcept
{
	return mShExperience;
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