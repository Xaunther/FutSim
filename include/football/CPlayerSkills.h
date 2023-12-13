#pragma once

#include "IJsonable.h"

#include "football/CPlayerSkillsTypes.h"

namespace futsim
{

namespace football
{

/**
 * @brief Class encapsulating the skill of a football player.
*/
class CPlayerSkills : public IJsonable
{
	using skill_type = CPlayerSkillsTypes::skill_type;
	using xp_type = CPlayerSkillsTypes::xp_type;

public:
	/**
	 * @brief Member constructor.
	 * @param aGKSkill \ref mGKSkill
	 * @param aDFSkill \ref mDFSkill
	 * @param aMFSkill \ref mMFSkill
	 * @param aFWSkill \ref mFWSkill
	 * @param aGKExperience \ref mGKExperience
	 * @param aDFExperience \ref mDFExperience
	 * @param aMFExperience \ref mMFExperience
	 * @param aFWExperience \ref mFWExperience
	*/
	explicit CPlayerSkills(
		const skill_type& aGKSkill,
		const skill_type& aDFSkill,
		const skill_type& aMFSkill,
		const skill_type& aFWSkill,
		const xp_type& aGKExperience,
		const xp_type& aDFExperience,
		const xp_type& aMFExperience,
		const xp_type& aFWExperience );

private:
	//! Goalkeeping skill value.
	skill_type mGKSkill;
	//! Defensive skill value.
	skill_type mDFSkill;
	//! Midfielding skill value.
	skill_type mMFSkill;
	//! Attacking skill value.
	skill_type mFWSkill;
	//! Goalkeeping skill experience.
	xp_type mGKExperience;
	//! Defensive skill experience.
	xp_type mDFExperience;
	//! Midfielding skill experience.
	xp_type mMFExperience;
	//! Attacking skill experience.
	xp_type mFWExperience;
};

} // football namespace

} // futsim namespace