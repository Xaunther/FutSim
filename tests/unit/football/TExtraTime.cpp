#include "ITest.h"

#include "football/CExtraTime.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TExtraTime )

void TExtraTime::TestExceptions() const
{
}

std::vector<std::string> TExtraTime::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& extraTime : {
		CExtraTime{},
		CExtraTime{ 1, 30, 2, E_GOAL_RULE::GOLDEN_GOAL },
		futsim::ValueFromJSONKeyString<CExtraTime>( R"( {
			"Extra time": {
				"Period count": 2,
				"Period time": 15,
				"Available subs": 1
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CExtraTime>( R"( {
			"Extra time": {
				"Period count": 1,
				"Period time": 30,
				"Available subs": 2,
				"Goal rule": "Golden goal"
			}
		} )" ) } )
	{
		result.push_back( std::string{ CExtraTime::JSON_GOAL_RULE } + ": " + std::to_string( static_cast< int >( extraTime.GetGoalRule() ) ) );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, extraTime );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TExtraTime::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Goal rule: 0",
		"{\n"
		"	\"Extra time\": {\n"
		"		\"Period count\": 2,\n"
		"		\"Period time\": 15,\n"
		"		\"Available subs\": 1\n"
		"	}\n"
		"}",
		"Goal rule: 2",
		"{\n"
		"	\"Extra time\": {\n"
		"		\"Period count\": 1,\n"
		"		\"Period time\": 30,\n"
		"		\"Available subs\": 2,\n"
		"		\"Goal rule\": \"Golden goal\"\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
