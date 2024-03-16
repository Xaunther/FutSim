#include "ITest.h"

#include "CEnumDistribution.h"

#include <array>
#include <functional>
#include <iostream>
#include <string>

using namespace futsim;

INITIALIZE_TEST( TEnumDistribution )

enum class myEnum
{
	A,
	B,
	C
};

std::string ToString( const myEnum& aEnum ) noexcept
{
	switch( aEnum )
	{
	case myEnum::A: return "A";
	case myEnum::B: return "B";
	default: return "C";
	}
}

void TEnumDistribution::TestExceptions() const
{
}

std::vector<std::string> TEnumDistribution::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	const std::array<double, 3> weightArray{ 1, 1, 1 };

	for( const auto& enumDistribution : {
		CEnumDistribution<myEnum>{},
		CEnumDistribution<myEnum>{ weightArray.cbegin(), weightArray.cend() },
		CEnumDistribution<myEnum>{ { 1, 2, 3 } },
		CEnumDistribution<myEnum>{ 3, 0.5, 3.5, std::identity{} },
		CEnumDistribution<myEnum>{ CEnumDistribution<myEnum>::param_type{} }
		} )
	{
		result.push_back( "min: " + ToString( enumDistribution.min() ) );
		result.push_back( "max: " + ToString( enumDistribution.max() ) );
		result.push_back( "Probabilities:" );
		for( const auto& probability : enumDistribution.probabilities() )
			result.push_back( std::to_string( probability ) );

	}
	return result;
}

std::vector<std::string> TEnumDistribution::ExpectedResults() const noexcept
{
	return std::vector<std::string>{
		"min: A",
			"max: A",
			"Probabilities:",
			"1.000000",
			"min: A",
			"max: C",
			"Probabilities:",
			"0.333333",
			"0.333333",
			"0.333333",
			"min: A",
			"max: C",
			"Probabilities:",
			"0.166667",
			"0.333333",
			"0.500000",
			"min: A",
			"max: C",
			"Probabilities:",
			"0.166667",
			"0.333333",
			"0.500000",
			"min: A",
			"max: A",
			"Probabilities:",
			"1.000000",
	};
}
