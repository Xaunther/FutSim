#pragma once

#include "IJsonable.h"

#include "football/types/CPlayerSkills.h"

namespace futsim
{

namespace football
{

/**
 * @brief Class encapsulating the skill of a football player.
*/
class CPlayerSkills : public IJsonable
{
protected:
	using skill_type = types::CPlayerSkills::skill_type;
	using xp_type = types::CPlayerSkills::xp_type;
	using skills = types::CPlayerSkills::skills;
	using experiences = types::CPlayerSkills::experiences;

public:
	/**
	 * @brief Member constructor.
	 * @param aSkills \ref mSkills
	 * @param aExperiences \ref mExperiences
	*/
	explicit CPlayerSkills(
		const skills& aSkills,
		const experiences& aExperiences
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPlayerSkills( const json& aJSON );

private:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	/**
	 * @brief Retrieves the requested skill.
	 * @param aPlayerSkill Player skill to retrieve.
	*/
	const skill_type& GetSkill( const E_PLAYER_SKILL& aPlayerSkill ) const noexcept;

	/**
	 * @brief Retrieves the requested skill experience.
	 * @param aPlayerSkill Player skill to retrieve.
	*/
	const xp_type& GetExperience( const E_PLAYER_SKILL& aPlayerSkill ) const noexcept;

private:
	//! Skill values.
	skills mSkills;
	//! Skill experiences.
	experiences mExperiences;
};

} // football namespace

template <> struct json_traits<football::CPlayerSkills>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Player skills";
	//! JSON key for a skill.
	template <football::E_PLAYER_SKILL tPlayerSkill> static inline constexpr std::string_view SKILL{};
	//! JSON key for a skill experience.
	template <football::E_PLAYER_SKILL tPlayerSkill> static inline constexpr std::string_view XP{};
};

FOR_EACH_PLAYER_SKILL( FUTSIM_INSTANTIATE_ENUM_TRAIT, football::CPlayerSkills, SKILL, football::E_PLAYER_SKILL, " skill" )
FOR_EACH_PLAYER_SKILL( FUTSIM_INSTANTIATE_ENUM_TRAIT, football::CPlayerSkills, XP, football::E_PLAYER_SKILL, " experience" )

} // futsim namespace