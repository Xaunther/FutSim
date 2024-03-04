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
	return result;
}

std::vector<std::string> TPossessionDrawConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
