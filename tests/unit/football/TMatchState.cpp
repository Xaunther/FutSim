#include "ATest.h"

#include "football/CMatchState.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TMatchState )

void TMatchState::TestExceptions()
{
}

std::vector<std::string> TMatchState::ObtainedResults() noexcept
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

	const CMatchConfiguration noExtraMatchConfig{ CPlayTime{ 1, 1 } };
	const CMatchConfiguration extraTimeMatchConfig{ CPlayTime{ 1, 1 }, CLineupConfiguration{}, true,
		CTacticsConfiguration{}, CTieCondition{}, CExtraTime{}, CPenaltyShootoutConfiguration{} };
	const CMatchConfiguration goldenGoalMatchConfig{ CPlayTime{ 1, 1 }, CLineupConfiguration{}, true, CTacticsConfiguration{}, CTieCondition{},
		CExtraTime{ futsim::default_traits<CPlayTime>::PERIOD_COUNT, 200, futsim::default_traits<CExtraTime>::AVAILABLE_SUBS, CGoalRule::GOLDEN_GOAL{} },
		CPenaltyShootoutConfiguration{} };
	const CMatchConfiguration silverGoalMatchConfig{ CPlayTime{ 1, 1 }, CLineupConfiguration{}, true, CTacticsConfiguration{}, CTieCondition{},
		CExtraTime{ 20, 15, futsim::default_traits<CExtraTime>::AVAILABLE_SUBS, CGoalRule::SILVER_GOAL{} },
		CPenaltyShootoutConfiguration{} };
	const CMatchConfiguration penaltyMatchConfig{ CPlayTime{ 1, 1 }, CLineupConfiguration{}, true, CTacticsConfiguration{}, CTieCondition{},
		{}, CPenaltyShootoutConfiguration{} };

	for( const auto& matchState : {
		CMatchState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, rng },
		CMatchState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		noExtraMatchConfig, homeTeamStrategy, awayTeamStrategy, rng },
		CMatchState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		extraTimeMatchConfig, homeTeamStrategy, awayTeamStrategy, rng },
		CMatchState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		goldenGoalMatchConfig, homeTeamStrategy, awayTeamStrategy, rng },
		CMatchState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		silverGoalMatchConfig, homeTeamStrategy, awayTeamStrategy, rng },
		CMatchState{ CMatch{ team, team, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		penaltyMatchConfig, homeTeamStrategy, awayTeamStrategy, rng },
		} )
	{
		result.push_back( std::string{ futsim::json_traits<CMatchState>::MANDATORY_PERIOD_STATES_KEY } + ": " +
			std::to_string( matchState.GetMandatoryPlayTimeState().GetStates().size() ) );
		if( matchState.GetExtraTimeState() )
			result.push_back( std::string{ futsim::json_traits<CMatchState>::EXTRA_PERIOD_STATES_KEY } + ": " +
				std::to_string( matchState.GetExtraTimeState()->GetStates().size() ) );
		if( matchState.GetPenaltyShootoutState() )
			result.push_back( std::string{ futsim::json_traits<CPenaltyShootoutState>::KEY } + ": " +
				std::to_string( matchState.GetPenaltyShootoutState()->GetPenalties().size() ) );

		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, matchState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TMatchState::ExpectedResults() noexcept
{
	return {};
}
