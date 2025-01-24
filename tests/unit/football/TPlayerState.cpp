#include "ATest.h"

#include "football/CPlayerState.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayerState )

void TPlayerState::TestExceptions() const
{
}

std::vector<std::string> TPlayerState::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TPlayerState::ExpectedResults() const noexcept
{
	return std::vector<std::string>{};
}
