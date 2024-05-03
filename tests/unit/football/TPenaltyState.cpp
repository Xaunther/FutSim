#include "ITest.h"

#include "football/CPenaltyState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TPenaltyState )

void TPenaltyState::TestExceptions() const
{
}

std::vector<std::string> TPenaltyState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPenaltyState::ExpectedResults() const noexcept
{
	return {};
}
