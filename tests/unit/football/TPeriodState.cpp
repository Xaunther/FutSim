#include "ATest.h"

#include "football/CPeriodState.h"
#include "football/CExtraTimePeriodPlayPolicy.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TPeriodState )

void TPeriodState::TestExceptions()
{
	// Test SDefaultExtraTimePeriodPlayPolicy::CheckMatchConfiguration
	CheckException( []()
	{
		IExtraTimePeriodPlayPolicy::CheckMatchConfiguration( CMatchConfiguration{} );
	},
		"The match configuration cannot be used for the default extra time period play policy." );
}

std::vector<std::string> TPeriodState::ObtainedResults() noexcept
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
		CExtraTime{ futsim::default_traits<CPlayTime>::PERIOD_COUNT, 200, futsim::default_traits<CExtraTime>::AVAILABLE_SUBS, CGoalRule::GOLDEN_GOAL{} },
		CPenaltyShootoutConfiguration{} };

	for( const auto& periodState : {
		CPeriodState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, true, rng },
		CPeriodState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, false, rng },
		CPeriodState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		extraTimeMatchConfig, homeTeamStrategy, awayTeamStrategy, true, rng, CExtraTimePeriodPlayPolicy<CGoalRule::NO>{} },
		CPeriodState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		goldenGoalMatchConfig, homeTeamStrategy, awayTeamStrategy, false, rng, CExtraTimePeriodPlayPolicy<CGoalRule::GOLDEN_GOAL>{} },
		} )
	{
		result.push_back( std::string{ futsim::json_traits<CPeriodState>::PLAYS_KEY } + ": "
			+ std::to_string( periodState.GetPlays().size() ) );

		result.push_back( std::to_string( periodState.CountScore().home ) );
		result.push_back( std::to_string( periodState.CountScore().away ) );

		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, periodState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPeriodState::ExpectedResults() noexcept
{
	return {};
}
