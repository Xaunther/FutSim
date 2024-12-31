#pragma once

#include "IJsonable.h"
#include "traits/default.h"
#include "traits/json.h"

#include "football/CTacticConfiguration.h"
#include "football/types/CTacticsConfiguration.h"

namespace futsim
{

namespace football
{
class CTacticsConfiguration;
}

template <> struct default_traits<football::CTacticsConfiguration>
{
private:
	using tactic_configurations = football::types::CTacticsConfiguration::tactic_configurations;
	using skill_bonus = football::types::CTacticConfiguration::skill_bonus;
public:
	//! Default \copybrief football::CTacticsConfiguration::mTacticConfigurations
	static inline tactic_configurations TACTIC_CONFIGURATIONS = {
		{ "N", football::CTacticConfiguration{ 0, 0, { "A", "E" } } },
		{ "A", football::CTacticConfiguration{ -0.5, -0.2, { "D", "E" } } },
		{ "D", football::CTacticConfiguration{ 0.7, -0.2, { "L", "P" } } },
		{ "L", football::CTacticConfiguration{ 0.3, -0.6, { "C", "N" } } },
		{ "C", football::CTacticConfiguration{ 0.5, -0.8, { "A", "P" } } },
		{ "P", football::CTacticConfiguration{ -0.2, 0.6, { "L", "N" } } },
		{ "E", football::CTacticConfiguration{ -0.3, 0.2, { "D", "C" } } }
	};

	//! Default \copybrief football::CTacticsConfiguration::mFavourableTacticSkillBonus
	static inline constexpr skill_bonus FAVOURABLE_TACTIC_SKILL_BONUS = 1.1;
};

template <> struct json_traits<football::CTacticsConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Tactics configuration";
	//! JSON key for the \copybrief football::CTacticsConfiguration::mTacticConfigurations
	static inline constexpr std::string_view TACTIC_CONFIGURATIONS_KEY = "Tactic configurations";
	//! JSON key for the \copybrief football::CTacticsConfiguration::mFavourableTacticSkillBonus
	static inline constexpr std::string_view FAVOURABLE_TACTIC_SKILL_BONUS_KEY = "Favourable tactic skill bonus";
};

namespace football
{

/**
 * @brief Class that configures the tactics.
*/
class CTacticsConfiguration : public IJsonable, protected default_traits<CTacticsConfiguration>, protected json_traits<CTacticsConfiguration>
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
		const tactic_configurations& aTacticConfigurations = TACTIC_CONFIGURATIONS,
		const skill_bonus& aFavourableTacticSkillBonus = FAVOURABLE_TACTIC_SKILL_BONUS
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

private:
	//! Tactic configurations.
	tactic_configurations mTacticConfigurations;
	//! Favourable tactic skill bonus.
	skill_bonus mFavourableTacticSkillBonus;
};

} // football namespace

} // futsim namespace
