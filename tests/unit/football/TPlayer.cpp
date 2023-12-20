#include "ITest.h"

#include "football/CPlayer.h"

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
	return result;
}

std::vector<std::string> TPlayer::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
