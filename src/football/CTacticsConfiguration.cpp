#include "football/CTacticsConfiguration.h"

#include "ExceptionUtils.h"
#include "NumberUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Checks that the tactic configurations are compatible.
 * @param aTacticConfigurations Tactic configurations.
*/
const CTacticsConfigurationTypes::tactic_configurations& CheckTacticConfigurations(
	const CTacticsConfigurationTypes::tactic_configurations& aTacticConfigurations );

} // anonymous namespace

CTacticsConfiguration::CTacticsConfiguration(
	const tactic_configurations& aTacticConfigurations,
	const skill_bonus& aFavourableTacticSkillBonus
) try :
	mTacticConfigurations( CheckTacticConfigurations( aTacticConfigurations ) ),
	mFavourableTacticSkillBonus( CheckNonNegativeness( aFavourableTacticSkillBonus, "favourable tactic skill bonus" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tactics configuration." )

const CTacticsConfiguration::tactic_configurations& CTacticsConfiguration::GetTacticConfigurations() const noexcept
{
	return mTacticConfigurations;
}

const CTacticsConfiguration::skill_bonus& CTacticsConfiguration::GetFavourableTacticSkillBonus() const noexcept
{
	return mFavourableTacticSkillBonus;
}

namespace
{

const CTacticsConfigurationTypes::tactic_configurations& CheckTacticConfigurations(
	const CTacticsConfigurationTypes::tactic_configurations& aTacticConfigurations ) try
{
	if( aTacticConfigurations.empty() )
		throw std::invalid_argument{ "The tactic configurations cannot be empty" };

	for( const auto& tacticConfiguration : aTacticConfigurations )
		for( const auto& favourableTacticID : tacticConfiguration.second.GetFavourableTactics() )
			if( const auto& favourableTactic = aTacticConfigurations.at( favourableTacticID );
				favourableTactic.GetFavourableTactics().contains( tacticConfiguration.first ) )
				throw std::invalid_argument{ "The tactics '" + tacticConfiguration.first + "' and '" + favourableTacticID + "' "
						"are favourable against each other, which is forbidden." };

	return aTacticConfigurations;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the tactic configurations." )

} // anonymous namespace

} // futsim::football namespace