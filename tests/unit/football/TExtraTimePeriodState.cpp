#include "ITest.h"

#include "football/CExtraTimePeriodState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TPeriodState )

void TPeriodState::TestExceptions() const
{
	// Test CheckMatchConfiguration
	CheckException( []() { CExtraTimePeriodState::CheckMatchConfiguration( CMatchConfiguration{} ); },
		"The match configuration cannot configure an extra time period state." );
}

std::vector<std::string> TPeriodState::ObtainedResults() const noexcept
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

	const CMatchConfiguration matchConfig{ CPlayTime{}, CLineupConfiguration{}, true,
			CTacticsConfiguration{}, CTieCondition{}, CExtraTime{}, CPenaltyShootoutConfiguration{} };
	const CMatchConfiguration goldenGoalMatchConfig{ CPlayTime{}, CLineupConfiguration{}, true, CTacticsConfiguration{}, CTieCondition{},
			CExtraTime{ CExtraTime::DEFAULT_PERIOD_COUNT, 90, CExtraTime::DEFAULT_AVAILABLE_SUBS, E_GOAL_RULE::GOLDEN_GOAL },
			CPenaltyShootoutConfiguration{} };

	for( const auto& extraTimePeriodState : {
		CExtraTimePeriodState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
			matchConfig, homeTeamStrategy, awayTeamStrategy, true, rng },
		CExtraTimePeriodState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
			goldenGoalMatchConfig, homeTeamStrategy, awayTeamStrategy, false, rng },
		} )
	{
		result.push_back( std::string{ CExtraTimePeriodState::JSON_PLAYS } + ": "
			+ std::to_string( extraTimePeriodState.GetPlays().size() ) );

		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, extraTimePeriodState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPeriodState::ExpectedResults() const noexcept
{
	return {};
}
