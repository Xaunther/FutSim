#include "ITest.h"

#include "CEnumDistribution.h"

#include <array>
#include <functional>
#include <iostream>
#include <string>

#include "EnumUtils.h"

using namespace futsim;

INITIALIZE_TEST( TEnumDistribution )

enum class myEnum
{
	A,
	B,
	C
};

FUTSIM_STRING_ENUM( myEnum, {
	{myEnum::A,"A"},
	{myEnum::B,"B"},
	{myEnum::C,"C"},
	} );

void TEnumDistribution::TestExceptions() const
{
}

std::vector<std::string> TEnumDistribution::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	const std::array<double, 3> weightArray{ 1, 1, 1 };
	std::mt19937 rng{ 1234 };

	for( auto enumDistribution : {
		CEnumDistribution<myEnum>{},
		CEnumDistribution<myEnum>{ weightArray.cbegin(), weightArray.cend() },
		CEnumDistribution<myEnum>{ { 1, 2, 3 } },
		CEnumDistribution<myEnum>{ 3, 0.5, 3.5, std::identity{} },
		CEnumDistribution<myEnum>{ CEnumDistribution<myEnum>::param_type{} }
		} )
	{
		result.push_back( "min: " + std::string{ ToString( enumDistribution.min() ) } );
		result.push_back( "max: " + std::string{ ToString( enumDistribution.max() ) } );
		result.push_back( "Probabilities:" );
		for( const auto& probability : enumDistribution.probabilities() )
			result.push_back( std::to_string( probability ) );
		enumDistribution( rng );
		enumDistribution( rng, enumDistribution.param() );
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
