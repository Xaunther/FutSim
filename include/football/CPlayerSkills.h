#pragma once

#include "IJsonable.h"

#include "football/CPlayerSkillsTypes.h"

namespace futsim::football
{

/**
 * @brief Class encapsulating the skill of a football player.
*/
class CPlayerSkills : public IJsonable
{
protected:
	using skill_type = CPlayerSkillsTypes::skill_type;
	using xp_type = CPlayerSkillsTypes::xp_type;

public:
	/**
	 * @brief Member constructor.
	 * @param aStSkill \ref mStSkill
	 * @param aTkSkill \ref mTkSkill
	 * @param aPsSkill \ref mPsSkill
	 * @param aShSkill \ref mShSkill
	 * @param aStExperience \ref mStExperience
	 * @param aTkExperience \ref mTkExperience
	 * @param aPsExperience \ref mPsExperience
	 * @param aShExperience \ref mShExperience
	*/
	explicit CPlayerSkills(
		const skill_type& aStSkill,
		const skill_type& aTkSkill,
		const skill_type& aPsSkill,
		const skill_type& aShSkill,
		const xp_type& aStExperience,
		const xp_type& aTkExperience,
		const xp_type& aPsExperience,
		const xp_type& aShExperience );

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
	//! Retrieves the \copybrief mStSkill
	const skill_type& GetStSkill() const noexcept;

	//! Retrieves the \copybrief mTkSkill
	const skill_type& GetTkSkill() const noexcept;

	//! Retrieves the \copybrief mPsSkill
	const skill_type& GetPsSkill() const noexcept;

	//! Retrieves the \copybrief mShSkill
	const skill_type& GetShSkill() const noexcept;

	//!Retrieves the \copybrief mStExperience
	const skill_type& GetStExperience() const noexcept;

	//!Retrieves the \copybrief mTkExperience
	const skill_type& GetTkExperience() const noexcept;

	//!Retrieves the \copybrief mPsExperience
	const skill_type& GetPsExperience() const noexcept;

	//!Retrieves the \copybrief mShExperience
	const skill_type& GetShExperience() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Player skills";
	//! JSON key for the \copybrief mStSkill
	static inline constexpr std::string_view JSON_ST_SKILL = "St skill";
	//! JSON key for the \copybrief mTkSkill
	static inline constexpr std::string_view JSON_TK_SKILL = "Tk skill";
	//! JSON key for the \copybrief mPsSkill
	static inline constexpr std::string_view JSON_PS_SKILL = "Ps skill";
	//! JSON key for the \copybrief mShSkill
	static inline constexpr std::string_view JSON_SH_SKILL = "Sh skill";
	//! JSON key for the \copybrief mStExperience
	static inline constexpr std::string_view JSON_ST_XP = "St experience";
	//! JSON key for the \copybrief mTkExperience
	static inline constexpr std::string_view JSON_TK_XP = "Tk experience";
	//! JSON key for the \copybrief mPsExperience
	static inline constexpr std::string_view JSON_PS_XP = "Ps experience";
	//! JSON key for the \copybrief mShExperience
	static inline constexpr std::string_view JSON_SH_XP = "Sh experience";

private:
	//! Goalkeeping skill value.
	skill_type mStSkill;
	//! Defensive skill value.
	skill_type mTkSkill;
	//! Midfielding skill value.
	skill_type mPsSkill;
	//! Attacking skill value.
	skill_type mShSkill;
	//! Goalkeeping skill experience.
	xp_type mStExperience;
	//! Defensive skill experience.
	xp_type mTkExperience;
	//! Midfielding skill experience.
	xp_type mPsExperience;
	//! Attacking skill experience.
	xp_type mShExperience;
};

} // futsim::football namespace