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
	for( const auto& chancesDrawConfiguration : {
		CChancesDrawConfiguration{},
		CChancesDrawConfiguration{ 20, 5, 2, 2, 3, 4, 1, 1 },
		futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {}
		} )" ),
		futsim::ValueFromJSONKeyString<CChancesDrawConfiguration>( R"( {
			"Chances draw configuration": {
				"Average chances": 20.0,
				"Average corner kicks": 5.0,
				"Average 1 on 1 vs GK chances": 2.0,
				"Average 1 on 1 vs DF chances": 2.0,
				"Average near shots": 3.0,
				"Average set pieces": 4.0,
				"Average penalties": 1.0,
				"Average direct free kicks": 1.0
			}
		} )" ) } )
	{
		result.push_back( std::string{ CChancesDrawConfiguration::JSON_AVERAGE_CHANCES } + ": " + std::to_string( chancesDrawConfiguration.GetAverageChances() ) );
		result.push_back( std::string{ CChancesDrawConfiguration::JSON_AVERAGE_CORNER_KICKS } + ": " + std::to_string( chancesDrawConfiguration.GetAverageCornerKicks() ) );
		result.push_back( std::string{ CChancesDrawConfiguration::JSON_AVERAGE_1VS1_GKS } + ": " + std::to_string( chancesDrawConfiguration.GetAverage1vs1GKs() ) );
		result.push_back( std::string{ CChancesDrawConfiguration::JSON_AVERAGE_1VS1_DFS } + ": " + std::to_string( chancesDrawConfiguration.GetAverage1vs1DFs() ) );
		result.push_back( std::string{ CChancesDrawConfiguration::JSON_AVERAGE_NEAR_SHOTS } + ": " + std::to_string( chancesDrawConfiguration.GetAverageNearShots() ) );
		result.push_back( std::string{ CChancesDrawConfiguration::JSON_AVERAGE_SET_PIECES } + ": " + std::to_string( chancesDrawConfiguration.GetAverageSetPieces() ) );
		result.push_back( std::string{ CChancesDrawConfiguration::JSON_AVERAGE_PENALTIES } + ": " + std::to_string( chancesDrawConfiguration.GetAveragePenalties() ) );
		result.push_back( std::string{ CChancesDrawConfiguration::JSON_AVERAGE_DIRECT_FREE_KICKS } + ": " + std::to_string( chancesDrawConfiguration.GetAverageDirectFreeKicks() ) );
		for( const auto& probability : chancesDrawConfiguration.CreateSetPieceTypeDistribution().probabilities() )
			result.push_back( std::to_string( probability ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, chancesDrawConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TChancesDrawConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Average chances: 25.286842",
		"Average corner kicks: 10.078947",
		"Average 1 on 1 vs GK chances: 2.000000",
		"Average 1 on 1 vs DF chances: 2.850000",
		"Average near shots: 3.000000",
		"Average set pieces: 4.065789",
		"Average penalties: 0.273684",
		"Average direct free kicks: 0.792105",
		"0.067314",
		"0.194822",
		"0.737864",
		"{\n"
		"	\"Chances draw configuration\": {\n"
		"		\"Average chances\": 25.28684210526316,\n"
		"		\"Average corner kicks\": 10.078947368421053,\n"
		"		\"Average 1 on 1 vs GK chances\": 2.0,\n"
		"		\"Average 1 on 1 vs DF chances\": 2.85,\n"
		"		\"Average near shots\": 3.0,\n"
		"		\"Average set pieces\": 4.065789473684211,\n"
		"		\"Average penalties\": 0.2736842105263158,\n"
		"		\"Average direct free kicks\": 0.7921052631578948\n"
		"	}\n"
		"}",
		"Average chances: 20.000000",
		"Average corner kicks: 5.000000",
		"Average 1 on 1 vs GK chances: 2.000000",
		"Average 1 on 1 vs DF chances: 2.000000",
		"Average near shots: 3.000000",
		"Average set pieces: 4.000000",
		"Average penalties: 1.000000",
		"Average direct free kicks: 1.000000",
		"0.250000",
		"0.250000",
		"0.500000",
		"{\n"
		"	\"Chances draw configuration\": {\n"
		"		\"Average chances\": 20.0,\n"
		"		\"Average corner kicks\": 5.0,\n"
		"		\"Average 1 on 1 vs GK chances\": 2.0,\n"
		"		\"Average 1 on 1 vs DF chances\": 2.0,\n"
		"		\"Average near shots\": 3.0,\n"
		"		\"Average set pieces\": 4.0,\n"
		"		\"Average penalties\": 1.0,\n"
		"		\"Average direct free kicks\": 1.0\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
