#include "ITest.h"

#include "football/CPenaltyShootoutState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;
namespace
{

const CTeam TEAM{
	"Luton Town FC", "lut", "Rob Edwards", {
		CPlayer{ "Thomas", "Kaminski", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 70, 1, 1, 1 }, {} } },
		CPlayer{ "Dan", "Potts", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 70, 1, 5 }, {} } },
		CPlayer{ "Tom", "Lockyer", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 80, 1, 6 }, {} } },
		CPlayer{ "Issa", "Kaboré", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 60, 1, 7 }, {} } },
		CPlayer{ "Amari'i", "Bell", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 60, 1, 8 }, {} } },
		CPlayer{ "Ross", "Barkley", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 80, 9 }, {} } },
		CPlayer{ "Marvelous", "Nakamba", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 75, 10 }, {} } },
		CPlayer{ "Pelly Ruddock", "Mpanzu", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 60, 11 }, {} } },
		CPlayer{ "Jordan", "Clark", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 70, 12 }, {} } },
		CPlayer{ "Carlton", "Morris", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 1, 75 }, {} } },
		CPlayer{ "Elijah", "Adebayo", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 1, 75 }, {} } },
}, 1.2, 11000, 2000
};

const CTeamStrategy HOME_STRATEGY{ "A", CLineup{ "Kaminski",
types::CLineup::names{ "Potts", "Lockyer", "Kaboré", "Bell" },
	{}, types::CLineup::names{ "Barkley", "Nakamba", "Mpanzu", "Clark" }, {},
	types::CLineup::names{ "Morris", "Adebayo" }, {} } };

const CTeamStrategy AWAY_STRATEGY{ "A", CLineup{ "Kaminski",
types::CLineup::names{ "Lockyer", "Kaboré", "Bell" },
	{}, types::CLineup::names{ "Barkley", "Nakamba", "Mpanzu", "Clark" }, {},
	types::CLineup::names{ "Morris", "Adebayo" }, {} } };

} // anonymous namespace

INITIALIZE_TEST( TPenaltyShootoutState )

void TPenaltyShootoutState::TestExceptions() const
{
	std::mt19937 rng{ 1234 };
	// Test constructor
	CheckException( [ & ]()
	{
		CPenaltyShootoutState{ CMatch{ TEAM, TEAM, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		CMatchConfiguration{}, HOME_STRATEGY, AWAY_STRATEGY, true, rng };
	},
		"The match configuration must include a penalty shootout configuration." );
}

std::vector<std::string> TPenaltyShootoutState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	std::mt19937 rng{ 1234 };

	for( const auto& penaltyShootoutState : {
		CPenaltyShootoutState{ CMatch{ TEAM, TEAM, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		CMatchConfiguration{ CPlayTime{}, CLineupConfiguration{}, true, CTacticsConfiguration{},
		CTieCondition{ 0 }, {}, CPenaltyShootoutConfiguration{ E_PENALTY_SEQUENCE::AB, 5 } },
		HOME_STRATEGY, AWAY_STRATEGY, true, rng },
		CPenaltyShootoutState{ CMatch{ TEAM, TEAM, CStadium{ "The New Lawn", 5147, 1 }, "Michael Oliver" },
		CMatchConfiguration{ CPlayTime{}, CLineupConfiguration{}, true, CTacticsConfiguration{},
		CTieCondition{ 0 }, {}, CPenaltyShootoutConfiguration{ E_PENALTY_SEQUENCE::ABBA, 15 } },
		HOME_STRATEGY, AWAY_STRATEGY, false, rng },
		} )
	{
		result.push_back( std::string{ futsim::json_traits<CPenaltyShootoutState>::PENALTIES } + ": "
			+ std::to_string( penaltyShootoutState.GetPenalties().size() ) );

		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, penaltyShootoutState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPenaltyShootoutState::ExpectedResults() const noexcept
{
	return {};
}
