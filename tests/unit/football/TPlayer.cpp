#include "ITest.h"

#include "football/CPlayer.h"

#include <iostream>

using namespace futsim::football;

INITIALIZE_TEST( TPlayer )

void TPlayer::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CPlayer{ "", "Messi", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ 1, 1, 1, 1, 1, 1, 1, 1 } }; },
		"The name cannot be empty." );
	CheckException( []() { CPlayer{ "Lionel", "", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ 1, 1, 1, 1, 1, 1, 1, 1 } }; },
		"The surnames cannot be empty." );
}

std::vector<std::string> TPlayer::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TPlayer::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
