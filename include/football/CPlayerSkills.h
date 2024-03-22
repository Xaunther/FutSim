#pragma once

#include "IJsonable.h"

#include "football/types/CPlayerSkills.h"

namespace futsim::football
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

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Player skills";
	//! JSON key for the St skill.
	static inline constexpr std::string_view JSON_ST_SKILL = "St skill";
	//! JSON key for the Tk skill.
	static inline constexpr std::string_view JSON_TK_SKILL = "Tk skill";
	//! JSON key for the Ps skill.
	static inline constexpr std::string_view JSON_PS_SKILL = "Ps skill";
	//! JSON key for the Sh skill.
	static inline constexpr std::string_view JSON_SH_SKILL = "Sh skill";
	//! JSON key for the St experience.
	static inline constexpr std::string_view JSON_ST_XP = "St experience";
	//! JSON key for the Tk experience.
	static inline constexpr std::string_view JSON_TK_XP = "Tk experience";
	//! JSON key for the Ps experience.
	static inline constexpr std::string_view JSON_PS_XP = "Ps experience";
	//! JSON key for the Sh experience.
	static inline constexpr std::string_view JSON_SH_XP = "Sh experience";

private:
	//! Skill values.
	skills mSkills;
	//! Skill experiences.
	experiences mExperiences;
};

} // futsim::football namespace