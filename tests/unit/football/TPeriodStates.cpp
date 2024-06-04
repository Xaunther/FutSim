#include "ITest.h"

#include "football/CPeriodStates.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TPeriodStates )

void TPeriodStates::TestExceptions() const
{
	// Test CheckMatchConfiguration
	CheckException( []() { CPeriodStates::SDefaultExtraTimePeriodPolicy::CheckMatchConfiguration( CMatchConfiguration{} ); },
		"The match configuration cannot be used for the default extra time period play policy." );
}

std::vector<std::string> TPeriodStates::ObtainedResults() const noexcept
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

	const CMatchConfiguration extraTimeMatchConfig{ CPlayTime{}, CLineupConfiguration{}, true,
			CTacticsConfiguration{}, CTieCondition{}, CExtraTime{}, CPenaltyShootoutConfiguration{} };
	const CMatchConfiguration goldenGoalMatchConfig{ CPlayTime{}, CLineupConfiguration{}, true, CTacticsConfiguration{}, CTieCondition{},
			CExtraTime{ CExtraTime::DEFAULT_PERIOD_COUNT, 200, CExtraTime::DEFAULT_AVAILABLE_SUBS, E_GOAL_RULE::GOLDEN_GOAL },
			CPenaltyShootoutConfiguration{} };
	const CMatchConfiguration silverGoalMatchConfig{ CPlayTime{}, CLineupConfiguration{}, true, CTacticsConfiguration{}, CTieCondition{},
			CExtraTime{ 20, 15, CExtraTime::DEFAULT_AVAILABLE_SUBS, E_GOAL_RULE::SILVER_GOAL },
			CPenaltyShootoutConfiguration{} };

	for( const auto& periodStates : {
		CPeriodStates{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" }, CMatchConfiguration{},
				homeTeamStrategy, awayTeamStrategy, rng },
		CPeriodStates{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" }, extraTimeMatchConfig,
				homeTeamStrategy, awayTeamStrategy, rng, CPeriodState::SDefaultExtraTimePeriodPlayPolicy{}, CPeriodStates::SDefaultExtraTimePeriodPolicy{} },
		CPeriodStates{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" }, goldenGoalMatchConfig,
				homeTeamStrategy, awayTeamStrategy, rng, CPeriodState::SGoldenGoalPeriodPlayPolicy{}, CPeriodStates::SSilverGoalPeriodPolicy{} },
		CPeriodStates{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" }, silverGoalMatchConfig,
				homeTeamStrategy, awayTeamStrategy, rng, CPeriodState::SDefaultExtraTimePeriodPlayPolicy{}, CPeriodStates::SSilverGoalPeriodPolicy{} },
		} )
	{
		result.push_back( std::string{ CPeriodStates::JSON_KEY } + ": "
			+ std::to_string( periodStates.GetStates().size() ) );

		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, periodStates );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPeriodStates::ExpectedResults() const noexcept
{
	return {};
}
