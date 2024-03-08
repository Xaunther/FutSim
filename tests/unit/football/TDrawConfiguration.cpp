#include "ITest.h"

#include "football/CDrawConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TDrawConfiguration )

void TDrawConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{ 10 }, CChancesDrawConfiguration{ 30, 1, 1, 1, 2, 20 } }; },
		"The probability to get a set piece chance given a foul cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 100 } }; },
		"The probability to get a chance after keeping possession or launching a counter attack cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 15 } }; },
		"The corner probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 4, 11 } }; },
		"The 1 on 1 vs GK probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 4, 2, 11 } }; },
		"The 1 on 1 vs DF probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 4, 2, 1, 11 } }; },
		"The near shot probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 10, 4, 2, 1, 3 } }; },
		"The far shot probability cannot be negative." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 20, 10, 1, 1, 1, 5, 0.01 }, CGoalDrawConfiguration{ 4, 0.5 } }; },
		"The penalty goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 20, 10, 1, 1, 1, 5, 1, 0.01 }, CGoalDrawConfiguration{ 4, 0.05, 0.5 } }; },
		"The direct free kick goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 20, 10, 1, 1, 1, 0.1, 0.01, 0.01 }, CGoalDrawConfiguration{ 4, 0, 0, 2 } }; },
		"The indirect free kick goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{}, CGoalDrawConfiguration{ 50, 0, 0, 0, 25 } }; },
		"The corner goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{}, CGoalDrawConfiguration{ 50, 0, 0, 0, 0, 30 } }; },
		"The far shot goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{ 20, 10, 1, 1, 1, 5, 1, 1 }, CGoalDrawConfiguration{ 4, 0.05, 0.05, 1 } }; },
		"The near shot goal probability cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{ 0.9 }, CFoulDrawConfiguration{ 10 } }; },
		"The joint probability of keeping possession or receiving a foul cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{}, CGoalDrawConfiguration{ 2.73, 0.25 } }; },
		"The joint probability of scoring or getting an extra corner from a penalty cannot be greater than 1." );
	CheckException( []() { CDrawConfiguration{ CPossessionDrawConfiguration{}, CFoulDrawConfiguration{}, CChancesDrawConfiguration{}, CGoalDrawConfiguration{ 2.73, 0, 0.6 } }; },
		"The joint probability of scoring or getting an extra corner from a direct free kick cannot be greater than 1." );
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
