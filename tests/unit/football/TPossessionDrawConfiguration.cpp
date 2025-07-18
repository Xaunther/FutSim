#include "ATest.h"

#include "football/CPossessionDrawConfiguration.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPossessionDrawConfiguration )

void TPossessionDrawConfiguration::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CPossessionDrawConfiguration{ -2 };
	}, "The probability to keep possession cannot be negative." );
	CheckException( []()
	{
		CPossessionDrawConfiguration{ 2 };
	}, "The probability to keep possession cannot be greater than 1." );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPossessionDrawConfiguration>( R"( {
			"Possession draw configuration": {
				"Keep possession probability": -2
			}
		} )" );
	}, "The probability to keep possession cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPossessionDrawConfiguration>( R"( {
			"Possession draw configuration": {
				"Keep possession probability": 2
			}
		} )" );
	}, "The probability to keep possession cannot be greater than 1." );
}

std::vector<std::string> TPossessionDrawConfiguration::ObtainedResults() noexcept
{
	std::vector<std::string> result;
	for( const auto& possessionDrawConfiguration : {
		CPossessionDrawConfiguration{},
		CPossessionDrawConfiguration{ 0.6 },
		futsim::ValueFromJSONKeyString<CPossessionDrawConfiguration>( R"( {
			"Possession draw configuration": {
				"Keep possession probability": 0.6420632665059802
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CPossessionDrawConfiguration>( R"( {
			"Possession draw configuration": {
				"Keep possession probability": 0.6
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CPossessionDrawConfiguration>::KEEP_POSSESSION_PROBABILITY_KEY } + ": " + std::to_string( possessionDrawConfiguration.GetKeepPossessionProbability() ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, possessionDrawConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TPossessionDrawConfiguration::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Keep possession probability: 0.642063",
		"{\n"
		"	\"Possession draw configuration\": {\n"
		"		\"Keep possession probability\": 0.6420632665059802\n"
		"	}\n"
		"}",
		"Keep possession probability: 0.600000",
		"{\n"
		"	\"Possession draw configuration\": {\n"
		"		\"Keep possession probability\": 0.6\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
