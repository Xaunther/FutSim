#include "ATest.h"

#include "football/CLineup.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TLineup )

void TLineup::TestExceptions()
{
	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CLineup>( R"( {
			"Lineup": {}
		} )" );
	}, "key 'GK' not found" );
}

std::vector<std::string> TLineup::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& lineup : {
		CLineup{ "Kelleher",
		types::CLineup::names{ "Bradley", "Quansah", "Van Dijk", "Joe Gomez" },
		types::CLineup::names{ "Endo" }, types::CLineup::names{ "Mac Allister", "Szoboszlai" }, types::CLineup::names{},
		types::CLineup::names{ "Elliot", "Darwin Núñez", "Luis Díaz" },
		types::CLineup::names{ "Salah", "Gakpo", "Robertson", "Adrián", "Tsimikas", "Bobby Clark", "McConnell", "Nallo", "Koumas" } },
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
		result.push_back( std::string{ futsim::json_traits<CLineup>::POSITION_KEY<E_PLAYER_POSITION::GK> } + ": " + std::string{ lineup.GetPlayers< E_PLAYER_POSITION::GK >() } );
		result.push_back( std::string{ futsim::json_traits<CLineup>::POSITION_KEY<E_PLAYER_POSITION::DF> } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::DF >() )
			result.push_back( player );
		result.push_back( std::string{ futsim::json_traits<CLineup>::POSITION_KEY<E_PLAYER_POSITION::DM> } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::DM >() )
			result.push_back( player );
		result.push_back( std::string{ futsim::json_traits<CLineup>::POSITION_KEY<E_PLAYER_POSITION::MF> } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::MF >() )
			result.push_back( player );
		result.push_back( std::string{ futsim::json_traits<CLineup>::POSITION_KEY<E_PLAYER_POSITION::AM> } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::AM >() )
			result.push_back( player );
		result.push_back( std::string{ futsim::json_traits<CLineup>::POSITION_KEY<E_PLAYER_POSITION::FW> } + ":" );
		for( const auto& player : lineup.GetPlayers< E_PLAYER_POSITION::FW >() )
			result.push_back( player );
		result.push_back( std::string{ futsim::json_traits<CLineup>::SUBS_KEY } + ":" );
		for( const auto& player : lineup.GetSubs() )
			result.push_back( player );
		result.emplace_back( "Playing players:" );
		for( const auto& player : lineup.CreatePlayersView<false>() )
			result.push_back( player );
		result.emplace_back( "All players:" );
		for( const auto& player : lineup.CreatePlayersView<true>() )
			result.push_back( player );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, lineup );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TLineup::ExpectedResults() noexcept
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
