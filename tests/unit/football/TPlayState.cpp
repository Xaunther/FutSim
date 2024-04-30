#include "ITest.h"

#include "football/CPlayState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

constexpr bool PRINT_OUTPUT = false;

INITIALIZE_TEST( TPlayState )

void TPlayState::TestExceptions() const
{
}

std::vector<std::string> TPlayState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return PRINT_OUTPUT ? result : std::vector<std::string>{};
}

std::vector<std::string> TPlayState::ExpectedResults() const noexcept
{
	return {};
}
