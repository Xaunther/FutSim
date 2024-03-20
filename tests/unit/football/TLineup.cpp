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

	// Test DrawPlayer method
	{
		std::mt19937 rng{ 1234 };
		const CLineup lineup{ CLineupTypes::position_names{ CLineupTypes::names{ "Kelleher" },
			CLineupTypes::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" },
			CLineupTypes::names{ "Endo" }, CLineupTypes::names{ "Mac Allister", "Szoboszlai" }, CLineupTypes::names{},
			CLineupTypes::names{ "Elliot", "Darwin Núñez", "Luis Díaz" },
			CLineupTypes::names{ "Salah", "Gakpo", "Robertson", "Adrián", "Tsimikas", "Bobby Clark", "McConnell", "Nallo", "Koumas" } } };
		if( auto drawnPlayer = lineup.DrawPlayer( rng, { 1 } ); drawnPlayer != "Kelleher" )
			throw std::invalid_argument{ "Kelleher should have been drawn instead of " + std::string{ drawnPlayer } + "." };
		if( auto drawnPlayer = lineup.DrawPlayer( rng, { 0, 0, 1 } ); drawnPlayer != "Endo" )
			throw std::invalid_argument{ "Endo should have been drawn instead of " + std::string{ drawnPlayer } + "." };
	}
}

std::vector<std::string> TLineup::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& lineup : std::initializer_list<CLineup>{
		CLineup{ CLineupTypes::position_names{ CLineupTypes::names{ "Kelleher" },
			CLineupTypes::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" },
			CLineupTypes::names{ "Endo" }, CLineupTypes::names{ "Mac Allister", "Szoboszlai" }, CLineupTypes::names{},
			CLineupTypes::names{ "Elliot", "Darwin Núñez", "Luis Díaz" },
			CLineupTypes::names{ "Salah", "Gakpo", "Robertson", "Adrián", "Tsimikas", "Bobby Clark", "McConnell", "Nallo", "Koumas" } } },
		futsim::ValueFromJSONKeyString<CLineup>( R"( {
			"Lineup": {
				"GK": [ "Kelleher" ],
				"DFs": [ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" ],
				"DMs": [ "Endo" ],
				"MFs": [ "Mac Allister", "Szoboszlai" ],
				"FWs": [ "Elliot", "Darwin Núñez", "Luis Díaz" ],
				"Subs": [ "Salah", "Gakpo", "Robertson", "Adrián", "Tsimikas", "Bobby Clark", "McConnell", "Nallo", "Koumas" ]
			}
		} )" ) } )
	{
		result.push_back( std::string{ CLineup::JSON_GK } + ": " + lineup.GetPlayers< E_PLAYER_POSITION::GK >().front() );
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
		"{\n"
		"	\"Lineup\": {\n"
		"		\"GK\": [\n"
		"			\"Kelleher\"\n"
		"		],\n"
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
