#include "ITest.h"

#include "football/CTeam.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTeam )

void TTeam::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CTeam{ "", "lut", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The name cannot be empty." );
	CheckException( []() { CTeam{ "Luton Town FC", "l", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The abbreviation must contain 3 characters, not 1." );
	CheckException( []() { CTeam{ "Luton Town FC", "a_c", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The abbreviation can only contain letters from A to Z." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "", {}, 1, 11000, 2000 }; }, "The manager name cannot be empty." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 0, 11000, 2000 }; }, "The support factor must be positive." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, -1000, 2000 }; }, "The mean attendance must be non-negative." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 0 }; }, "The standard deviation of the attendance must be positive." );

	//! Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {}
		} )" ); }, "key 'Name' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": ""
			}
		} )" ); }, "The name cannot be empty." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC"
			}
		} )" ); }, "key 'Abbreviation' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "l"
			}
		} )" ); }, "The abbreviation must contain 3 characters, not 1." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "a_c"
			}
		} )" ); }, "The abbreviation can only contain letters from A to Z." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut"
			}
		} )" ); }, "key 'Manager' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": ""
			}
		} )" ); }, "The manager name cannot be empty." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards"
			}
		} )" ); }, "key 'Support factor' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 0
			}
		} )" ); }, "The support factor must be positive." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"StdDev attendance": 1000
			}
		} )" ); }, "key 'Mean attendance' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"Mean attendance": -1000,
				"StdDev attendance": 1000
			}
		} )" ); }, "The mean attendance must be non-negative." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"Mean attendance": 11000
			}
		} )" ); }, "key 'StdDev attendance' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"Mean attendance": 11000,
				"StdDev attendance": 0
			}
		} )" ); }, "The standard deviation of the attendance must be positive." );
}

std::vector<std::string> TTeam::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> TTeam::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
