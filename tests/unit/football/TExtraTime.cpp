#include "ITest.h"

#include "football/CExtraTime.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TExtraTime )

void TExtraTime::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CExtraTime>( R"( {
			"Extra time": {
				"Period count": 2,
				"Period time": 15,
				"Available subs": 1,
				"Goal rule": "error"
			}
		} )" ); }, "No goal rule matching the string 'error'." );
}

std::vector<std::string> TExtraTime::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TExtraTime::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
