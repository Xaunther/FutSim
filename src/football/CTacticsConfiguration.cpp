#include "football/CTacticsConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NumberUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Checks that the tactic configurations are compatible.
 * @param aTacticConfigurations Tactic configurations.
*/
const types::CTacticsConfiguration::tactic_configurations& CheckTacticConfigurations(
	const types::CTacticsConfiguration::tactic_configurations& aTacticConfigurations );

/**
 * @brief Creates the tactic configurations from JSON.
 * @param aJSON JSON object.
*/
types::CTacticsConfiguration::tactic_configurations CreateTacticConfigurationsFromJSON( const futsim::types::IJsonable::json& aJSON );

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

CTacticsConfiguration::CTacticsConfiguration( const json& aJSON ) try :
	mTacticConfigurations( CheckTacticConfigurations( aJSON.find( JSON_TACTIC_CONFIGURATIONS ) != aJSON.cend() ?
		CreateTacticConfigurationsFromJSON( aJSON.at( JSON_TACTIC_CONFIGURATIONS ) ) : DEFAULT_TACTIC_CONFIGURATIONS ) ),
	mFavourableTacticSkillBonus( CheckNonNegativeness( ValueFromOptionalJSONKey<skill_bonus>(
		aJSON, JSON_FAVOURABLE_TACTIC_SKILL_BONUS, DEFAULT_FAVOURABLE_TACTIC_SKILL_BONUS ), "favourable tactic skill bonus" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tactics configuration from JSON." )

void CTacticsConfiguration::JSON( json& aJSON ) const noexcept
{
	for( auto& JSONTacticConfigurations = aJSON[ JSON_TACTIC_CONFIGURATIONS ];
		const auto & tacticConfiguration : mTacticConfigurations )
		AddToJSONKey( JSONTacticConfigurations, tacticConfiguration.second, tacticConfiguration.first );
	AddToJSONKey( aJSON, mFavourableTacticSkillBonus, JSON_FAVOURABLE_TACTIC_SKILL_BONUS );
}

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

const types::CTacticsConfiguration::tactic_configurations& CheckTacticConfigurations(
	const types::CTacticsConfiguration::tactic_configurations& aTacticConfigurations ) try
{
	if( aTacticConfigurations.empty() )
		throw std::invalid_argument{ "The tactic configurations cannot be empty" };

	for( const auto& tacticConfiguration : aTacticConfigurations )
		for( const auto& favourableTacticID : tacticConfiguration.second.GetFavourableTactics() )
			if( aTacticConfigurations.at( favourableTacticID ).GetFavourableTactics().contains( tacticConfiguration.first ) )
				throw std::invalid_argument{ "The tactics '" + tacticConfiguration.first + "' and '" + favourableTacticID + "' "
						"are favourable against each other, which is forbidden." };

	return aTacticConfigurations;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the tactic configurations." )

types::CTacticsConfiguration::tactic_configurations CreateTacticConfigurationsFromJSON( const futsim::types::IJsonable::json& aJSON ) try
{
	types::CTacticsConfiguration::tactic_configurations result;
	for( const auto& JSONTacticConfiguration : aJSON.items() )
		result.emplace( JSONTacticConfiguration.key(), ValueFromJSON<CTacticConfiguration>( JSONTacticConfiguration.value() ) );

	return result;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the tactic configurations from JSON." )

} // anonymous namespace

} // futsim::football namespace