#include "ATest.h"

#include "football/CTieCondition.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTieCondition )

void TTieCondition::TestExceptions()
{
	// Test member constructor.
	CheckException( []()
	{
		CTieCondition{ 5, 1 };
	}, "The home team goals cannot be smaller than the home team lead." );

	// Test JSON constructor.
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTieCondition>( R"( {
			"Tie condition": {
				"Home team lead" : 5,
				"Home team goals": 1
			}
		} )" );
	}, "The home team goals cannot be smaller than the home team lead." );
}

std::vector<std::string> TTieCondition::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& tieCondition : {
		CTieCondition{},
		CTieCondition{ -2 },
		CTieCondition{ 1, 2 },
		futsim::ValueFromJSONKeyString<CTieCondition>( R"( {
			"Tie condition": {
				"Home team lead" : 0
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CTieCondition>( R"( {
			"Tie condition": {
				"Home team lead" : -2
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CTieCondition>( R"( {
			"Tie condition": {
				"Home team lead" : 1,
				"Home team goals": 2
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CTieCondition>::HOME_TEAM_LEAD_KEY } + ": " + std::to_string( tieCondition.GetHomeTeamLead() ) );
		if( tieCondition.GetHomeTeamGoals() )
			result.push_back( std::string{ futsim::json_traits<CTieCondition>::HOME_TEAM_GOALS_KEY } + ": " + std::to_string( *tieCondition.GetHomeTeamGoals() ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, tieCondition );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TTieCondition::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Home team lead: 0",
		"{\n"
		"	\"Tie condition\": {\n"
		"		\"Home team lead\": 0\n"
		"	}\n"
		"}",
		"Home team lead: -2",
		"{\n"
		"	\"Tie condition\": {\n"
		"		\"Home team lead\": -2\n"
		"	}\n"
		"}",
		"Home team lead: 1",
		"Home team goals: 2",
		"{\n"
		"	\"Tie condition\": {\n"
		"		\"Home team lead\": 1,\n"
		"		\"Home team goals\": 2\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
