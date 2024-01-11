#include "ITest.h"

#include "football/CMatch.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TMatch )

void TMatch::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CMatch{
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
		CStadium{ "Camp Nou", 98000, 1 }, "" }; }, "The referee name cannot be empty." );

	//! Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatch>( R"( {
			"Match": {}
		} )" ); }, "key 'Home team' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatch>( R"( {
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
		} )" ); }, "key 'Away team' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatch>( R"( {
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
		} )" ); }, "key 'Stadium' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatch>( R"( {
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
		} )" ); }, "key 'Referee' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CMatch>( R"( {
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
		} )" ); }, "The referee name cannot be empty." );
}

std::vector<std::string> TMatch::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TMatch::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
