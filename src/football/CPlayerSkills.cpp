#include "football/CPlayerSkills.h"

#include <exception>
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
*/
const skill_type& CheckSkill( const skill_type& aSkill );

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
	mGKSkill( CheckSkill( aGKSkill ) ),
	mDFSkill( CheckSkill( aDFSkill ) ),
	mMFSkill( CheckSkill( aMFSkill ) ),
	mFWSkill( CheckSkill( aFWSkill ) ),
	mGKExperience( aGKExperience ),
	mDFExperience( aDFExperience ),
	mMFExperience( aMFExperience ),
	mFWExperience( aFWExperience )
{
}
catch( const std::exception& aException )
{
	std::stringstream ss;
	ss << aException.what() << "\n" << "Error creating the player skills.";
	throw std::invalid_argument( ss.str() );
}

CPlayerSkills::CPlayerSkills( const json& aJSON ) try :
	CPlayerSkills(
		aJSON.at( JSON_GK_SKILL ),
		aJSON.at( JSON_DF_SKILL ),
		aJSON.at( JSON_MF_SKILL ),
		aJSON.at( JSON_FW_SKILL ),
		aJSON.at( JSON_GK_XP ),
		aJSON.at( JSON_DF_XP ),
		aJSON.at( JSON_MF_XP ),
		aJSON.at( JSON_FW_XP )
	)
{
}
catch( const std::exception& aException )
{
	std::stringstream ss;
	ss << aException.what() << "\n" << "Error creating the player skills from JSON.";
	throw std::invalid_argument( ss.str() );
}

CPlayerSkills::json CPlayerSkills::JSON() const noexcept
{
	json result;

	result[ JSON_GK_SKILL ] = mGKSkill;
	result[ JSON_DF_SKILL ] = mDFSkill;
	result[ JSON_MF_SKILL ] = mMFSkill;
	result[ JSON_FW_SKILL ] = mFWSkill;
	result[ JSON_GK_XP ] = mGKExperience;
	result[ JSON_DF_XP ] = mDFExperience;
	result[ JSON_MF_XP ] = mMFExperience;
	result[ JSON_FW_XP ] = mFWExperience;

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

const skill_type& CheckSkill( const skill_type& aSkill ) try
{
	if( aSkill == 0 )
		throw std::domain_error( "The skill value must be greater than 0." );
	return aSkill;
}
catch( const std::exception& aException )
{
	std::stringstream ss;
	ss << aException.what() << "\n" << "Invalid skill value.";
	throw std::invalid_argument( ss.str() );
}

} // anonymous namespace

} // football namespace

} // futsim namespace