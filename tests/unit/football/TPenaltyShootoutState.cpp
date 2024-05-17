#include "ITest.h"

#include "football/CPenaltyShootoutState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TPenaltyShootoutState )

void TPenaltyShootoutState::TestExceptions() const
{
}

std::vector<std::string> TPenaltyShootoutState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPenaltyShootoutState::ExpectedResults() const noexcept
{
	return {};
}
