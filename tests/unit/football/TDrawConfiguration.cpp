#include "ITest.h"

#include "football/CDrawConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TDrawConfiguration )

void TDrawConfiguration::TestExceptions() const
{
}

std::vector<std::string> TDrawConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TDrawConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
