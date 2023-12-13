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