#include "ITest.h"

#include "football/CFoulDrawConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TFoulDrawConfiguration )

void TFoulDrawConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CFoulDrawConfiguration{ -1 }; }, "The average number of fouls cannot be negative." );
	CheckException( []() { CFoulDrawConfiguration{ CFoulDrawConfiguration::DEFAULT_AVERAGE_FOULS, -1 }; },
		"The average number of yellow cards cannot be negative." );
	CheckException( []() { CFoulDrawConfiguration{ CFoulDrawConfiguration::DEFAULT_AVERAGE_FOULS, CFoulDrawConfiguration::DEFAULT_AVERAGE_YELLOW_CARDS, -1 }; },
		"The average number of red cards cannot be negative." );
	CheckException( []() { CFoulDrawConfiguration{ 0 }; },
		"The average number of fouls minus the average number of yellow and red cards cannot be negative." );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average fouls": -1
			}
		} )" ); }, "The average number of fouls cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average yellow cards": -1
			}
		} )" ); }, "The average number of yellow cards cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average red cards": -1
			}
		} )" ); }, "The average number of red cards cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average fouls": 0
			}
		} )" ); }, "The average number of fouls minus the average number of yellow and red cards cannot be negative." );
}

std::vector<std::string> TFoulDrawConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TFoulDrawConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
