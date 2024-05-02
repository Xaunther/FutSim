#include "ITest.h"

#include "football/CPeriodState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TPeriodState )

void TPeriodState::TestExceptions() const
{
}

std::vector<std::string> TPeriodState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPeriodState::ExpectedResults() const noexcept
{
	return {};
}
