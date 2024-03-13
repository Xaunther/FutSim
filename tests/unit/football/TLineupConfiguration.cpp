#include "ITest.h"

#include "football/CLineupConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TLineupConfiguration )

void TLineupConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CLineupConfiguration{ CLineupConfigurationTypes::player_count_range{ 1, 0 } }; },
		"The maximum number of DFs cannot be smaller than the minimum number." );
	// Test member constructor
	CheckException( []() { CLineupConfiguration{ CLineupConfiguration::DEFAULT_DF_RANGE,
		CLineupConfigurationTypes::player_count_range{ 1, 0 } }; },
		"The maximum number of MFs cannot be smaller than the minimum number." );
	// Test member constructor
	CheckException( []() { CLineupConfiguration{ CLineupConfiguration::DEFAULT_DF_RANGE,
		CLineupConfiguration::DEFAULT_MF_RANGE,
		CLineupConfigurationTypes::player_count_range{ 1, 0 } }; },
		"The maximum number of FWs cannot be smaller than the minimum number." );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Max DFs": 6
			}
		} )" ); }, "key 'Min DFs' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Min DFs": 1,
				"Max DFs": 0
			}
		} )" ); }, "The maximum number of DFs cannot be smaller than the minimum number." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Max MFs": 6
			}
		} )" ); }, "key 'Min MFs' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Min MFs": 1,
				"Max MFs": 0
			}
		} )" ); }, "The maximum number of MFs cannot be smaller than the minimum number." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Max FWs": 6
			}
		} )" ); }, "key 'Min FWs' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Min FWs": 1,
				"Max FWs": 0
			}
		} )" ); }, "The maximum number of FWs cannot be smaller than the minimum number." );
}

std::vector<std::string> TLineupConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TLineupConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
