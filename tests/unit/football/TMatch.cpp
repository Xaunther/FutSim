#include "ITest.h"

#include "football/CMatch.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TMatch )

void TMatch::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CMatch{
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
		CStadium{ "Camp Nou", 98000, 1 }, "" }; }, "The referee name cannot be empty." );
}

std::vector<std::string> TMatch::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TMatch::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
