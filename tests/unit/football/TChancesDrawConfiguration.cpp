#include "ITest.h"

#include "football/CChancesDrawConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TChancesDrawConfiguration )

void TChancesDrawConfiguration::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CChancesDrawConfiguration{ -1 }; },
		"The average number of chances cannot be negative." );
	CheckException( []() { CChancesDrawConfiguration{ CChancesDrawConfiguration::DEFAULT_AVERAGE_CHANCES, -1 }; },
		"The average number of corner kicks cannot be negative." );
	CheckException( []() { CChancesDrawConfiguration{ CChancesDrawConfiguration::DEFAULT_AVERAGE_CHANCES, CChancesDrawConfiguration::DEFAULT_AVERAGE_CORNER_KICKS, -1 }; },
		"The average number of 1 on 1 vs GK chances cannot be negative." );
	CheckException( []() { CChancesDrawConfiguration{ CChancesDrawConfiguration::DEFAULT_AVERAGE_CHANCES, CChancesDrawConfiguration::DEFAULT_AVERAGE_CORNER_KICKS,
		CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_GKS, -1 }; },
		"The average number of 1 on 1 vs DF chances cannot be negative." );
	CheckException( []() { CChancesDrawConfiguration{ CChancesDrawConfiguration::DEFAULT_AVERAGE_CHANCES, CChancesDrawConfiguration::DEFAULT_AVERAGE_CORNER_KICKS,
		CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_GKS, CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_DFS, -1 }; },
		"The average number of near shots cannot be negative." );
	CheckException( []() { CChancesDrawConfiguration{ CChancesDrawConfiguration::DEFAULT_AVERAGE_CHANCES, CChancesDrawConfiguration::DEFAULT_AVERAGE_CORNER_KICKS,
		CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_GKS, CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_DFS, CChancesDrawConfiguration::DEFAULT_AVERAGE_NEAR_SHOTS, -1 }; },
		"The average number of set pieces cannot be negative." );
	CheckException( []() { CChancesDrawConfiguration{ CChancesDrawConfiguration::DEFAULT_AVERAGE_CHANCES, CChancesDrawConfiguration::DEFAULT_AVERAGE_CORNER_KICKS,
		CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_GKS, CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_DFS, CChancesDrawConfiguration::DEFAULT_AVERAGE_NEAR_SHOTS,
		CChancesDrawConfiguration::DEFAULT_AVERAGE_SET_PIECES, -1 }; },
		"The average number of penalties cannot be negative." );
	CheckException( []() { CChancesDrawConfiguration{ CChancesDrawConfiguration::DEFAULT_AVERAGE_CHANCES, CChancesDrawConfiguration::DEFAULT_AVERAGE_CORNER_KICKS,
		CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_GKS, CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_DFS, CChancesDrawConfiguration::DEFAULT_AVERAGE_NEAR_SHOTS,
		CChancesDrawConfiguration::DEFAULT_AVERAGE_SET_PIECES, CChancesDrawConfiguration::DEFAULT_AVERAGE_PENALTIES, -1 }; },
		"The average number of direct free kicks cannot be negative." );
	CheckException( []() { CChancesDrawConfiguration{ CChancesDrawConfiguration::DEFAULT_AVERAGE_CHANCES, CChancesDrawConfiguration::DEFAULT_AVERAGE_CORNER_KICKS,
		CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_GKS, CChancesDrawConfiguration::DEFAULT_AVERAGE_1VS1_DFS, CChancesDrawConfiguration::DEFAULT_AVERAGE_NEAR_SHOTS, 0 }; },
		"The average number of set pieces minus the average number of penalties and direct free kicks cannot be negative." );

	// Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average chances": -1
			}
		} )" ); }, "The average number of chances cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average corner kicks": -1
			}
		} )" ); }, "The average number of corner kicks cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average 1 on 1 vs GK chances": -1
			}
		} )" ); }, "The average number of 1 on 1 vs GK chances cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average 1 on 1 vs DF chances": -1
			}
		} )" ); }, "The average number of 1 on 1 vs DF chances cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average near shots": -1
			}
		} )" ); }, "The average number of near shots cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average set pieces": -1
			}
		} )" ); }, "The average number of set pieces cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average penalties": -1
			}
		} )" ); }, "The average number of penalties cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average direct free kicks": -1
			}
		} )" ); }, "The average number of direct free kicks cannot be negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average set pieces": 0
			}
		} )" ); }, "The average number of set pieces minus the average number of penalties and direct free kicks cannot be negative." );
}

std::vector<std::string> TChancesDrawConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TChancesDrawConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
