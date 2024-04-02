#include "ITest.h"

#include "football/CChanceState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TChanceState )

void TChanceState::TestExceptions() const
{
}

std::vector<std::string> TChanceState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TChanceState::ExpectedResults() const noexcept
{
	return std::vector<std::string>{};
}
