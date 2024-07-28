#include "ITest.h"

#include "football/CTacticsConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTacticsConfiguration )

void TTacticsConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []()
	{
		CTacticsConfiguration{ types::CTacticsConfiguration::tactic_configurations{} };
	},
		"The tactic configurations cannot be empty" );
	CheckException( []()
	{
		CTacticsConfiguration{ { { "A", CTacticConfiguration{ 0, 0, { "A" } } } } };
	},
		"The tactics 'A' and 'A' are favourable against each other, which is forbidden." );
	CheckException( []()
	{
		CTacticsConfiguration{ { { "A", CTacticConfiguration{ 0, 0, { "E" } } },
		{ "E", CTacticConfiguration{ 0, 0, { "A" } } } } };
	},
		"The tactics 'A' and 'E' are favourable against each other, which is forbidden." );
	CheckException( []()
	{
		CTacticsConfiguration{ futsim::default_traits<CTacticsConfiguration>::TACTIC_CONFIGURATIONS, -0.5 };
	},
		"The favourable tactic skill bonus cannot be negative" );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTacticsConfiguration>( R"( {
			"Tactics configuration": {
				"Tactic configurations": {}
			}
		} )" );
	}, "The tactic configurations cannot be empty" );

	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTacticsConfiguration>( R"( {
			"Tactics configuration": {
				"Tactic configurations": {
					"A": {
						"Tk bonus": 0,
						"Ps bonus": 0,
						"Favourable tactics": ["A"]
					}
				}
			}
		} )" );
	}, "The tactics 'A' and 'A' are favourable against each other, which is forbidden." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTacticsConfiguration>( R"( {
			"Tactics configuration": {
				"Tactic configurations": {
					"A": {
						"Tk bonus": 0,
						"Ps bonus": 0,
						"Favourable tactics": ["E"]
					},
					"E": {
						"Tk bonus": 0,
						"Ps bonus": 0,
						"Favourable tactics": ["A"]
					}
				}
			}
		} )" );
	}, "The tactics 'A' and 'E' are favourable against each other, which is forbidden." );

	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTacticsConfiguration>( R"( {
			"Tactics configuration": {
				"Favourable tactic skill bonus": -1
			}
		} )" );
	}, "The favourable tactic skill bonus cannot be negative" );
}

std::vector<std::string> TTacticsConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& tacticsConfiguration : {
		CTacticsConfiguration{},
		CTacticsConfiguration{ { { "A", CTacticConfiguration{ 0, 0, { "E" } } }, { "E", CTacticConfiguration{ 0, 0 } } }, 1.3 },
		futsim::ValueFromJSONKeyString<CTacticsConfiguration>( R"( {
			"Tactics configuration": {}
		} )" ),
		futsim::ValueFromJSONKeyString<CTacticsConfiguration>( R"( {
			"Tactics configuration": {
				"Tactic configurations": {
					"A": {
						"Tk bonus": 0,
						"Ps bonus": 0,
						"Favourable tactics": ["E"]
					},
					"E": {
						"Tk bonus": 0,
						"Ps bonus": 0
					}
				},
				"Favourable tactic skill bonus": 1.3
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CTacticsConfiguration>::TACTIC_CONFIGURATIONS } + ":" );
		for( const auto& tacticConfiguration : tacticsConfiguration.GetTacticConfigurations() )
			result.push_back( tacticConfiguration.first );
		result.push_back( std::string{ futsim::json_traits<CTacticsConfiguration>::FAVOURABLE_TACTIC_SKILL_BONUS } + ": " + std::to_string( tacticsConfiguration.GetFavourableTacticSkillBonus() ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, tacticsConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TTacticsConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Tactic configurations:",
		"A",
		"C",
		"D",
		"E",
		"L",
		"N",
		"P",
		"Favourable tactic skill bonus: 1.100000",
		"{\n"
		"	\"Tactics configuration\": {\n"
		"		\"Tactic configurations\": {\n"
		"			\"A\": {\n"
		"				\"Tk bonus\": -0.5,\n"
		"				\"Ps bonus\": -0.2,\n"
		"				\"Favourable tactics\": [\n"
		"					\"D\",\n"
		"					\"E\"\n"
		"				],\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			},\n"
		"			\"C\": {\n"
		"				\"Tk bonus\": 0.5,\n"
		"				\"Ps bonus\": -0.8,\n"
		"				\"Favourable tactics\": [\n"
		"					\"A\",\n"
		"					\"P\"\n"
		"				],\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			},\n"
		"			\"D\": {\n"
		"				\"Tk bonus\": 0.7,\n"
		"				\"Ps bonus\": -0.2,\n"
		"				\"Favourable tactics\": [\n"
		"					\"L\",\n"
		"					\"P\"\n"
		"				],\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			},\n"
		"			\"E\": {\n"
		"				\"Tk bonus\": -0.3,\n"
		"				\"Ps bonus\": 0.2,\n"
		"				\"Favourable tactics\": [\n"
		"					\"C\",\n"
		"					\"D\"\n"
		"				],\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			},\n"
		"			\"L\": {\n"
		"				\"Tk bonus\": 0.3,\n"
		"				\"Ps bonus\": -0.6,\n"
		"				\"Favourable tactics\": [\n"
		"					\"C\",\n"
		"					\"N\"\n"
		"				],\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			},\n"
		"			\"N\": {\n"
		"				\"Tk bonus\": 0.0,\n"
		"				\"Ps bonus\": 0.0,\n"
		"				\"Favourable tactics\": [\n"
		"					\"A\",\n"
		"					\"E\"\n"
		"				],\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			},\n"
		"			\"P\": {\n"
		"				\"Tk bonus\": -0.2,\n"
		"				\"Ps bonus\": 0.6,\n"
		"				\"Favourable tactics\": [\n"
		"					\"L\",\n"
		"					\"N\"\n"
		"				],\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			}\n"
		"		},\n"
		"		\"Favourable tactic skill bonus\": 1.1\n"
		"	}\n"
		"}",
		"Tactic configurations:",
		"A",
		"E",
		"Favourable tactic skill bonus: 1.300000",
		"{\n"
		"	\"Tactics configuration\": {\n"
		"		\"Tactic configurations\": {\n"
		"			\"A\": {\n"
		"				\"Tk bonus\": 0.0,\n"
		"				\"Ps bonus\": 0.0,\n"
		"				\"Favourable tactics\": [\n"
		"					\"E\"\n"
		"				],\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			},\n"
		"			\"E\": {\n"
		"				\"Tk bonus\": 0.0,\n"
		"				\"Ps bonus\": 0.0,\n"
		"				\"Position penalties\": [\n"
		"					0.0,\n"
		"					-0.2,\n"
		"					-0.4\n"
		"				]\n"
		"			}\n"
		"		},\n"
		"		\"Favourable tactic skill bonus\": 1.3\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
