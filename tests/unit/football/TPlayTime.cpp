#include "ITest.h"

#include "football/CPlayTime.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayTime )

void TPlayTime::TestExceptions() const
{
	CheckException( []() { futsim::ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 2,
				"Period time": 45
			}
		} )" ); }, "key 'Available subs' not found" );
}

std::vector<std::string> TPlayTime::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TPlayTime::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
