#include "ATest.h"

#include "football/CPlayerState.h"

#include "football/CFoulState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayerState )

void TPlayerState::TestExceptions() const
{
}

std::vector<std::string> TPlayerState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	std::mt19937 rng{ 1234 };

	const auto state = CPlayerState{}.AddMinutePlayed().AddMinutePlayed().AddMinutePlayed().AddMinutePlayed().AddMinutePlayed()
			.AddFoul( CFoulState{ CMatchConfiguration{}, CTeamStrategy{ "A", CLineup{ "Ter Stegen", {}, {}, {}, {}, {}, {} } }, rng } )
			.AddFoul( CFoulState{ CMatchConfiguration{}, CTeamStrategy{ "A", CLineup{ "Iñaki Peña", {}, {}, {}, {}, {}, {} } }, rng } )
			.AddPass( true ).AddPass( false ).AddSave().AddSave().AddSave().AddShot( false ).AddShot( true ).AddShot( true )
			.AddTackle().AddTackle().AddTackle();

	const auto JSONstate = futsim::ValueFromJSONKeyString<CPlayerState>( R"( {
		"Player state": {
			"Minutes played": 5,
			"Saves": 3,
			"Tackles": 3,
			"Passes": 2,
			"Shots": 3,
			"Assists": 1,
			"Goals": 2,
			"Fouls committed": 2
		}
	} )" );

	for( const auto& playerState : {
			CPlayerState{},
			CPlayerState{} + CPlayerState{},
			state,
			state + state,
			futsim::ValueFromJSONKeyString<CPlayerState>( R"( { "Player state": null } )" ),
			futsim::ValueFromJSONKeyString<CPlayerState>( R"( { "Player state": null } )" ),
			JSONstate,
			JSONstate + JSONstate,
	} )
	{
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::MINUTES_PLAYED_KEY } + ": " + std::to_string( playerState.GetMinutesPlayed() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::SAVES_KEY } + ": " + std::to_string( playerState.GetSaves() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::TACKLES_KEY } + ": " + std::to_string( playerState.GetTackles() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::PASSES_KEY } + ": " + std::to_string( playerState.GetPasses() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::SHOTS_KEY } + ": " + std::to_string( playerState.GetShots() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::ASSISTS_KEY } + ": " + std::to_string( playerState.GetAssists() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::GOALS_KEY } + ": " + std::to_string( playerState.GetGoals() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::FOULS_COMMITTED } + ": " + std::to_string( playerState.GetFoulsCommitted() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::YELLOW_CARDS_KEY } + ": " + std::to_string( playerState.GetYellowCards() ) );	
		result.push_back( std::string{ futsim::json_traits<CPlayerState>::RED_CARDS_KEY } + ": " + std::to_string( playerState.GetRedCards() ) );	
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, playerState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPlayerState::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Minutes played: 0",
		"Saves: 0",
		"Tackles: 0",
		"Passes: 0",
		"Shots: 0",
		"Assists: 0",
		"Goals: 0",
		"Fouls committed: 0",
		"Yellow cards: 0",
		"Red cards: 0",
		"{\n"
		"	\"Player state\": null\n"
		"}",
		"Minutes played: 0",
		"Saves: 0",
		"Tackles: 0",
		"Passes: 0",
		"Shots: 0",
		"Assists: 0",
		"Goals: 0",
		"Fouls committed: 0",
		"Yellow cards: 0",
		"Red cards: 0",
		"{\n"
		"	\"Player state\": null\n"
		"}",
		"Minutes played: 5",
		"Saves: 3",
		"Tackles: 3",
		"Passes: 2",
		"Shots: 3",
		"Assists: 1",
		"Goals: 2",
		"Fouls committed: 2",
		"Yellow cards: 0",
		"Red cards: 0",
		"{\n"
		"	\"Player state\": {\n"
		"		\"Minutes played\": 5,\n"
		"		\"Saves\": 3,\n"
		"		\"Tackles\": 3,\n"
		"		\"Passes\": 2,\n"
		"		\"Shots\": 3,\n"
		"		\"Assists\": 1,\n"
		"		\"Goals\": 2,\n"
		"		\"Fouls committed\": 2\n"
		"	}\n"
		"}",
		"Minutes played: 10",
		"Saves: 6",
		"Tackles: 6",
		"Passes: 4",
		"Shots: 6",
		"Assists: 2",
		"Goals: 4",
		"Fouls committed: 4",
		"Yellow cards: 0",
		"Red cards: 0",
		"{\n"
		"	\"Player state\": {\n"
		"		\"Minutes played\": 10,\n"
		"		\"Saves\": 6,\n"
		"		\"Tackles\": 6,\n"
		"		\"Passes\": 4,\n"
		"		\"Shots\": 6,\n"
		"		\"Assists\": 2,\n"
		"		\"Goals\": 4,\n"
		"		\"Fouls committed\": 4\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
