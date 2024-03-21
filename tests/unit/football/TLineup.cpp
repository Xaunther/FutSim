#include "ITest.h"

#include "football/CLineup.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TLineup )

void TLineup::TestExceptions() const
{
	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CLineup>( R"( {
			"Lineup": {}
		} )" ); }, "key 'GK' not found" );

	// Test GetPlayer method
	CheckException( []() { CLineup{ "Ter Stegen", {}, {}, {}, {}, {}, {} }.GetPlayer( 2 ); },
		"Player index 2 out of range." );
}

std::vector<std::string> TLineup::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& lineup : std::initializer_list<CLineup>{
		CLineup{ "Kelleher",
			CLineupTypes::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" },
			CLineupTypes::names{ "Endo" }, CLineupTypes::names{ "Mac Allister", "Szoboszlai" }, CLineupTypes::names{},
			CLineupTypes::names{ "Elliot", "Darwin Núñez", "Luis Díaz" },
			CLineupTypes::names{ "Salah", "Gakpo", "Robertson", "Adrián", "Tsimikas", "Bobby Clark", "McConnell", "Nallo", "Koumas" } },
		futsim::ValueFromJSONKeyString<CLineup>( R"( {
			"Lineup": {
				"GK": "Kelleher",
				"DFs": [ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" ],
				"DMs": [ "Endo" ],
				"MFs": [ "Mac Allister", "Szoboszlai" ],
				"FWs": [ "Elliot", "Darwin Núñez", "Luis Díaz" ],
				"Subs": [ "Salah", "Gakpo", "Robertson", "Adrián", "Tsimikas", "Bobby Clark", "McConnell", "Nallo", "Koumas" ]
			}
		} )" ) } )
	{
		result.push_back( std::string{ CLineup::JSON_GK } + ": " + std::string{ lineup.GetPlayers< E_PLAYER_POSITION::GK >() } );
		result.push_back( std::string{ CLineup::JSON_DFS } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::DF >() )
			result.push_back( player );
		result.push_back( std::string{ CLineup::JSON_DMS } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::DM >() )
			result.push_back( player );
		result.push_back( std::string{ CLineup::JSON_MFS } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::MF >() )
			result.push_back( player );
		result.push_back( std::string{ CLineup::JSON_AMS } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::AM >() )
			result.push_back( player );
		result.push_back( std::string{ CLineup::JSON_FWS } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::FW >() )
			result.push_back( player );
		result.push_back( std::string{ CLineup::JSON_SUBS } + ":" );
		for( const auto& player : lineup.GetSubs() )
			result.push_back( player );
		result.push_back( "Player count: " + std::to_string( lineup.GetPlayersCount<true>() ) );
		result.push_back( "Player count without subs: " + std::to_string( lineup.GetPlayersCount<false>() ) );
		result.push_back( "GK: " + std::string{ lineup.GetPlayer( 0 ) } );
		result.push_back( "Playing players:" );
		lineup.ForEachPlayer<false>( [ &result ]( const auto& aPlayer ) { result.push_back( aPlayer ); } );
		result.push_back( "All players:" );
		lineup.ForEachPlayer<true>( [ &result ]( const auto& aPlayer ) { result.push_back( aPlayer ); } );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, lineup );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TLineup::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"GK: Kelleher",
		"DFs:",
		"Bradley",
		"Quansah",
		"Van Dijk",
		"Joe Gomez",
		"DMs:",
		"Endo",
		"MFs:",
		"Mac Allister",
		"Szoboszlai",
		"AMs:",
		"FWs:",
		"Elliot",
		"Darwin Núñez",
		"Luis Díaz",
		"Subs:",
		"Salah",
		"Gakpo",
		"Robertson",
		"Adrián",
		"Tsimikas",
		"Bobby Clark",
		"McConnell",
		"Nallo",
		"Koumas",
		"Player count: 20",
		"Player count without subs: 11",
		"GK: Kelleher",
		"Playing players:",
		"Kelleher",
		"Bradley",
		"Quansah",
		"Van Dijk",
		"Joe Gomez",
		"Endo",
		"Mac Allister",
		"Szoboszlai",
		"Elliot",
		"Darwin Núñez",
		"Luis Díaz",
		"All players:",
		"Kelleher",
		"Bradley",
		"Quansah",
		"Van Dijk",
		"Joe Gomez",
		"Endo",
		"Mac Allister",
		"Szoboszlai",
		"Elliot",
		"Darwin Núñez",
		"Luis Díaz",
		"Salah",
		"Gakpo",
		"Robertson",
		"Adrián",
		"Tsimikas",
		"Bobby Clark",
		"McConnell",
		"Nallo",
		"Koumas",
		"{\n"
		"	\"Lineup\": {\n"
		"		\"GK\": \"Kelleher\",\n"
		"		\"DFs\": [\n"
		"			\"Bradley\",\n"
		"			\"Quansah\",\n"
		"			\"Van Dijk\",\n"
		"			\"Joe Gomez\"\n"
		"		],\n"
		"		\"DMs\": [\n"
		"			\"Endo\"\n"
		"		],\n"
		"		\"MFs\": [\n"
		"			\"Mac Allister\",\n"
		"			\"Szoboszlai\"\n"
		"		],\n"
		"		\"FWs\": [\n"
		"			\"Elliot\",\n"
		"			\"Darwin Núñez\",\n"
		"			\"Luis Díaz\"\n"
		"		],\n"
		"		\"Subs\": [\n"
		"			\"Salah\",\n"
		"			\"Gakpo\",\n"
		"			\"Robertson\",\n"
		"			\"Adrián\",\n"
		"			\"Tsimikas\",\n"
		"			\"Bobby Clark\",\n"
		"			\"McConnell\",\n"
		"			\"Nallo\",\n"
		"			\"Koumas\"\n"
		"		]\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
