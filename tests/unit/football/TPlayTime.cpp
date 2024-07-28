#include "ITest.h"

#include "football/CPlayTime.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayTime )

void TPlayTime::TestExceptions() const
{
}

std::vector<std::string> TPlayTime::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& playTime : {
		CPlayTime{},
		CPlayTime{ 3, 15, 1 },
		CPlayTime{ 2, 45, {} },
		futsim::ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 2,
				"Period time": 45,
				"Available subs": 5
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 3,
				"Period time": 15,
				"Available subs": 1
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 2,
				"Period time": 45
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CPlayTime>::AVAILABLE_SUBS } + ": " + std::to_string( playTime.GetAvailableSubs().value_or( 9999 ) ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, playTime );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPlayTime::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Available subs: 5",
		"{\n"
		"	\"Play time\": {\n"
		"		\"Period count\": 2,\n"
		"		\"Period time\": 45,\n"
		"		\"Available subs\": 5\n"
		"	}\n"
		"}",
		"Available subs: 1",
		"{\n"
		"	\"Play time\": {\n"
		"		\"Period count\": 3,\n"
		"		\"Period time\": 15,\n"
		"		\"Available subs\": 1\n"
		"	}\n"
		"}",
		"Available subs: 9999",
		"{\n"
		"	\"Play time\": {\n"
		"		\"Period count\": 2,\n"
		"		\"Period time\": 45\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
