#include "ITest.h"

#include "football/CPlayer.h"

#include "NationalityUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayer )

void TPlayer::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CPlayer{ "", "Messi", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ 1, 1, 1, 1, 1, 1, 1, 1 } }; },
		"The name cannot be empty." );
	CheckException( []() { CPlayer{ "Lionel", "", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ 1, 1, 1, 1, 1, 1, 1, 1 } }; },
		"The surnames cannot be empty." );

	//! Test JSON constructor
	CheckException( []() { CPlayer{ json::parse( R"( {
			"Player": {}
		} )" )[ CPlayer::JSON_NAME ] }; }, "key 'First name' not found" );
	CheckException( []() { CPlayer{ json::parse( R"( {
			"Player": {
				"First name": ""
			}
		} )" )[ CPlayer::JSON_NAME ] }; }, "The name cannot be empty." );
	CheckException( []() { CPlayer{ json::parse( R"( {
			"Player": {
				"First name": "Lionel"
			}
		} )" )[ CPlayer::JSON_NAME ] }; }, "key 'Surnames' not found" );
	CheckException( []() { CPlayer{ json::parse( R"( {
			"Player": {
				"First name": "Lionel",
				"Surnames": ""
			}
		} )" )[ CPlayer::JSON_NAME ] }; }, "The surnames cannot be empty." );
	CheckException( []() { CPlayer{ json::parse( R"( {
			"Player": {
				"First name": "Lionel",
				"Surnames": "Messi"
			}
		} )" )[ CPlayer::JSON_NAME ] }; }, "key 'Age' not found" );
	CheckException( []() { CPlayer{ json::parse( R"( {
			"Player": {
				"First name": "Lionel",
				"Surnames": "Messi",
				"Age": 35
			}
		} )" )[ CPlayer::JSON_NAME ] }; }, "key 'Nationality' not found" );
	CheckException( []() { CPlayer{ json::parse( R"( {
			"Player": {
				"First name": "Lionel",
				"Surnames": "Messi",
				"Age": 35,
				"Nationality": "ARG"
			}
		} )" )[ CPlayer::JSON_NAME ] }; }, "key 'Player skills' not found" );
}

std::vector<std::string> TPlayer::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& player : {
		CPlayer{ "Lionel", "Messi", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ 1, 1, 1, 99, 0, 0, 0, 0 } },
		CPlayer{ "Ansu", "Fati", "Ansu Fati", 20, futsim::E_NATIONALITY::ESP, CPlayerSkills{ 1, 1, 1, 80, 0, 0, 0, 0 } },
		CPlayer{ json::parse( R"( {
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
		} )" )[ CPlayer::JSON_NAME ] },
		CPlayer{ json::parse( R"( {
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
		} )" )[ CPlayer::JSON_NAME ] } } )
	{
		result.push_back( std::string{ CPlayer::JSON_FIRST_NAME } + ": " + std::string{ player.GetFirstName() } );
		result.push_back( std::string{ CPlayer::JSON_SURNAMES } + ": " + std::string{ player.GetSurnames() } );
		result.push_back( std::string{ CPlayer::JSON_KNOWN_NAME } + ": " + std::string{ player.GetKnownName() } );
		result.push_back( std::string{ CPlayer::JSON_AGE } + ": " + std::to_string( player.GetAge() ) );
		result.push_back( std::string{ CPlayer::JSON_NATIONALITY } + ": " + futsim::ToString( player.GetNationality() ) );
		result.push_back( std::string{ CPlayerSkills::JSON_NAME } + ": " + player.GetPlayerSkills().ToJSON().dump( 1, '\t' ) );
		futsim::IJsonableTypes::json outputJSON;
		outputJSON[ CPlayer::JSON_NAME ] = player.ToJSON();
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPlayer::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"First name: Lionel",
		"Surnames: Messi",
		"Known name: Messi",
		"Age: 35",
		"Nationality: ARG",
		"Player skills: {\n"
		"	\"GK skill\": 1,\n"
		"	\"DF skill\": 1,\n"
		"	\"MF skill\": 1,\n"
		"	\"FW skill\": 99,\n"
		"	\"GK experience\": 0,\n"
		"	\"DF experience\": 0,\n"
		"	\"MF experience\": 0,\n"
		"	\"FW experience\": 0\n"
		"}",
		"{\n"
		"	\"Player\": {\n"
		"		\"First name\": \"Lionel\",\n"
		"		\"Surnames\": \"Messi\",\n"
		"		\"Age\": 35,\n"
		"		\"Nationality\": \"ARG\",\n"
		"		\"Player skills\": {\n"
		"			\"GK skill\": 1,\n"
		"			\"DF skill\": 1,\n"
		"			\"MF skill\": 1,\n"
		"			\"FW skill\": 99,\n"
		"			\"GK experience\": 0,\n"
		"			\"DF experience\": 0,\n"
		"			\"MF experience\": 0,\n"
		"			\"FW experience\": 0\n"
		"		}\n"
		"	}\n"
		"}",
		"First name: Ansu",
		"Surnames: Fati",
		"Known name: Ansu Fati",
		"Age: 20",
		"Nationality: ESP",
		"Player skills: {\n"
		"	\"GK skill\": 1,\n"
		"	\"DF skill\": 1,\n"
		"	\"MF skill\": 1,\n"
		"	\"FW skill\": 80,\n"
		"	\"GK experience\": 0,\n"
		"	\"DF experience\": 0,\n"
		"	\"MF experience\": 0,\n"
		"	\"FW experience\": 0\n"
		"}",
		"{\n"
		"	\"Player\": {\n"
		"		\"First name\": \"Ansu\",\n"
		"		\"Surnames\": \"Fati\",\n"
		"		\"Known name\": \"Ansu Fati\",\n"
		"		\"Age\": 20,\n"
		"		\"Nationality\": \"ESP\",\n"
		"		\"Player skills\": {\n"
		"			\"GK skill\": 1,\n"
		"			\"DF skill\": 1,\n"
		"			\"MF skill\": 1,\n"
		"			\"FW skill\": 80,\n"
		"			\"GK experience\": 0,\n"
		"			\"DF experience\": 0,\n"
		"			\"MF experience\": 0,\n"
		"			\"FW experience\": 0\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
