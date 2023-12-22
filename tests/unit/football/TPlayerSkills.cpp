#include "ITest.h"

#include "football/CPlayerSkills.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayerSkills )

void TPlayerSkills::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CPlayerSkills{ 0, 1, 1, 1, 1, 1, 1, 1 }; }, "The GK skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 0, 1, 1, 1, 1, 1, 1 }; }, "The DF skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 1, 0, 1, 1, 1, 1, 1 }; }, "The MF skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 1, 1, 0, 1, 1, 1, 1 }; }, "The FW skill value must be greater than 0." );

	//! Test JSON constructor
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {}
		} )" ); }, "key 'GK skill' not found" );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 0
			}
		} )" ); }, "The GK skill value must be greater than 0." );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1
			}
		} )" ); }, "key 'DF skill' not found" );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 0
			}
		} )" ); }, "The DF skill value must be greater than 0." );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1
			}
		} )" ); }, "key 'MF skill' not found" );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 0
			}
		} )" ); }, "The MF skill value must be greater than 0." );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1
			}
		} )" ); }, "key 'FW skill' not found" );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 0
			}
		} )" ); }, "The FW skill value must be greater than 0." );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1
			}
		} )" ); }, "key 'GK experience' not found" );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0
			}
		} )" ); }, "key 'DF experience' not found" );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0
			}
		} )" ); }, "key 'MF experience' not found" );
	CheckException( []() { futsim::ValueFromJSONString<CPlayerSkills>( R"( {
			"Player skills": {
				"GK skill": 1,
				"DF skill": 1,
				"MF skill": 1,
				"FW skill": 1,
				"GK experience": 0,
				"DF experience": 0,
				"MF experience": 0
			}
		} )" ); }, "key 'FW experience' not found" );
}

std::vector<std::string> TPlayerSkills::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& playerSkills : {
		CPlayerSkills{ 1, 1, 1, 1, 0, 0, 0, 0 },
		CPlayerSkills{ 99, 10, 50, 10, 60, 20, 45, 0 },
		futsim::ValueFromJSONString<CPlayerSkills>( R"( {
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
		} )" ),
		futsim::ValueFromJSONString<CPlayerSkills>( R"( {
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
		} )" ) } )
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
		outputJSON[ CPlayerSkills::JSON_KEY ] = playerSkills.ToJSON();
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
