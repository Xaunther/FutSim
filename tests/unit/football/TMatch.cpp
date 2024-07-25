#include "ITest.h"

#include "football/CMatch.h"
#include "football/CTeamStrategy.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TMatch )

void TMatch::TestExceptions() const
{
	// Test member constructor
	CheckException( []()
	{
		CMatch{
			CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
			CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
			CStadium{ "Camp Nou", 98000, 1 }, "" };
	}, "The referee name cannot be empty." );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CMatch>( R"( {
			"Match": {}
		} )" );
	}, "key 'Home team' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CMatch>( R"( {
			"Match": {
				"Home team": {
					"Name": "Luton Town FC",
					"Abbreviation": "lut",
					"Manager": "Rob Edwards",
					"Support factor": 1,
					"Mean attendance": 11000,
					"StdDev attendance": 1000
				}
			}
		} )" );
	}, "key 'Away team' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CMatch>( R"( {
			"Match": {
				"Home team": {
					"Name": "Luton Town FC",
					"Abbreviation": "lut",
					"Manager": "Rob Edwards",
					"Support factor": 1,
					"Mean attendance": 11000,
					"StdDev attendance": 1000
				},
				"Away team": {
					"Name": "Luton Town FC",
					"Abbreviation": "lut",
					"Manager": "Rob Edwards",
					"Support factor": 1,
					"Mean attendance": 11000,
					"StdDev attendance": 1000
				}
			}
		} )" );
	}, "key 'Stadium' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CMatch>( R"( {
			"Match": {
				"Home team": {
					"Name": "Luton Town FC",
					"Abbreviation": "lut",
					"Manager": "Rob Edwards",
					"Support factor": 1,
					"Mean attendance": 11000,
					"StdDev attendance": 1000
				},
				"Away team": {
					"Name": "Luton Town FC",
					"Abbreviation": "lut",
					"Manager": "Rob Edwards",
					"Support factor": 1,
					"Mean attendance": 11000,
					"StdDev attendance": 1000
				},
				"Stadium": {
					"Name": "Camp Nou",
					"Capacity": 98000,
					"Ambient factor": 1
				}
			}
		} )" );
	}, "key 'Referee' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CMatch>( R"( {
			"Match": {
				"Home team": {
					"Name": "Luton Town FC",
					"Abbreviation": "lut",
					"Manager": "Rob Edwards",
					"Support factor": 1,
					"Mean attendance": 11000,
					"StdDev attendance": 1000
				},
				"Away team": {
					"Name": "Luton Town FC",
					"Abbreviation": "lut",
					"Manager": "Rob Edwards",
					"Support factor": 1,
					"Mean attendance": 11000,
					"StdDev attendance": 1000
				},
				"Stadium": {
					"Name": "Camp Nou",
					"Capacity": 98000,
					"Ambient factor": 1
				},
				"Referee": ""
			}
		} )" );
	}, "The referee name cannot be empty." );

	// Test CheckTeamStrategy
	{
		const CTeamStrategy teamStrategy{ "A", CLineup{ "Ter Stegen", {}, {}, {}, {}, {}, {} } };
		const CMatch match{ CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
			CTeam{ "Manchester City FC", "mci", "Pep Guardiola", {}, 1, 50000, 6000 },
			CStadium{ "Camp Nou", 98000, 1 }, "Michael Oliver" };
		CheckException( [ &teamStrategy, &match ]()
		{
			match.CheckTeamStrategy<true>( teamStrategy );
		},
			"Error checking the team strategy against the match definition." );
		CheckException( [ &teamStrategy, &match ]()
		{
			match.CheckTeamStrategy<false>( teamStrategy );
		},
			"Error checking the team strategy against the match definition." );
	}
}

std::vector<std::string> TMatch::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& match : {
		CMatch{ CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
		CTeam{ "Manchester City FC", "mci", "Pep Guardiola", {}, 1, 50000, 6000 },
		CStadium{ "Camp Nou", 98000, 1 }, "Michael Oliver" },
		futsim::ValueFromJSONKeyString<CMatch>( R"( {
			"Match": {
				"Home team": {
					"Name": "Luton Town FC",
					"Abbreviation": "lut",
					"Manager": "Rob Edwards",
					"Support factor": 1,
					"Mean attendance": 11000,
					"StdDev attendance": 2000
				},
				"Away team": {
					"Name": "Manchester City FC",
					"Abbreviation": "mci",
					"Manager": "Pep Guardiola",
					"Support factor": 1,
					"Mean attendance": 50000,
					"StdDev attendance": 6000
				},
				"Stadium": {
					"Name": "Camp Nou",
					"Capacity": 98000,
					"Ambient factor": 1
				},
				"Referee": "Michael Oliver"
			}
		} )" ) } )
	{
		result.push_back( std::string{ CMatch::JSON_HOME_TEAM } + ": " + std::string{ match.GetHomeTeam().GetName() } );
		result.push_back( std::string{ CMatch::JSON_AWAY_TEAM } + ": " + std::string{ match.GetAwayTeam().GetName() } );
		result.push_back( std::string{ futsim::json_traits<CStadium>::KEY } + ": " + std::string{ match.GetStadium().GetName() } );
		result.push_back( std::string{ CMatch::JSON_REFEREE } + ": " + std::string{ match.GetReferee() } );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, match );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}
	return result;
}

std::vector<std::string> TMatch::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Home team: Luton Town FC",
		"Away team: Manchester City FC",
		"Stadium: Camp Nou",
		"Referee: Michael Oliver",
		"{\n"
		"	\"Match\": {\n"
		"		\"Home team\": {\n"
		"			\"Name\": \"Luton Town FC\",\n"
		"			\"Abbreviation\": \"lut\",\n"
		"			\"Manager\": \"Rob Edwards\",\n"
		"			\"Support factor\": 1.0,\n"
		"			\"Mean attendance\": 11000.0,\n"
		"			\"StdDev attendance\": 2000.0\n"
		"		},\n"
		"		\"Away team\": {\n"
		"			\"Name\": \"Manchester City FC\",\n"
		"			\"Abbreviation\": \"mci\",\n"
		"			\"Manager\": \"Pep Guardiola\",\n"
		"			\"Support factor\": 1.0,\n"
		"			\"Mean attendance\": 50000.0,\n"
		"			\"StdDev attendance\": 6000.0\n"
		"		},\n"
		"		\"Stadium\": {\n"
		"			\"Name\": \"Camp Nou\",\n"
		"			\"Capacity\": 98000,\n"
		"			\"Ambient factor\": 1.0\n"
		"		},\n"
		"		\"Referee\": \"Michael Oliver\"\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
