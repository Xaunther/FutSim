#include "ATest.h"

#include "football/CFoulDrawConfiguration.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TFoulDrawConfiguration )

void TFoulDrawConfiguration::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CFoulDrawConfiguration{ -1 };
	}, "The average number of fouls cannot be negative." );
	CheckException( []()
	{
		CFoulDrawConfiguration{ futsim::default_traits<CFoulDrawConfiguration>::AVERAGE_FOULS, -1 };
	},
		"The average number of yellow cards cannot be negative." );
	CheckException( []()
	{
		CFoulDrawConfiguration{ futsim::default_traits<CFoulDrawConfiguration>::AVERAGE_FOULS, futsim::default_traits<CFoulDrawConfiguration>::AVERAGE_YELLOW_CARDS, -1 };
	},
		"The average number of red cards cannot be negative." );
	CheckException( []()
	{
		CFoulDrawConfiguration{ 0 };
	},
		"The average number of fouls minus the average number of yellow and red cards cannot be negative." );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average fouls": -1
			}
		} )" );
	}, "The average number of fouls cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average yellow cards": -1
			}
		} )" );
	}, "The average number of yellow cards cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average red cards": -1
			}
		} )" );
	}, "The average number of red cards cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average fouls": 0
			}
		} )" );
	}, "The average number of fouls minus the average number of yellow and red cards cannot be negative." );

	// Test DrawFoulCommitter method
	{
		std::mt19937 rng{ 1234 };
		const CLineup lineup{ "Kelleher", {}, {}, {}, {}, {}, {} };
		if( auto drawnPlayer = CFoulDrawConfiguration{}.DrawFoulCommitter( lineup, rng ); drawnPlayer != "Kelleher" )
			throw std::invalid_argument{ "Kelleher should have been drawn instead of " + std::string{ drawnPlayer } + "." };
	}
}

std::vector<std::string> TFoulDrawConfiguration::ObtainedResults() noexcept
{
	std::vector<std::string> result;
	for( const auto& foulDrawConfiguration : {
		CFoulDrawConfiguration{},
		CFoulDrawConfiguration{ 10, 4, 1 },
		futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {}
		} )" ),
		futsim::ValueFromJSONKeyString<CFoulDrawConfiguration>( R"( {
			"Foul draw configuration": {
				"Average fouls": 10,
				"Average yellow cards": 4,
				"Average red cards": 1
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CFoulDrawConfiguration>::AVERAGE_FOULS_KEY } + ": " + std::to_string( foulDrawConfiguration.GetAverageFouls() ) );
		result.push_back( std::string{ futsim::json_traits<CFoulDrawConfiguration>::AVERAGE_YELLOW_CARDS_KEY } + ": " + std::to_string( foulDrawConfiguration.GetAverageYellowCards() ) );
		result.push_back( std::string{ futsim::json_traits<CFoulDrawConfiguration>::AVERAGE_RED_CARDS_KEY } + ": " + std::to_string( foulDrawConfiguration.GetAverageRedCards() ) );
		result.push_back( "Foul probability: " + std::to_string( foulDrawConfiguration.GetFoulProbability() ) );
		for( const auto& probability : foulDrawConfiguration.CreateFoulDistribution().probabilities() )
			result.push_back( std::to_string( probability ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, foulDrawConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TFoulDrawConfiguration::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Average fouls: 21.565789",
		"Average yellow cards: 3.618421",
		"Average red cards: 0.081579",
		"Foul probability: 0.239620",
		"0.167785",
		"0.003783",
		"0.828432",
		"{\n"
		"	\"Foul draw configuration\": {\n"
		"		\"Average fouls\": 21.56578947368421,\n"
		"		\"Average yellow cards\": 3.6184210526315788,\n"
		"		\"Average red cards\": 0.08157894736842106\n"
		"	}\n"
		"}",
		"Average fouls: 10.000000",
		"Average yellow cards: 4.000000",
		"Average red cards: 1.000000",
		"Foul probability: 0.111111",
		"0.400000",
		"0.100000",
		"0.500000",
		"{\n"
		"	\"Foul draw configuration\": {\n"
		"		\"Average fouls\": 10.0,\n"
		"		\"Average yellow cards\": 4.0,\n"
		"		\"Average red cards\": 1.0\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
