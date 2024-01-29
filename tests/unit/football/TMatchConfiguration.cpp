#include "ITest.h"

#include "football/CMatchConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TMatchConfiguration )

void TMatchConfiguration::TestExceptions() const
{
	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Play time": {
					"Period count": 2,
					"Period time": 45,
					"Available subs": 5
				}
			}
		} )" ); }, "key 'Apply ambient factor' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatchConfiguration>( R"( {
			"Match configuration": {
				"Play time": {
					"Period count": 2,
					"Period time": 45,
					"Available subs": 5
				},
				"Apply ambient factor": true,
				"Tie condition": {
					"Home team lead": 1,
					"Home team goals": 3
				}
			}
		} )" ); }, "There cannot be a tie condition without a penalty shootout configuration" );
}

std::vector<std::string> TMatchConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TMatchConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
