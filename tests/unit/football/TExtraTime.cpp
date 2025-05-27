#include "ATest.h"

#include "football/CExtraTime.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TExtraTime )

void TExtraTime::TestExceptions()
{
}

std::vector<std::string> TExtraTime::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& extraTime : {
		CExtraTime{},
		CExtraTime{ 1, 30, 2, CGoalRule::GOLDEN_GOAL{} },
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
		result.push_back( std::string{ futsim::json_traits<CGoalRule>::KEY } + ": " + std::string{ std::visit(
				[]( auto&& aRule ) -> std::string_view { return aRule; }, static_cast<CGoalRule::variant>( extraTime.GetGoalRule() ) ) } );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, extraTime );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TExtraTime::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Goal rule: No",
		"{\n"
		"	\"Extra time\": {\n"
		"		\"Period count\": 2,\n"
		"		\"Period time\": 15,\n"
		"		\"Available subs\": 1\n"
		"	}\n"
		"}",
		"Goal rule: Golden goal",
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
