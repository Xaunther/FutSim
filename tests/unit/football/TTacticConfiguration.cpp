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
	return result;
}

std::vector<std::string> TTacticConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
