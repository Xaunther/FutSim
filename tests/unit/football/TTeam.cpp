#include "ITest.h"

#include "football/CTeam.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTeam )

void TTeam::TestExceptions() const
{
	// Test member constructor
	CheckException( []() { CTeam{ "", "lut", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The name cannot be empty." );
	CheckException( []() { CTeam{ "Luton Town FC", "l", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The abbreviation must contain 3 characters, not 1." );
	CheckException( []() { CTeam{ "Luton Town FC", "a_c", "Rob Edwards", {}, 1, 11000, 2000 }; }, "The abbreviation can only contain letters from A to Z." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "", {}, 1, 11000, 2000 }; }, "The manager name cannot be empty." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 0, 11000, 2000 }; }, "The support factor must be positive." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, -1000, 2000 }; }, "The mean attendance cannot be negative." );
	CheckException( []() { CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 0 }; }, "The standard deviation of the attendance must be positive." );

	// Test JSON constructor
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
		} )" ); }, "The mean attendance cannot be negative." );
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
	CheckException( []() { futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Players": [
					{
						"Player": {
							"Surnames": "Longstaff",
							"First name": "Matty",
							"Age": 23,
							"Nationality": "GBR",
							"Player skills": {
								"GK skill": 1,
								"DF skill": 1,
								"MF skill": 60,
								"FW skill": 1,  
								"GK experience": 0,
								"MF experience": 0,
								"DF experience": 0,
								"FW experience": 0
							}
						}
					},
					{
						"Player": {
							"First name": "Sean",
							"Surnames": "Longstaff",
							"Age": 26,
							"Nationality": "GBR",
							"Player skills": {
								"GK skill": 1,
								"DF skill": 1,
								"MF skill": 80,
								"FW skill": 1,
								"GK experience": 0,
								"MF experience": 0,
								"DF experience": 0,
								"FW experience": 0
							}
						}
					}
				],
				"Support factor": 1,
				"Mean attendance": 11000,
				"StdDev attendance": 1000
			}
		} )" ); }, "There are two players with the same known name 'Longstaff'." );
}

std::vector<std::string> TTeam::ObtainedResults() const noexcept
{
	std::vector<std::string> result;
	for( const auto& team : {
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {
			CPlayer{ "Lionel", "Messi", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ 1, 1, 1, 99, 0, 0, 0, 0 } },
			CPlayer{ "Ansu", "Fati", "Ansu Fati", 20, futsim::E_NATIONALITY::ESP, CPlayerSkills{ 1, 1, 1, 80, 0, 0, 0, 0 } } },
			1, 11000, 2000 },
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"Mean attendance": 11000,
				"StdDev attendance": 2000
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Players": [
					{
						"Player": {
							"Surnames": "Messi",
							"First name": "Lionel",
							"Age": 35,
							"Nationality": "ARG",
							"Player skills": {
								"GK skill": 1,
								"DF skill": 1,
								"MF skill": 1,
								"FW skill": 99,
								"GK experience": 0,
								"MF experience": 0,
								"DF experience": 0,
								"FW experience": 0
							}
						}
					},
					{
						"Player": {
							"First name": "Ansu",
							"Surnames": "Fati",
							"Known name": "Ansu Fati",
							"Age": 20,
							"Nationality": "ESP",
							"Player skills": {
								"GK skill": 1,
								"DF skill": 1,
								"MF skill": 1,
								"FW skill": 80,
								"GK experience": 0,
								"MF experience": 0,
								"DF experience": 0,
								"FW experience": 0
							}
						}
					}
				],
				"Support factor": 1,
				"Mean attendance": 11000,
				"StdDev attendance": 2000
			}
		} )" ) } )
	{
		result.push_back( std::string{ CTeam::JSON_NAME } + ": " + std::string{ team.GetName() } );
		result.push_back( std::string{ CTeam::JSON_ABBREVIATION } + ": " + std::string{ team.GetAbbreviation() } );
		result.push_back( std::string{ CTeam::JSON_MANAGER } + ": " + std::string{ team.GetManager() } );
		for( const auto& player : team.GetPlayers() )
			result.push_back( std::string{ CPlayer::JSON_KEY } + ": " + std::string{ player.GetKnownName() } );
		result.push_back( std::string{ CTeam::JSON_SUPPORT_FACTOR } + ": " + std::to_string( team.GetSupportFactor() ) );
		result.push_back( std::string{ CTeam::JSON_MEAN_ATTENDANCE } + ": " + std::to_string( team.GetAttendanceDistributionParameters().mean() ) );
		result.push_back( std::string{ CTeam::JSON_STD_DEV_ATTENDANCE } + ": " + std::to_string( team.GetAttendanceDistributionParameters().stddev() ) );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, team );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TTeam::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Name: Luton Town FC",
		"Abbreviation: lut",
		"Manager: Rob Edwards",
		"Support factor: 1.000000",
		"Mean attendance: 11000.000000",
		"StdDev attendance: 2000.000000",
		"{\n"
		"	\"Team\": {\n"
		"		\"Name\": \"Luton Town FC\",\n"
		"		\"Abbreviation\": \"lut\",\n"
		"		\"Manager\": \"Rob Edwards\",\n"
		"		\"Support factor\": 1.0,\n"
		"		\"Mean attendance\": 11000.0,\n"
		"		\"StdDev attendance\": 2000.0\n"
		"	}\n"
		"}",
		"Name: Luton Town FC",
		"Abbreviation: lut",
		"Manager: Rob Edwards",
		"Player: Messi",
		"Player: Ansu Fati",
		"Support factor: 1.000000",
		"Mean attendance: 11000.000000",
		"StdDev attendance: 2000.000000",
		"{\n"
		"	\"Team\": {\n"
		"		\"Name\": \"Luton Town FC\",\n"
		"		\"Abbreviation\": \"lut\",\n"
		"		\"Manager\": \"Rob Edwards\",\n"
		"		\"Players\": [\n"
		"			{\n"
		"				\"Player\": {\n"
		"					\"First name\": \"Lionel\",\n"
		"					\"Surnames\": \"Messi\",\n"
		"					\"Age\": 35,\n"
		"					\"Nationality\": \"ARG\",\n"
		"					\"Player skills\": {\n"
		"						\"GK skill\": 1,\n"
		"						\"DF skill\": 1,\n"
		"						\"MF skill\": 1,\n"
		"						\"FW skill\": 99,\n"
		"						\"GK experience\": 0,\n"
		"						\"DF experience\": 0,\n"
		"						\"MF experience\": 0,\n"
		"						\"FW experience\": 0\n"
		"					}\n"
		"				}\n"
		"			},\n"
		"			{\n"
		"				\"Player\": {\n"
		"					\"First name\": \"Ansu\",\n"
		"					\"Surnames\": \"Fati\",\n"
		"					\"Known name\": \"Ansu Fati\",\n"
		"					\"Age\": 20,\n"
		"					\"Nationality\": \"ESP\",\n"
		"					\"Player skills\": {\n"
		"						\"GK skill\": 1,\n"
		"						\"DF skill\": 1,\n"
		"						\"MF skill\": 1,\n"
		"						\"FW skill\": 80,\n"
		"						\"GK experience\": 0,\n"
		"						\"DF experience\": 0,\n"
		"						\"MF experience\": 0,\n"
		"						\"FW experience\": 0\n"
		"					}\n"
		"				}\n"
		"			}\n"
		"		],\n"
		"		\"Support factor\": 1.0,\n"
		"		\"Mean attendance\": 11000.0,\n"
		"		\"StdDev attendance\": 2000.0\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
