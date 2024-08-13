#include "ATest.h"

#include "football/CPlayer.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayer )

void TPlayer::TestExceptions() const
{
	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayer>( R"( {
			"Player": {
				"First name": "Lionel",
				"Surnames": "Messi",
				"Age": 35,
				"Nationality": "ARG"
			}
		} )" );
	}, "key 'Player skills' not found" );
}

std::vector<std::string> TPlayer::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& player : {
		CPlayer{ "Lionel", "Messi", {}, 35, futsim::E_NATIONALITY::ARG, CPlayerSkills{ { 1, 1, 1, 99 }, { 0, 0, 0, 0 } } },
		CPlayer{ "Ansu", "Fati", "Ansu Fati", 20, futsim::E_NATIONALITY::ESP, CPlayerSkills{ { 1, 1, 1, 80 }, { 0, 0, 0, 0 } } },
		futsim::ValueFromJSONKeyString<CPlayer>( R"( {
			"Player": {
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
		} )" ) } )
	{
		result.push_back( futsim::json_traits<std::decay_t<decltype( player.GetPlayerSkills() )>>::KEY.data() );
		futsim::types::IJsonable::json outputJSON;
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
		"			\"St skill\": 1,\n"
		"			\"Tk skill\": 1,\n"
		"			\"Ps skill\": 1,\n"
		"			\"Sh skill\": 99,\n"
		"			\"St experience\": 0,\n"
		"			\"Tk experience\": 0,\n"
		"			\"Ps experience\": 0,\n"
		"			\"Sh experience\": 0\n"
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
		"			\"St skill\": 1,\n"
		"			\"Tk skill\": 1,\n"
		"			\"Ps skill\": 1,\n"
		"			\"Sh skill\": 80,\n"
		"			\"St experience\": 0,\n"
		"			\"Tk experience\": 0,\n"
		"			\"Ps experience\": 0,\n"
		"			\"Sh experience\": 0\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
