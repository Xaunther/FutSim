#include "ITest.h"

#include "football/CTieCondition.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTieCondition )

void TTieCondition::TestExceptions() const
{
	//! Test member constructor.
	CheckException( []() { CTieCondition{ 5, 1 }; }, "The home team goals cannot be smaller than the home team lead." );

	//! Test JSON constructor.
	CheckException( []() { futsim::ValueFromJSONKeyString<CTieCondition>( R"( {
			"Tie condition": {}
		} )" ); }, "key 'Home team lead' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTieCondition>( R"( {
			"Tie condition": {
				"Home team lead" : 5,
				"Home team goals": 1
			}
		} )" ); }, "The home team goals cannot be smaller than the home team lead." );
}

std::vector<std::string> TTieCondition::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TTieCondition::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
