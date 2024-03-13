#include "ITest.h"

#include "football/CLineup.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TLineup )

void TLineup::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CLineup{ CLineupTypes::position_names{} }; }, "There has to be exactly 1 GK." );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineup>( R"( {
			"Lineup": {}
		} )" ); }, "key 'GK' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineup>( R"( {
			"Lineup": {
				"GK": []
			}
		} )" ); }, "There has to be exactly 1 GK." );
}

std::vector<std::string> TLineup::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TLineup::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
