#include "ATest.h"

#include "football/CPlayerSkills.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPlayerSkills )

void TPlayerSkills::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CPlayerSkills{ { 0, 1, 1, 1 }, { 1, 1, 1, 1 } };
	}, "The St skill value must be greater than 0." );
	CheckException( []()
	{
		CPlayerSkills{ { 1, 0, 1, 1 }, { 1, 1, 1, 1 } };
	}, "The Tk skill value must be greater than 0." );
	CheckException( []()
	{
		CPlayerSkills{ { 1, 1, 0, 1 }, { 1, 1, 1, 1 } };
	}, "The Ps skill value must be greater than 0." );
	CheckException( []()
	{
		CPlayerSkills{ { 1, 1, 1, 0 }, { 1, 1, 1, 1 } };
	}, "The Sh skill value must be greater than 0." );

	// Test JSON constructor
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {}
		} )" );
	}, "key 'St skill' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 0
			}
		} )" );
	}, "The St skill value must be greater than 0." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1
			}
		} )" );
	}, "key 'Tk skill' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 0
			}
		} )" );
	}, "The Tk skill value must be greater than 0." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 1
			}
		} )" );
	}, "key 'Ps skill' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 1,
				"Ps skill": 0
			}
		} )" );
	}, "The Ps skill value must be greater than 0." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 1,
				"Ps skill": 1
			}
		} )" );
	}, "key 'Sh skill' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 1,
				"Ps skill": 1,
				"Sh skill": 0
			}
		} )" );
	}, "The Sh skill value must be greater than 0." );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 1,
				"Ps skill": 1,
				"Sh skill": 1
			}
		} )" );
	}, "key 'St experience' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 1,
				"Ps skill": 1,
				"Sh skill": 1,
				"St experience": 0
			}
		} )" );
	}, "key 'Tk experience' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 1,
				"Ps skill": 1,
				"Sh skill": 1,
				"St experience": 0,
				"Tk experience": 0
			}
		} )" );
	}, "key 'Ps experience' not found" );
	CheckException( []()
	{
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Tk skill": 1,
				"Ps skill": 1,
				"Sh skill": 1,
				"St experience": 0,
				"Tk experience": 0,
				"Ps experience": 0
			}
		} )" );
	}, "key 'Sh experience' not found" );
}

std::vector<std::string> TPlayerSkills::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& playerSkills : {
		CPlayerSkills{ { 1, 1, 1, 1 }, { 0, 0, 0, 0 } },
		CPlayerSkills{ { 99, 10, 50, 10 }, { 60, 20, 45, 0 } },
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St skill": 1,
				"Ps skill": 1,
				"Tk skill": 1,
				"Sh skill": 1,
				"St experience": 0,
				"Tk experience": 0,
				"Ps experience": 0,
				"Sh experience": 0
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CPlayerSkills>( R"( {
			"Player skills": {
				"St experience": 60,
				"St skill": 99,
				"Tk skill": 10,
				"Ps skill": 50,
				"Sh skill": 10,
				"Ps experience": 45,
				"Tk experience": 20,
				"Sh experience": 0
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CPlayerSkills>::SKILL_KEY<E_PLAYER_SKILL::St> } + ": " + std::to_string( playerSkills.GetSkill( E_PLAYER_SKILL::St ) ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerSkills>::SKILL_KEY<E_PLAYER_SKILL::Tk> } + ": " + std::to_string( playerSkills.GetSkill( E_PLAYER_SKILL::Tk ) ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerSkills>::SKILL_KEY<E_PLAYER_SKILL::Ps> } + ": " + std::to_string( playerSkills.GetSkill( E_PLAYER_SKILL::Ps ) ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerSkills>::SKILL_KEY<E_PLAYER_SKILL::Sh> } + ": " + std::to_string( playerSkills.GetSkill( E_PLAYER_SKILL::Sh ) ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerSkills>::XP_KEY<E_PLAYER_SKILL::St> } + ": " + std::to_string( playerSkills.GetExperience( E_PLAYER_SKILL::St ) ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerSkills>::XP_KEY<E_PLAYER_SKILL::Tk> } + ": " + std::to_string( playerSkills.GetExperience( E_PLAYER_SKILL::Tk ) ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerSkills>::XP_KEY<E_PLAYER_SKILL::Ps> } + ": " + std::to_string( playerSkills.GetExperience( E_PLAYER_SKILL::Ps ) ) );
		result.push_back( std::string{ futsim::json_traits<CPlayerSkills>::XP_KEY<E_PLAYER_SKILL::Sh> } + ": " + std::to_string( playerSkills.GetExperience( E_PLAYER_SKILL::Sh ) ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, playerSkills );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPlayerSkills::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"St skill: 1",
		"Tk skill: 1",
		"Ps skill: 1",
		"Sh skill: 1",
		"St experience: 0",
		"Tk experience: 0",
		"Ps experience: 0",
		"Sh experience: 0",
		"{\n"
		"	\"Player skills\": {\n"
		"		\"St skill\": 1,\n"
		"		\"Tk skill\": 1,\n"
		"		\"Ps skill\": 1,\n"
		"		\"Sh skill\": 1,\n"
		"		\"St experience\": 0,\n"
		"		\"Tk experience\": 0,\n"
		"		\"Ps experience\": 0,\n"
		"		\"Sh experience\": 0\n"
		"	}\n"
		"}",
		"St skill: 99",
		"Tk skill: 10",
		"Ps skill: 50",
		"Sh skill: 10",
		"St experience: 60",
		"Tk experience: 20",
		"Ps experience: 45",
		"Sh experience: 0",
		"{\n"
		"	\"Player skills\": {\n"
		"		\"St skill\": 99,\n"
		"		\"Tk skill\": 10,\n"
		"		\"Ps skill\": 50,\n"
		"		\"Sh skill\": 10,\n"
		"		\"St experience\": 60,\n"
		"		\"Tk experience\": 20,\n"
		"		\"Ps experience\": 45,\n"
		"		\"Sh experience\": 0\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
