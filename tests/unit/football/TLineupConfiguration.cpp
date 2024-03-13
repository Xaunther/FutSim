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
	for( const auto& lineupConfiguration : std::initializer_list<CLineupConfiguration>{
		CLineupConfiguration{},
		CLineupConfiguration{ { 1, {} }, { 2, 5 }, { 0, 3 }, {} },
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Benched players": 9
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Min DFs": 1,
				"Min MFs": 2,
				"Max MFs": 5,
				"Min FWs": 0,
				"Max FWs": 3
			}
		} )" ) } )
	{
		result.push_back( std::string{ CLineupConfiguration::JSON_MIN_DFS } + ": " + std::to_string( lineupConfiguration.GetDFRange().first ) );
		if( lineupConfiguration.GetDFRange().second )
			result.push_back( std::string{ CLineupConfiguration::JSON_MAX_DFS } + ": " + std::to_string( *lineupConfiguration.GetDFRange().second ) );
		result.push_back( std::string{ CLineupConfiguration::JSON_MIN_MFS } + ": " + std::to_string( lineupConfiguration.GetMFRange().first ) );
		if( lineupConfiguration.GetMFRange().second )
			result.push_back( std::string{ CLineupConfiguration::JSON_MAX_MFS } + ": " + std::to_string( *lineupConfiguration.GetMFRange().second ) );
		result.push_back( std::string{ CLineupConfiguration::JSON_MIN_FWS } + ": " + std::to_string( lineupConfiguration.GetFWRange().first ) );
		if( lineupConfiguration.GetFWRange().second )
			result.push_back( std::string{ CLineupConfiguration::JSON_MAX_FWS } + ": " + std::to_string( *lineupConfiguration.GetFWRange().second ) );
		if( lineupConfiguration.GetBenchedPlayersCount() )
			result.push_back( std::string{ CLineupConfiguration::JSON_BENCHED_PLAYERS } + ": " + std::to_string( *lineupConfiguration.GetBenchedPlayersCount() ) );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, lineupConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TLineupConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Min DFs: 3",
		"Max DFs: 6",
		"Min MFs: 2",
		"Max MFs: 6",
		"Min FWs: 0",
		"Max FWs: 4",
		"Benched players: 9",
		"{\n"
		"	\"Lineup configuration\": {\n"
		"		\"Min DFs\": 3,\n"
		"		\"Max DFs\": 6,\n"
		"		\"Min MFs\": 2,\n"
		"		\"Max MFs\": 6,\n"
		"		\"Min FWs\": 0,\n"
		"		\"Max FWs\": 4,\n"
		"		\"Benched players\": 9\n"
		"	}\n"
		"}",
		"Min DFs: 1",
		"Min MFs: 2",
		"Max MFs: 5",
		"Min FWs: 0",
		"Max FWs: 3",
		"{\n"
		"	\"Lineup configuration\": {\n"
		"		\"Min DFs\": 1,\n"
		"		\"Min MFs\": 2,\n"
		"		\"Max MFs\": 5,\n"
		"		\"Min FWs\": 0,\n"
		"		\"Max FWs\": 3\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
