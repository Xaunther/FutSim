#include "ATest.h"

#include "football/CTeam.h"

#include "football/CLineup.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TTeam )

void TTeam::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CTeam{ "", "lut", "Rob Edwards", {}, 1, 11000, 2000 };
	}, "The name cannot be empty." );
	CheckException( []()
	{
		CTeam{ "Luton Town FC", "l", "Rob Edwards", {}, 1, 11000, 2000 };
	}, "The abbreviation must contain 3 characters, not 1." );
	CheckException( []()
	{
		CTeam{ "Luton Town FC", "a_c", "Rob Edwards", {}, 1, 11000, 2000 };
	}, "The abbreviation can only contain letters from A to Z." );
	CheckException( []()
	{
		CTeam{ "Luton Town FC", "lut", "", {}, 1, 11000, 2000 };
	}, "The manager name cannot be empty." );
	CheckException( []()
	{
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 0, 11000, 2000 };
	}, "The support factor must be positive." );
	CheckException( []()
	{
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, -1000, 2000 };
	}, "The mean attendance cannot be negative." );
	CheckException( []()
	{
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 0 };
	}, "The standard deviation of the attendance must be positive." );
	CheckException( []()
	{
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {
			CPlayer{ "Matty", "Longstaff", "", 23, futsim::E_NATIONALITY::GBR, CPlayerSkills{ { 1, 1, 60, 1 }, { 0, 0, 0, 0 } } },
			CPlayer{ "Sean", "Longstaff", "", 26, futsim::E_NATIONALITY::GBR, CPlayerSkills{ { 1, 1, 80, 1 }, { 0, 0, 0, 0 } } },
		}, 1, 11000, 0 };
	}, "There are two players with the same known name 'Longstaff'." );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {}
		} )" );
	}, "key 'Name' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": ""
			}
		} )" );
	}, "The name cannot be empty." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC"
			}
		} )" );
	}, "key 'Abbreviation' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "l"
			}
		} )" );
	}, "The abbreviation must contain 3 characters, not 1." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "a_c"
			}
		} )" );
	}, "The abbreviation can only contain letters from A to Z." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut"
			}
		} )" );
	}, "key 'Manager' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": ""
			}
		} )" );
	}, "The manager name cannot be empty." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards"
			}
		} )" );
	}, "key 'Support factor' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 0
			}
		} )" );
	}, "The support factor must be positive." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"StdDev attendance": 1000
			}
		} )" );
	}, "key 'Mean attendance' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"Mean attendance": -1000,
				"StdDev attendance": 1000
			}
		} )" );
	}, "The mean attendance cannot be negative." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"Mean attendance": 11000
			}
		} )" );
	}, "key 'StdDev attendance' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Support factor": 1,
				"Mean attendance": 11000,
				"StdDev attendance": 0
			}
		} )" );
	}, "The standard deviation of the attendance must be positive." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CTeam>( R"( {
			"Team": {
				"Name": "Luton Town FC",
				"Abbreviation": "lut",
				"Manager": "Rob Edwards",
				"Players": [
					{
						"Surnames": "Longstaff",
						"First name": "Matty",
						"Age": 23,
						"Nationality": "GBR",
						"Player skills": {
							"St skill": 1,
							"Tk skill": 1,
							"Ps skill": 60,
							"Sh skill": 1,  
							"St experience": 0,
							"Ps experience": 0,
							"Tk experience": 0,
							"Sh experience": 0
						}
					},
					{
						"First name": "Sean",
						"Surnames": "Longstaff",
						"Age": 26,
						"Nationality": "GBR",
						"Player skills": {
							"St skill": 1,
							"Tk skill": 1,
							"Ps skill": 80,
							"Sh skill": 1,
							"St experience": 0,
							"Ps experience": 0,
							"Tk experience": 0,
							"Sh experience": 0
						}
					}
				],
				"Support factor": 1,
				"Mean attendance": 11000,
				"StdDev attendance": 1000
			}
		} )" );
	}, "There are two players with the same known name 'Longstaff'." );

	// GetPlayer exception
	CheckException( []()
	{
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {
			CPlayer{ "Matty", "Longstaff", "", 23, futsim::E_NATIONALITY::GBR, CPlayerSkills{ { 1, 1, 60, 1 }, { 0, 0, 0, 0 } } },
		}, 1, 11000, 1000 }.GetPlayer( "Messi" );
	}, "Messi is not in Luton Town FC's list of players." );

	// Test CheckLineup
	{
		const CLineup lineup{ "Ter Stegen", {}, {}, {}, {}, {}, {} };
		CheckException( [ &lineup ]()
		{
			CTeam{ "Luton Town FC", "lut", "Rob Edwards", {
				CPlayer{ "Matty", "Longstaff", "", 23, futsim::E_NATIONALITY::GBR, CPlayerSkills{ { 1, 1, 60, 1 }, { 0, 0, 0, 0 } } },
			}, 1, 11000, 1000 }.CheckLineup( lineup );
		}, "Error checking the lineup against the team." );
	}
}

