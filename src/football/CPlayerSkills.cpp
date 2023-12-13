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