#include "ITest.h"

#include "football/CPlayer.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayer )

void TPlayer::TestExceptions() const
{
	//! Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONKeyString<CPlayer>( R"( {
			"Player": {
				"First name": "Lionel",
				"Surnames": "Messi",
				"Age": 35,
				"Nationality": "ARG"
			}
		} )" ); }, "key 'Player skills' not found" );
}

std::vector<std::string> TPlayer::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& player : {
		CPlayer{ "Lionel", "Messi", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ 1, 1, 1, 99, 0, 0, 0, 0 } },
		CPlayer{ "Ansu", "Fati", "Ansu Fati", 20, futsim::E_NATIONALITY::ESP, CPlayerSkills{ 1, 1, 1, 80, 0, 0, 0, 0 } },
		futsim::ValueFromJSONKeyString<CPlayer>( R"( {
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
		} )" ),
		futsim::ValueFromJSONKeyString<CPlayer>( R"( {
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
		} )" ) } )
	{
		result.push_back( player.GetPlayerSkills().JSON_KEY.data() );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, player );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPlayer::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Player skills",
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
		"Player skills",
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
