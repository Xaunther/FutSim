#include "ATest.h"

#include "football/CLineupConfiguration.h"

#include "football/CLineup.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TLineupConfiguration )

void TLineupConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []()
	{
		CLineupConfiguration{ types::CLineupConfiguration::player_count_range{ .min=1, .max=0 } };
	},
		"The maximum number of DFs cannot be smaller than the minimum number." );
	CheckException( []()
	{
		CLineupConfiguration{ futsim::default_traits<CLineupConfiguration>::DF_RANGE,
		types::CLineupConfiguration::player_count_range{ .min=1, .max=0 } };
	},
		"The maximum number of MFs cannot be smaller than the minimum number." );
	CheckException( []()
	{
		CLineupConfiguration{ futsim::default_traits<CLineupConfiguration>::DF_RANGE,
		futsim::default_traits<CLineupConfiguration>::MF_RANGE,
		types::CLineupConfiguration::player_count_range{ .min=1, .max=0 } };
	},
		"The maximum number of FWs cannot be smaller than the minimum number." );
	CheckException( []()
	{
		CLineupConfiguration{ futsim::default_traits<CLineupConfiguration>::DF_RANGE,
		futsim::default_traits<CLineupConfiguration>::MF_RANGE, futsim::default_traits<CLineupConfiguration>::FW_RANGE, 12 };
	},
		"The maximum number of players cannot be smaller than the minimum number." );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Max DFs": 6
			}
		} )" );
	}, "key 'Min DFs' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Min DFs": 1,
				"Max DFs": 0
			}
		} )" );
	}, "The maximum number of DFs cannot be smaller than the minimum number." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Max MFs": 6
			}
		} )" );
	}, "key 'Min MFs' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Min MFs": 1,
				"Max MFs": 0
			}
		} )" );
	}, "The maximum number of MFs cannot be smaller than the minimum number." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Max FWs": 6
			}
		} )" );
	}, "key 'Min FWs' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Min FWs": 1,
				"Max FWs": 0
			}
		} )" );
	}, "The maximum number of FWs cannot be smaller than the minimum number." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CLineupConfiguration>( R"( {
			"Lineup configuration": {
				"Min players": 12
			}
		} )" );
	}, "The maximum number of players cannot be smaller than the minimum number." );

	// Test CheckLineup
	{
		const CLineupConfiguration lineupConfiguration;
		CheckException( [ &lineupConfiguration ]()
		{
			lineupConfiguration.CheckLineup( CLineup{
				"Kelleher", {}, {}, {}, {}, {}, {} } );
		},
			"The lineup has less DF (0) than the minimum allowed (3)." );
		CheckException( [ &lineupConfiguration ]()
		{
			lineupConfiguration.CheckLineup( CLineup{
				"Kelleher", types::CLineup::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez", "A.A.", "Robertson", "Konate" }, {}, {}, {}, {}, {} } );
		},
			"The lineup has more DF (7) than the maximum allowed (6)." );
		CheckException( [ &lineupConfiguration ]()
		{
			lineupConfiguration.CheckLineup( CLineup{
				"Kelleher", types::CLineup::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" }, {}, {}, {}, {}, {} } );
		},
			"The lineup has less DM+MF+AM (0) than the minimum allowed (2)." );
		CheckException( [ &lineupConfiguration ]()
		{
			lineupConfiguration.CheckLineup( CLineup{
				"Kelleher", types::CLineup::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" },
				types::CLineup::names{ "Endo", "Mac Allister", "Szoboszlai", "Elliot", "Darwin Núñez", "Luis Díaz", "Salah" }, {}, {}, {}, {} } );
		},
			"The lineup has more DM+MF+AM (7) than the maximum allowed (6)." );
		CheckException( [ &lineupConfiguration ]()
		{
			lineupConfiguration.CheckLineup( CLineup{
				"Kelleher", types::CLineup::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" },
				types::CLineup::names{ "Endo" }, types::CLineup::names{ "Mac Allister", "Szoboszlai" }, types::CLineup::names{},
				types::CLineup::names{ "Salah", "Gakpo", "Robertson", "Adrián", "Tsimikas", "Bobby Clark", "McConnell", "Nallo", "Koumas" }, {} } );
		},
			"The lineup has more FW (9) than the maximum allowed (4)." );
		CheckException( [ &lineupConfiguration ]()
		{
			lineupConfiguration.CheckLineup( CLineup{
				"Kelleher", types::CLineup::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" },
				types::CLineup::names{ "Endo" }, types::CLineup::names{ "Mac Allister", "Szoboszlai" }, types::CLineup::names{},
				types::CLineup::names{ "Elliot", "Darwin Núñez", "Luis Díaz" },
				types::CLineup::names{ "Salah", "Gakpo", "Robertson", "Adrián", "Tsimikas", "Bobby Clark", "McConnell", "Nallo", "Koumas", "Trent", "Konate", "Allison" } } );
		},
			"The lineup has more subs (12) than the maximum allowed (9)." );
		CheckException( [ &lineupConfiguration ]()
		{
			lineupConfiguration.CheckLineup( CLineup{
				"Kelleher", types::CLineup::names{ "Bradley", "Quansah", "Van Dijk" },
				types::CLineup::names{ "Endo" }, types::CLineup::names{ "Mac Allister" }, types::CLineup::names{}, {}, {} } );
		},
			"The lineup has less players (6) than the minimum allowed (7)." );
		CheckException( [ &lineupConfiguration ]()
		{
			lineupConfiguration.CheckLineup( CLineup{
				"Kelleher", types::CLineup::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez", "Robertson" },
				types::CLineup::names{ "Endo" }, types::CLineup::names{ "Mac Allister", "Szoboszlai" }, types::CLineup::names{},
				types::CLineup::names{ "Elliot", "Darwin Núñez", "Luis Díaz" }, {} } );
		},
			"The lineup has more players (12) than the maximum allowed (11)." );
	}
}

std::vector<std::string> TLineupConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& lineupConfiguration : {
		CLineupConfiguration{},
		CLineupConfiguration{ { 1, {} }, { 2, 5 }, { 0, 3 }, 8, {} },
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
				"Max FWs": 3,
				"Min players": 8
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CLineupConfiguration>::MIN_DFS_KEY } + ": " + std::to_string( lineupConfiguration.GetDFRange().min ) );
		if( lineupConfiguration.GetDFRange().max )
			result.push_back( std::string{ futsim::json_traits<CLineupConfiguration>::MAX_DFS_KEY } + ": " + std::to_string( *lineupConfiguration.GetDFRange().max ) );
		result.push_back( std::string{ futsim::json_traits<CLineupConfiguration>::MIN_MFS_KEY } + ": " + std::to_string( lineupConfiguration.GetMFRange().min ) );
		if( lineupConfiguration.GetMFRange().max )
			result.push_back( std::string{ futsim::json_traits<CLineupConfiguration>::MAX_MFS_KEY } + ": " + std::to_string( *lineupConfiguration.GetMFRange().max ) );
		result.push_back( std::string{ futsim::json_traits<CLineupConfiguration>::MIN_FWS_KEY } + ": " + std::to_string( lineupConfiguration.GetFWRange().min ) );
		if( lineupConfiguration.GetFWRange().max )
			result.push_back( std::string{ futsim::json_traits<CLineupConfiguration>::MAX_FWS_KEY } + ": " + std::to_string( *lineupConfiguration.GetFWRange().max ) );
		result.push_back( std::string{ futsim::json_traits<CLineupConfiguration>::MIN_PLAYERS_KEY } + ": " + std::to_string( lineupConfiguration.GetMinPlayerCount() ) );
		if( lineupConfiguration.GetBenchedPlayersCount() )
			result.push_back( std::string{ futsim::json_traits<CLineupConfiguration>::BENCHED_PLAYERS_KEY } + ": " + std::to_string( *lineupConfiguration.GetBenchedPlayersCount() ) );
		futsim::types::IJsonable::json outputJSON;
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
		"Min players: 7",
		"Benched players: 9",
		"{\n"
		"	\"Lineup configuration\": {\n"
		"		\"Min DFs\": 3,\n"
		"		\"Max DFs\": 6,\n"
		"		\"Min MFs\": 2,\n"
		"		\"Max MFs\": 6,\n"
		"		\"Min FWs\": 0,\n"
		"		\"Max FWs\": 4,\n"
		"		\"Min players\": 7,\n"
		"		\"Benched players\": 9\n"
		"	}\n"
		"}",
		"Min DFs: 1",
		"Min MFs: 2",
		"Max MFs: 5",
		"Min FWs: 0",
		"Max FWs: 3",
		"Min players: 8",
		"{\n"
		"	\"Lineup configuration\": {\n"
		"		\"Min DFs\": 1,\n"
		"		\"Min MFs\": 2,\n"
		"		\"Max MFs\": 5,\n"
		"		\"Min FWs\": 0,\n"
		"		\"Max FWs\": 3,\n"
		"		\"Min players\": 8\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
