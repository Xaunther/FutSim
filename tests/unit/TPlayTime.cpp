#include "ITest.h"

#include "CPlayTime.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim;
using namespace nlohmann;

INITIALIZE_TEST( TPlayTime )

void TPlayTime::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CPlayTime{ 0, 45 }; },
		"The number of periods cannot be zero." );
	CheckException( []() { CPlayTime{ 2, 0 }; },
		"The length of the period cannot be zero." );

	//! Test JSON constructor
	CheckException( []() { ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {}
		} )" ); }, "key 'Period count' not found" );
	CheckException( []() { ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 0
			}
		} )" ); }, "The number of periods cannot be zero." );
	CheckException( []() { ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 2
			}
		} )" ); }, "key 'Period time' not found" );
	CheckException( []() { ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 2,
				"Period time": 0
			}
		} )" ); }, "The length of the period cannot be zero." );
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
