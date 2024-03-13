#include "ITest.h"

#include "football/CTacticsConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTacticsConfiguration )

void TTacticsConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CTacticsConfiguration{ CTacticsConfigurationTypes::tactic_configurations{} }; },
		"The tactic configurations cannot be empty" );
	CheckException( []() { CTacticsConfiguration{ { { "A", CTacticConfiguration{ 0, 0, { "A" } } } } }; },
		"The tactics 'A' and 'A' are favourable against each other, which is forbidden." );
	CheckException( []() { CTacticsConfiguration{ { { "A", CTacticConfiguration{ 0, 0, { "E" } } },
		{ "E", CTacticConfiguration{ 0, 0, { "A" } } } } }; },
		"The tactics 'A' and 'E' are favourable against each other, which is forbidden." );
	CheckException( []() { CTacticsConfiguration{ CTacticsConfiguration::DEFAULT_TACTIC_CONFIGURATIONS, -0.5 }; },
		"The favourable tactic skill bonus cannot be negative" );
}

std::vector<std::string> TTacticsConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TTacticsConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
