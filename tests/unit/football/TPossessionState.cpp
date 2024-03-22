#include "ITest.h"

#include "football/CPossessionState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPossessionState )

void TPossessionState::TestExceptions() const
{
}

std::vector<std::string> TPossessionState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	std::mt19937 rng{ 1234 };
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
	const CTeamStrategy homeTeamStrategy{ "A", CLineup{ "Kaminski",
			types::CLineup::names{ "Potts", "Lockyer", "Kaboré", "Bell" },
			{}, types::CLineup::names{ "Barkley", "Nakamba", "Mpanzu", "Clark" }, {},
			types::CLineup::names{ "Morris", "Adebayo" }, {} } };
	const CTeamStrategy awayTeamStrategy{ "N", homeTeamStrategy.GetLineup() };

	for( const auto& possessionState : std::initializer_list{
		CPossessionState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 100 }, "Michael Oliver" },
			CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, true, rng },
		CPossessionState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 100 }, "Michael Oliver" },
			CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, false, rng },
		} )
	{
		result.push_back( std::string{ CPossessionState::JSON_OUTCOME } + ": " + std::string{ ToString( possessionState.GetOutcome() ) } );
		if( possessionState.GetTackler() )
			result.push_back( std::string{ CPossessionState::JSON_TACKLER } + ": " + *possessionState.GetTackler() );
		if( possessionState.GetPasser() )
			result.push_back( std::string{ CPossessionState::JSON_PASSER } + ": " + *possessionState.GetPasser() );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, possessionState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TPossessionState::ExpectedResults() const noexcept
{
	return std::vector<std::string>{
		"Outcome: Keep possession",
			"Passer: Clark",
			"{\n"
			"	\"Possession state\": {\n"
			"		\"Outcome\": \"Keep possession\",\n"
			"		\"Passer\": \"Clark\"\n"
			"	}\n"
			"}",
			"Outcome: Counter attack",
			"Tackler: Bell",
			"{\n"
			"	\"Possession state\": {\n"
			"		\"Outcome\": \"Counter attack\",\n"
			"		\"Tackler\": \"Bell\"\n"
			"	}\n"
			"}"
	};
}
