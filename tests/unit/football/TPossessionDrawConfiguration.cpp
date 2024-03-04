#include "ITest.h"

#include "football/CPossessionDrawConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPossessionDrawConfiguration )

void TPossessionDrawConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CPossessionDrawConfiguration{ -2 }; }, "The probability to keep possession cannot be negative." );
	CheckException( []() { CPossessionDrawConfiguration{ 2 }; }, "The probability to keep possession cannot be greater than 1." );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CPossessionDrawConfiguration>( R"( {
			"Possession draw configuration": {}
		} )" ); }, "key 'Keep possession probability' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CPossessionDrawConfiguration>( R"( {
			"Possession draw configuration": {
				"Keep possession probability": -2
			}
		} )" ); }, "The probability to keep possession cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CPossessionDrawConfiguration>( R"( {
			"Possession draw configuration": {
				"Keep possession probability": 2
			}
		} )" ); }, "The probability to keep possession cannot be greater than 1." );
}

std::vector<std::string> TPossessionDrawConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& possessionDrawConfiguration : {
		CPossessionDrawConfiguration{ 295952.0 / 460939.0 },
		futsim::ValueFromJSONKeyString<CPossessionDrawConfiguration>( R"( {
			"Possession draw configuration": {
				"Keep possession probability": 0.6420632665059802
			}
		} )" ) } )
	{
		result.push_back( std::string{ CPossessionDrawConfiguration::JSON_KEEP_POSSESSION_PROBABILITY } + ": " + std::to_string( possessionDrawConfiguration.GetKeepPossessionProbability() ) );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, possessionDrawConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TPossessionDrawConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Keep possession probability: 0.642063",
		"{\n"
		"	\"Possession draw configuration\": {\n"
		"		\"Keep possession probability\": 0.6420632665059802\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
