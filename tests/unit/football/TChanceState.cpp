#include "ATest.h"

#include "football/CChanceState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TChanceState )

namespace
{

template <E_PLAYER_SKILL tPlayerSkill>
void PushActor( auto& aResult, const CChanceState& aChanceState )
{
	if( const auto& actor = aChanceState.GetActor<tPlayerSkill>() )
		aResult.push_back( std::string{ futsim::json_traits<CChanceState>::ACTOR<tPlayerSkill> } + ": " + *actor );
};

} // anonymous namespace

void TChanceState::TestExceptions()
{
}

std::vector<std::string> TChanceState::ObtainedResults() noexcept
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

	for( const auto& chanceState : {
		CChanceState{ std::true_type{}, CMatch{ team, team, CStadium{ "The New Lawn", 5147, 100 }, "Michael Oliver" },
		CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, true, rng },
		CChanceState{ std::false_type{}, CMatch{ team, team, CStadium{ "The New Lawn", 5147, 100 }, "Michael Oliver" },
		CMatchConfiguration{}, homeTeamStrategy, awayTeamStrategy, false, rng },
		} )
	{
		result.push_back( std::string{ futsim::json_traits<CChanceState>::CHANCE_TYPE_KEY } + ": "
			+ std::string{ std::visit( []( auto&& aChanceType )
		{
			return ToString( aChanceType );
		}, chanceState.GetChanceType() ) } );
		result.push_back( std::string{ futsim::json_traits<CChanceState>::OUTCOME_KEY } + ": " + std::string{ ToString( chanceState.GetChanceOutcome() ) } );
		PushActor< E_PLAYER_SKILL::St >( result, chanceState );
		PushActor< E_PLAYER_SKILL::Tk >( result, chanceState );
		PushActor< E_PLAYER_SKILL::Ps >( result, chanceState );
		PushActor< E_PLAYER_SKILL::Sh >( result, chanceState );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, chanceState );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TChanceState::ExpectedResults() noexcept
{
	return {};
}
