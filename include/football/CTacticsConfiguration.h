#pragma once

#include "IJsonable.h"
#include "football/traits/CTacticsConfiguration.h"

#include "football/CTacticConfiguration.h"
#include "football/types/CTacticsConfiguration.h"

namespace futsim::football
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

} // futsim::football namespace
