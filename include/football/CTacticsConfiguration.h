#pragma once

#include "IJsonable.h"

#include "football/CTacticConfiguration.h"
#include "football/types/CTacticsConfiguration.h"

namespace futsim::football
{

/**
 * @brief Class that configures the tactics.
*/
class CTacticsConfiguration : public IJsonable
{
protected:
	using tactic_configurations = types::CTacticsConfiguration::tactic_configurations;
	using skill_bonus = types::CTacticConfiguration::skill_bonus;

public:
	/**
	 * @brief Member constructor.
	 * @param aTacticConfigurations \ref mTacticConfigurations
	 * @param aFavourableTacticSkillBonus \ref mFavourableTacticSkillBonus
	*/
	explicit CTacticsConfiguration(
		const tactic_configurations& aTacticConfigurations = DEFAULT_TACTIC_CONFIGURATIONS,
		const skill_bonus& aFavourableTacticSkillBonus = DEFAULT_FAVOURABLE_TACTIC_SKILL_BONUS
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CTacticsConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mTacticConfigurations
	const tactic_configurations& GetTacticConfigurations() const noexcept;

	//! Retrieves the \copybrief mFavourableTacticSkillBonus
	const skill_bonus& GetFavourableTacticSkillBonus() const noexcept;

	//! Default \copybrief mTacticConfigurations
	static inline tactic_configurations DEFAULT_TACTIC_CONFIGURATIONS = {
		{ "N", CTacticConfiguration{ 0, 0, {"A", "E"} } },
		{ "A", CTacticConfiguration{ -0.5, -0.2, {"D", "E"} } },
		{ "D", CTacticConfiguration{ 0.7, -0.2, {"L", "P"} } },
		{ "L", CTacticConfiguration{ 0.3, -0.6, {"C", "N"} } },
		{ "C", CTacticConfiguration{ 0.5, -0.8, {"A", "P"} } },
		{ "P", CTacticConfiguration{ -0.2, 0.6, {"L", "N"} } },
		{ "E", CTacticConfiguration{ -0.3, 0.2, {"D", "C"} } }
	};

	//! Default \copybrief mFavourableTacticSkillBonus
	static inline constexpr skill_bonus DEFAULT_FAVOURABLE_TACTIC_SKILL_BONUS = 1.1;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Tactics configuration";
	//! JSON key for the \copybrief mTacticConfigurations
	static inline constexpr std::string_view JSON_TACTIC_CONFIGURATIONS = "Tactic configurations";
	//! JSON key for the \copybrief mFavourableTacticSkillBonus
	static inline constexpr std::string_view JSON_FAVOURABLE_TACTIC_SKILL_BONUS = "Favourable tactic skill bonus";

private:
	//! Tactic configurations.
	tactic_configurations mTacticConfigurations;
	//! Favourable tactic skill bonus.
	skill_bonus mFavourableTacticSkillBonus;
};

} // futsim namespace