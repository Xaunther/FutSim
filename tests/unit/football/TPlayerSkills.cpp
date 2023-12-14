#include "ITest.h"

#include "football/CPlayerSkills.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayerSkills )

void TPlayerSkills::DoRun() const
{
	//! Test member constructor
	CheckException( []() { CPlayerSkills{ 0, 1, 1, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 0, 1, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 1, 0, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 1, 1, 0, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );

	//! Test JSON constructor
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'FW experience' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'MF experience' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'DF experience' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'GK experience' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'FW skill' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'MF skill' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'DF skill' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'GK skill' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 0,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 0,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 0,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 0,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "The skill value must be greater than 0." );
}
