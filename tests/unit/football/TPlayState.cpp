#include "ITest.h"

#include "football/CPlayState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TPlayState )

void TPlayState::TestExceptions() const
{
}

std::vector<std::string> TPlayState::ObtainedResults() const noexcept
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

	for( const auto& playState : {
		CPlayState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 100 }, "Michael Oliver" },
		CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, true, rng },
		CPlayState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 100 }, "Michael Oliver" },
		CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, false, rng },
		} )
	{
		result.push_back( std::string{ futsim::json_traits<CPossessionState>::KEY } + ": "
			+ std::string{ ToString( playState.GetPossessionState().GetOutcome() ) } );
		if( playState.GetFoulState() )
			result.push_back( std::string{ futsim::json_traits<CFoulState>::KEY } + ": "
				+ std::string{ ToString( ( *playState.GetFoulState() ).GetOutcome() ) } );
		result.push_back( std::string{ futsim::json_traits<CPlayState>::CHANCES } );
		for( const auto& chance : playState.GetChancesStates() )
			result.push_back( std::string{ ToString( chance.GetChanceOutcome() ) } );

		result.push_back( std::to_string( playState.IsGoalScored() ) );

		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, playState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPlayState::ExpectedResults() const noexcept
{
	return {};
}
