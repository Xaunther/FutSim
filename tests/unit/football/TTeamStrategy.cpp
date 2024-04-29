#include "ITest.h"

#include "football/CTeamStrategy.h"

#include "football/CMatch.h"
#include "football/CMatchConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTeamStrategy )

void TTeamStrategy::TestExceptions() const
{
	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeamStrategy>( R"( {
			"Team strategy": {}
		} )" ); }, "key 'Tactic' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeamStrategy>( R"( {
			"Team strategy": {
				"Tactic": "A"
			}
		} )" ); }, "key 'Lineup' not found" );
}

std::vector<std::string> TTeamStrategy::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& teamStrategy : {
		CTeamStrategy{ "A", CLineup{  "Ter Stegen", {}, {}, {}, {}, {}, {} } },
		futsim::ValueFromJSONKeyString<CTeamStrategy>( R"( {
			"Team strategy": {
				"Tactic": "A",
				"Lineup": {
					"GK": "Ter Stegen"
				}
			}
		} )" ) } )
	{
		result.push_back( std::string{ CTeamStrategy::JSON_TACTIC } + ": " + std::string{ teamStrategy.GetTacticID() } );
		result.push_back( std::string{ CLineup::JSON_KEY } + ": " + std::string{ teamStrategy.GetLineup().GetPlayers< E_PLAYER_POSITION::GK >() } );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, teamStrategy );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	{
		const CTeam team{ "Luton Town FC", "lut", "Rob Edwards", {
				CPlayer{ "Thomas", "Kaminski", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 70, 1, 1, 1 }, {} } },
				CPlayer{ "Dan", "Potts", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 70, 1, 1 }, {} } },
				CPlayer{ "Tom", "Lockyer", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 80, 1, 1 }, {} } },
				CPlayer{ "Issa", "Kaboré", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 60, 1, 1 }, {} } },
				CPlayer{ "Amari'i", "Bell", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 60, 1, 1 }, {} } },
				CPlayer{ "Ross", "Barkley", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 80, 1 }, {} } },
				CPlayer{ "Marvelous", "Nakamba", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 75, 1 }, {} } },
				CPlayer{ "Pelly Ruddock", "Mpanzu", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 60, 1 }, {} } },
				CPlayer{ "Jordan", "Clark", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 70, 1 }, {} } },
				CPlayer{ "Carlton", "Morris", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 1, 75 }, {} } },
				CPlayer{ "Elijah", "Adebayo", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 1, 75 }, {} } },
				},
				1.2, 11000, 2000 };
		const CStadium stadium{ "The New Lawn", 5147, 1.1 };
		const CMatch match{ team, team, stadium, "Michael Oliver" };
		const CTeamStrategy homeTeamStrategy{ "A", CLineup{ "Kaminski",
			types::CLineup::names{ "Potts", "Lockyer", "Kaboré", "Bell" },
			{}, types::CLineup::names{ "Barkley", "Nakamba", "Mpanzu", "Clark" }, {},
			types::CLineup::names{ "Morris", "Adebayo" }, {} } };
		const CTeamStrategy awayTeamStrategy{ "N", homeTeamStrategy.GetLineup() };

		homeTeamStrategy.ForEachPlayerSkill( E_PLAYER_SKILL::St, match, CMatchConfiguration{}, true, awayTeamStrategy,
			[ &result ]( const auto& aSkill ) { result.push_back( std::to_string( aSkill ) ); } );
		homeTeamStrategy.ForEachPlayerSkill( E_PLAYER_SKILL::Tk, match, CMatchConfiguration{}, true, awayTeamStrategy,
			[ &result ]( const auto& aSkill ) { result.push_back( std::to_string( aSkill ) ); } );
		awayTeamStrategy.ForEachPlayerSkill( E_PLAYER_SKILL::St, match, CMatchConfiguration{}, false, homeTeamStrategy,
			[ &result ]( const auto& aSkill ) { result.push_back( std::to_string( aSkill ) ); } );
		awayTeamStrategy.ForEachPlayerSkill( E_PLAYER_SKILL::Tk, match, CMatchConfiguration{}, false, homeTeamStrategy,
			[ &result ]( const auto& aSkill ) { result.push_back( std::to_string( aSkill ) ); } );
	}

	return result;
}

std::vector<std::string> TTeamStrategy::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Tactic: A",
		"Lineup: Ter Stegen",
		"{\n"
		"	\"Team strategy\": {\n"
		"		\"Tactic\": \"A\",\n"
		"		\"Lineup\": {\n"
		"			\"GK\": \"Ter Stegen\"\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );

	result.insert( result.cend(), {
		// Home team St skills tactic A against N
		"92.400000", // 70 * 1 * 1.2 * 1.1
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		// Home team Tk skills tactic A against N
		"0.000000",
		// Base * 1 * 1.2 * 1.1 * (43/30)
		"132.440000",
		"151.360000",
		"113.520000",
		"113.520000",
		// Base * 1 * 1.2 * 1.1 * (19/30)
		"0.836000",
		"0.836000",
		"0.836000",
		"0.836000",
		// Base * 1 * 1.2 * 1.1 * (13/30)
		"0.572000",
		"0.572000",
		// Away team St skills tactic N against A
		"77.000000", // 70 * 1.1 * 1 * 1
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		"0.000000",
		// Away team Tk skills tactic N against A
		"0.000000",
		// Base * 1.1 * 1 * 1 * (16/10)
		"123.200000",
		"140.800000",
		"105.600000",
		"105.600000",
		// Base * 1.1 * 1 * 1 * (8/10)
		"0.880000",
		"0.880000",
		"0.880000",
		"0.880000",
		// Base * 1.1 * 1 * 1 * (6/10)
		"0.660000",
		"0.660000"
		} );
	return result;
}
