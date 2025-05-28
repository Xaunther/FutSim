#include "ATest.h"

#include "football/CGoalRule.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TGoalRule )

void TGoalRule::TestExceptions()
{
	// Test JSON constructor
	CheckException( []()
		{
			futsim::ValueFromJSONKeyString<CGoalRule>( R"( { "Goal rule" : "Wrong" } )" );
		}, "'Wrong' is not a valid goal rule." );
}

std::vector<std::string> TGoalRule::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& goalRule : {
			CGoalRule{},
			CGoalRule{ CGoalRule::SILVER_GOAL{} },
			CGoalRule{ CGoalRule::GOLDEN_GOAL{} },
			futsim::ValueFromJSONKeyString<CGoalRule>( R"( { "Goal rule" : "No" } )" ),
			futsim::ValueFromJSONKeyString<CGoalRule>( R"( { "Goal rule" : "Silver goal" } )" ),
			futsim::ValueFromJSONKeyString<CGoalRule>( R"( { "Goal rule" : "Golden goal" } )" ),
			} )
	{
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, goalRule );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TGoalRule::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"{\n"
		"	\"Goal rule\": \"No\"\n"
		"}",
		"{\n"
		"	\"Goal rule\": \"Silver goal\"\n"
		"}",
		"{\n"
		"	\"Goal rule\": \"Golden goal\"\n"
		"}",
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