std::vector<std::string> TTeam::ObtainedResults() noexcept
{
	std::vector<std::string> result;
	for( const auto& team : {
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {}, 1, 11000, 2000 },
		CTeam{ "Luton Town FC", "lut", "Rob Edwards", {
			CPlayer{ "Lionel", "Messi", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 1, 99 }, { 0, 0, 0, 0 } } },
			CPlayer{ "Ansu", "Fati", "Ansu Fati", 20, futsim::E_NATIONALITY::ESP, CPlayerSkills{ { 1, 1, 1, 80 }, { 0, 0, 0, 0 } } } },
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
						"Surnames": "Messi",
						"First name": "Lionel",
						"Age": 35,
						"Nationality": "ARG",
						"Player skills": {
							"St skill": 1,
							"Tk skill": 1,
							"Ps skill": 1,
							"Sh skill": 99,
							"St experience": 0,
							"Ps experience": 0,
							"Tk experience": 0,
							"Sh experience": 0
						}
					},
					{
						"First name": "Ansu",
						"Surnames": "Fati",
						"Known name": "Ansu Fati",
						"Age": 20,
						"Nationality": "ESP",
						"Player skills": {
							"St skill": 1,
							"Tk skill": 1,
							"Ps skill": 1,
							"Sh skill": 80,
							"St experience": 0,
							"Ps experience": 0,
							"Tk experience": 0,
							"Sh experience": 0
						}
					}
				],
				"Support factor": 1,
				"Mean attendance": 11000,
				"StdDev attendance": 2000
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CTeam>::NAME_KEY } + ": " + std::string{ team.GetName() } );
		result.push_back( std::string{ futsim::json_traits<CTeam>::ABBREVIATION_KEY } + ": " + std::string{ team.GetAbbreviation() } );
		result.push_back( std::string{ futsim::json_traits<CTeam>::MANAGER_KEY } + ": " + std::string{ team.GetManager() } );
		for( const auto& player : team.GetPlayers() )
			result.push_back( std::string{ futsim::json_traits<CPlayer>::KEY } + ": " + std::string{ team.GetPlayer( player.GetKnownName() ).GetKnownName() } );
		result.push_back( std::string{ futsim::json_traits<CTeam>::SUPPORT_FACTOR_KEY } + ": " + std::to_string( team.GetSupportFactor() ) );
		result.push_back( std::string{ futsim::json_traits<CTeam>::MEAN_ATTENDANCE_KEY } + ": " + std::to_string( team.GetAttendanceDistributionParameters().mean() ) );
		result.push_back( std::string{ futsim::json_traits<CTeam>::STD_DEV_ATTENDANCE_KEY } + ": " + std::to_string( team.GetAttendanceDistributionParameters().stddev() ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, team );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TTeam::ExpectedResults() noexcept
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
		"				\"First name\": \"Lionel\",\n"
		"				\"Surnames\": \"Messi\",\n"
		"				\"Age\": 35,\n"
		"				\"Nationality\": \"ARG\",\n"
		"				\"Player skills\": {\n"
		"					\"St skill\": 1,\n"
		"					\"Tk skill\": 1,\n"
		"					\"Ps skill\": 1,\n"
		"					\"Sh skill\": 99,\n"
		"					\"St experience\": 0,\n"
		"					\"Tk experience\": 0,\n"
		"					\"Ps experience\": 0,\n"
		"					\"Sh experience\": 0\n"
		"				}\n"
		"			},\n"
		"			{\n"
		"				\"First name\": \"Ansu\",\n"
		"				\"Surnames\": \"Fati\",\n"
		"				\"Known name\": \"Ansu Fati\",\n"
		"				\"Age\": 20,\n"
		"				\"Nationality\": \"ESP\",\n"
		"				\"Player skills\": {\n"
		"					\"St skill\": 1,\n"
		"					\"Tk skill\": 1,\n"
		"					\"Ps skill\": 1,\n"
		"					\"Sh skill\": 80,\n"
		"					\"St experience\": 0,\n"
		"					\"Tk experience\": 0,\n"
		"					\"Ps experience\": 0,\n"
		"					\"Sh experience\": 0\n"
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
