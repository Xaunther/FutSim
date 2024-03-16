#include "ITest.h"

#include "CEnumDistribution.h"

#include <iostream>

using namespace futsim;

INITIALIZE_TEST( TEnumDistribution )

void TEnumDistribution::TestExceptions() const
{
}

std::vector<std::string> TEnumDistribution::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TEnumDistribution::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
