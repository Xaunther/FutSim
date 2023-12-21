#include "ITest.h"

#include "football/CPlayerSkills.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayerSkills )

void TPlayerSkills::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CPlayerSkills{ 0, 1, 1, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 0, 1, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 1, 0, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 1, 1, 0, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );

	//! Test JSON constructor
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'GK skill' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'DF skill' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'MF skill' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'FW skill' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'GK experience' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'DF experience' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'MF experience' not found" );
	CheckException( []() { CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] }; }, "key 'FW experience' not found" );
}

std::vector<std::string> TPlayerSkills::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& playerSkills : {
		CPlayerSkills{ 1, 1, 1, 1, 0, 0, 0, 0 },
		CPlayerSkills{ 99, 10, 50, 10, 60, 20, 45, 0 },
		CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK skill": 1,
				"MF skill": 1,
				"DF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] },
		CPlayerSkills{ json::parse( R"( {
			"Player skills": {
				"GK experience": 60,
				"GK skill": 99,
				"DF skill": 10,
				"MF skill": 50,
				"FW skill": 10,
				"MF experience": 45,
				"DF experience": 20,
				"FW experience": 0
			}
		} )" )[ CPlayerSkills::JSON_NAME ] } } )
	{
		result.push_back( std::string{ CPlayerSkills::JSON_GK_SKILL } + ": " + std::to_string( playerSkills.GetGKSkill() ) );
		result.push_back( std::string{ CPlayerSkills::JSON_DF_SKILL } + ": " + std::to_string( playerSkills.GetDFSkill() ) );
		result.push_back( std::string{ CPlayerSkills::JSON_MF_SKILL } + ": " + std::to_string( playerSkills.GetMFSkill() ) );
		result.push_back( std::string{ CPlayerSkills::JSON_FW_SKILL } + ": " + std::to_string( playerSkills.GetFWSkill() ) );
		result.push_back( std::string{ CPlayerSkills::JSON_GK_XP } + ": " + std::to_string( playerSkills.GetGKExperience() ) );
		result.push_back( std::string{ CPlayerSkills::JSON_DF_XP } + ": " + std::to_string( playerSkills.GetDFExperience() ) );
		result.push_back( std::string{ CPlayerSkills::JSON_MF_XP } + ": " + std::to_string( playerSkills.GetMFExperience() ) );
		result.push_back( std::string{ CPlayerSkills::JSON_FW_XP } + ": " + std::to_string( playerSkills.GetFWExperience() ) );
		futsim::IJsonableTypes::json outputJSON;
		outputJSON[ CPlayerSkills::JSON_NAME ] = playerSkills.ToJSON();
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPlayerSkills::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"GK skill: 1",
		"DF skill: 1",
		"MF skill: 1",
		"FW skill: 1",
		"GK experience: 0",
		"DF experience: 0",
		"MF experience: 0",
		"FW experience: 0",
		"{\n"
		"	\"Player skills\": {\n"
		"		\"GK skill\": 1,\n"
		"		\"DF skill\": 1,\n"
		"		\"MF skill\": 1,\n"
		"		\"FW skill\": 1,\n"
		"		\"GK experience\": 0,\n"
		"		\"DF experience\": 0,\n"
		"		\"MF experience\": 0,\n"
		"		\"FW experience\": 0\n"
		"	}\n"
		"}",
		"GK skill: 99",
		"DF skill: 10",
		"MF skill: 50",
		"FW skill: 10",
		"GK experience: 60",
		"DF experience: 20",
		"MF experience: 45",
		"FW experience: 0",
		"{\n"
		"	\"Player skills\": {\n"
		"		\"GK skill\": 99,\n"
		"		\"DF skill\": 10,\n"
		"		\"MF skill\": 50,\n"
		"		\"FW skill\": 10,\n"
		"		\"GK experience\": 60,\n"
		"		\"DF experience\": 20,\n"
		"		\"MF experience\": 45,\n"
		"		\"FW experience\": 0\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
