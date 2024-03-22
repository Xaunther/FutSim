#include "ITest.h"

#include "football/CTacticConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTacticConfiguration )

void TTacticConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CTacticConfiguration{ 10, 10 }; }, "The Sh bonus for DF cannot be negative." );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CTacticConfiguration>( R"( {
			"Tactic configuration": {}
		} )" ); }, "key 'Tk bonus' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTacticConfiguration>( R"( {
			"Tactic configuration": {
				"Tk bonus": 0
			}
		} )" ); }, "key 'Ps bonus' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTacticConfiguration>( R"( {
			"Tactic configuration": {
				"Tk bonus": 10,
				"Ps bonus": 10
			}
		} )" ); }, "The Sh bonus for DF cannot be negative." );
}

std::vector<std::string> TTacticConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& tacticConfiguration : {
	CTacticConfiguration{ 0, 0 },
	CTacticConfiguration{ -0.5, -0.2, { "E", "D" }, { 0, -0.1, -0.3 } },
	futsim::ValueFromJSONKeyString<CTacticConfiguration>( R"( {
			"Tactic configuration": {
				"Tk bonus": 0,
				"Ps bonus": 0
			}
		} )" ),
	futsim::ValueFromJSONKeyString<CTacticConfiguration>( R"( {
			"Tactic configuration": {
				"Tk bonus": -0.5,
				"Ps bonus": -0.2,
				"Favourable tactics": [
					"D",
					"E"
				],
				"Position penalties": [
					0.0,
					-0.1,
					-0.3
				]
			}
		} )" ) } )
	{
		result.push_back( std::string{ CTacticConfiguration::JSON_TK_BONUS } + ": " + std::to_string( tacticConfiguration.GetTkBonus() ) );
		result.push_back( std::string{ CTacticConfiguration::JSON_PS_BONUS } + ": " + std::to_string( tacticConfiguration.GetPsBonus() ) );
		result.push_back( std::string{ CTacticConfiguration::JSON_FAVOURABLE_TACTICS } + ": " );
		for( const auto& favourableTactic : tacticConfiguration.GetFavourableTactics() )
			result.push_back( std::string{ favourableTactic } );
		result.push_back( std::string{ CTacticConfiguration::JSON_POSITION_PENALTIES } + ": " );
		for( const auto& positionPenalty : tacticConfiguration.GetPositionPenalties() )
			result.push_back( std::to_string( positionPenalty ) );
		result.push_back( "St bonus for GK: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::GK, E_PLAYER_SKILL::St ) ) );
		result.push_back( "Tk bonus for DF: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::DF, E_PLAYER_SKILL::Tk ) ) );
		result.push_back( "Ps bonus for DF: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::DF, E_PLAYER_SKILL::Ps ) ) );
		result.push_back( "Sh bonus for DF: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::DF, E_PLAYER_SKILL::Sh ) ) );
		result.push_back( "Tk bonus for DM: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::DM, E_PLAYER_SKILL::Tk ) ) );
		result.push_back( "Ps bonus for DM: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::DM, E_PLAYER_SKILL::Ps ) ) );
		result.push_back( "Sh bonus for DM: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::DM, E_PLAYER_SKILL::Sh ) ) );
		result.push_back( "Tk bonus for MF: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::MF, E_PLAYER_SKILL::Tk ) ) );
		result.push_back( "Ps bonus for MF: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::MF, E_PLAYER_SKILL::Ps ) ) );
		result.push_back( "Sh bonus for MF: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::MF, E_PLAYER_SKILL::Sh ) ) );
		result.push_back( "Tk bonus for AM: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::AM, E_PLAYER_SKILL::Tk ) ) );
		result.push_back( "Ps bonus for AM: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::AM, E_PLAYER_SKILL::Ps ) ) );
		result.push_back( "Sh bonus for AM: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::AM, E_PLAYER_SKILL::Sh ) ) );
		result.push_back( "Tk bonus for FW: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::FW, E_PLAYER_SKILL::Tk ) ) );
		result.push_back( "Ps bonus for FW: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::FW, E_PLAYER_SKILL::Ps ) ) );
		result.push_back( "Sh bonus for FW: " + std::to_string( tacticConfiguration.GetSkillBonus( E_PLAYER_POSITION::FW, E_PLAYER_SKILL::Sh ) ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, tacticConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TTacticConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Tk bonus: 0.000000",
		"Ps bonus: 0.000000",
		"Favourable tactics: ",
		"Position penalties: ",
		"0.000000",
		"-0.200000",
		"-0.400000",
		"St bonus for GK: 1.000000",
		"Tk bonus for DF: 1.600000",
		"Ps bonus for DF: 0.800000",
		"Sh bonus for DF: 0.600000",
		"Tk bonus for DM: 1.000000",
		"Ps bonus for DM: 1.300000",
		"Sh bonus for DM: 0.700000",
		"Tk bonus for MF: 0.800000",
		"Ps bonus for MF: 1.400000",
		"Sh bonus for MF: 0.800000",
		"Tk bonus for AM: 0.700000",
		"Ps bonus for AM: 1.300000",
		"Sh bonus for AM: 1.000000",
		"Tk bonus for FW: 0.600000",
		"Ps bonus for FW: 0.800000",
		"Sh bonus for FW: 1.600000",
		"{\n"
		"	\"Tactic configuration\": {\n"
		"		\"Tk bonus\": 0.0,\n"
		"		\"Ps bonus\": 0.0,\n"
		"		\"Position penalties\": [\n"
		"			0.0,\n"
		"			-0.2,\n"
		"			-0.4\n"
		"		]\n"
		"	}\n"
		"}",
		"Tk bonus: -0.500000",
		"Ps bonus: -0.200000",
		"Favourable tactics: ",
		"D",
		"E",
		"Position penalties: ",
		"0.000000",
		"-0.100000",
		"-0.300000",
		"St bonus for GK: 1.000000",
		"Tk bonus for DF: 1.233333",
		"Ps bonus for DF: 0.833333",
		"Sh bonus for DF: 0.933333",
		"Tk bonus for DM: 0.833333",
		"Ps bonus for DM: 1.133333",
		"Sh bonus for DM: 1.033333",
		"Tk bonus for MF: 0.733333",
		"Ps bonus for MF: 1.133333",
		"Sh bonus for MF: 1.133333",
		"Tk bonus for AM: 0.633333",
		"Ps bonus for AM: 1.133333",
		"Sh bonus for AM: 1.233333",
		"Tk bonus for FW: 0.533333",
		"Ps bonus for FW: 0.833333",
		"Sh bonus for FW: 1.633333",
		"{\n"
		"	\"Tactic configuration\": {\n"
		"		\"Tk bonus\": -0.5,\n"
		"		\"Ps bonus\": -0.2,\n"
		"		\"Favourable tactics\": [\n"
		"			\"D\",\n"
		"			\"E\"\n"
		"		],\n"
		"		\"Position penalties\": [\n"
		"			0.0,\n"
		"			-0.1,\n"
		"			-0.3\n"
		"		]\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
