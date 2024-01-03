#include "ITest.h"

#include "football/CTeam.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTeam )

void TTeam::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CTeam{ "", "lut", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The name cannot be empty." );
	CheckException( []() { CTeam{ "Luton Town FC", "l", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The abbreviation must contain 3 characters, not 1." );
	CheckException( []() { CTeam{ "Luton Town FC", "a_c", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The abbreviation can only contain letters from A to Z." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "", {}, 1, 11000, 2000 }; }, "The manager name cannot be empty." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 0, 11000, 2000 }; }, "The support factor must be positive." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, -1000, 2000 }; }, "The mean attendance must be non-negative." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 0 }; }, "The standard deviation of the attendance must be positive." );
}

std::vector<std::string> TTeam::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TTeam::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
