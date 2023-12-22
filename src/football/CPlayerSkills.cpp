#include "football/CPlayerSkills.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

#include <iostream>

namespace futsim
{

namespace football
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
	const skill_type& aGKSkill,
	const skill_type& aDFSkill,
	const skill_type& aMFSkill,
	const skill_type& aFWSkill,
	const xp_type& aGKExperience,
	const xp_type& aDFExperience,
	const xp_type& aMFExperience,
	const xp_type& aFWExperience
) try :
	mGKSkill( CheckSkill( aGKSkill, JSON_GK_SKILL ) ),
	mDFSkill( CheckSkill( aDFSkill, JSON_DF_SKILL ) ),
	mMFSkill( CheckSkill( aMFSkill, JSON_MF_SKILL ) ),
	mFWSkill( CheckSkill( aFWSkill, JSON_FW_SKILL ) ),
	mGKExperience( aGKExperience ),
	mDFExperience( aDFExperience ),
	mMFExperience( aMFExperience ),
	mFWExperience( aFWExperience )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player skills." )

CPlayerSkills::CPlayerSkills( const json& aJSON ) try :
	mGKSkill( CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_GK_SKILL ), JSON_GK_SKILL ) ),
	mDFSkill( CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_DF_SKILL ), JSON_DF_SKILL ) ),
	mMFSkill( CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_MF_SKILL ), JSON_MF_SKILL ) ),
	mFWSkill( CheckSkill( ValueFromRequiredJSONKey<skill_type>( aJSON, JSON_FW_SKILL ), JSON_FW_SKILL ) ),
	mGKExperience( ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_GK_XP ) ),
	mDFExperience( ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_DF_XP ) ),
	mMFExperience( ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_MF_XP ) ),
	mFWExperience( ValueFromRequiredJSONKey<xp_type>( aJSON, JSON_FW_XP ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the player skills from JSON." )

CPlayerSkills::json CPlayerSkills::JSON() const noexcept
{
	json result;

	AddToJSONKey( result, mGKSkill, JSON_GK_SKILL );
	AddToJSONKey( result, mDFSkill, JSON_DF_SKILL );
	AddToJSONKey( result, mMFSkill, JSON_MF_SKILL );
	AddToJSONKey( result, mFWSkill, JSON_FW_SKILL );
	AddToJSONKey( result, mGKExperience, JSON_GK_XP );
	AddToJSONKey( result, mDFExperience, JSON_DF_XP );
	AddToJSONKey( result, mMFExperience, JSON_MF_XP );
	AddToJSONKey( result, mFWExperience, JSON_FW_XP );

	return result;
}

const skill_type& CPlayerSkills::GetGKSkill() const noexcept
{
	return mGKSkill;
}

const skill_type& CPlayerSkills::GetDFSkill() const noexcept
{
	return mDFSkill;
}

const skill_type& CPlayerSkills::GetMFSkill() const noexcept
{
	return mMFSkill;
}

const skill_type& CPlayerSkills::GetFWSkill() const noexcept
{
	return mFWSkill;
}

const skill_type& CPlayerSkills::GetGKExperience() const noexcept
{
	return mGKExperience;
}

const skill_type& CPlayerSkills::GetDFExperience() const noexcept
{
	return mDFExperience;
}

const skill_type& CPlayerSkills::GetMFExperience() const noexcept
{
	return mMFExperience;
}

const skill_type& CPlayerSkills::GetFWExperience() const noexcept
{
	return mFWExperience;
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

} // football namespace

} // futsim namespace