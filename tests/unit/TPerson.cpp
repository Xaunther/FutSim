#include "ITest.h"

#include "CPerson.h"

#include "NationalityUtils.h"

#include <iostream>

using namespace futsim;
using namespace nlohmann;

INITIALIZE_TEST( TPerson )

void TPerson::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CPerson{ "", "López", {}, 35, futsim::E_NATIONALITY::ARG }; },
		"The name cannot be empty." );
	CheckException( []() { CPerson{ "Marcos", "", {}, 35, futsim::E_NATIONALITY::ARG }; },
		"The surnames cannot be empty." );

	//! Test JSON constructor
	CheckException( []() { CPerson{ json::parse( R"( {
			"Person": {}
		} )" )[ CPerson::JSON_KEY ] }; }, "key 'First name' not found" );
	CheckException( []() { CPerson{ json::parse( R"( {
			"Person": {
				"First name": ""
			}
		} )" )[ CPerson::JSON_KEY ] }; }, "The name cannot be empty." );
	CheckException( []() { CPerson{ json::parse( R"( {
			"Person": {
				"First name": "Lionel"
			}
		} )" )[ CPerson::JSON_KEY ] }; }, "key 'Surnames' not found" );
	CheckException( []() { CPerson{ json::parse( R"( {
			"Person": {
				"First name": "Lionel",
				"Surnames": ""
			}
		} )" )[ CPerson::JSON_KEY ] }; }, "The surnames cannot be empty." );
	CheckException( []() { CPerson{ json::parse( R"( {
			"Person": {
				"First name": "Lionel",
				"Surnames": "Messi"
			}
		} )" )[ CPerson::JSON_KEY ] }; }, "key 'Age' not found" );
	CheckException( []() { CPerson{ json::parse( R"( {
			"Person": {
				"First name": "Lionel",
				"Surnames": "Messi",
				"Age": 35
			}
		} )" )[ CPerson::JSON_KEY ] }; }, "key 'Nationality' not found" );
}

std::vector<std::string> TPerson::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& person : {
		CPerson{ "Lorenzo", "Blanco", {}, 35, futsim::E_NATIONALITY::ARG },
		CPerson{ "Pedro", "Pérez Martínez", "Perico", 20, futsim::E_NATIONALITY::ESP },
		CPerson{ json::parse( R"( {
			"Person": {
				"Surnames": "Blanco",
				"First name": "Lorenzo",
				"Age": 35,
				"Nationality": "ARG"
			}
		} )" )[ CPerson::JSON_KEY ] },
		CPerson{ json::parse( R"( {
			"Person": {
				"First name": "Pedro",
				"Surnames": "Pérez Martínez",
				"Known name": "Perico",
				"Age": 20,
				"Nationality": "ESP"
			}
		} )" )[ CPerson::JSON_KEY ] } } )
	{
		result.push_back( std::string{ CPerson::JSON_FIRST_NAME } + ": " + std::string{ person.GetFirstName() } );
		result.push_back( std::string{ CPerson::JSON_SURNAMES } + ": " + std::string{ person.GetSurnames() } );
		result.push_back( std::string{ CPerson::JSON_KNOWN_NAME } + ": " + std::string{ person.GetKnownName() } );
		result.push_back( std::string{ CPerson::JSON_AGE } + ": " + std::to_string( person.GetAge() ) );
		result.push_back( std::string{ CPerson::JSON_NATIONALITY } + ": " + futsim::ToString( person.GetNationality() ) );
		futsim::IJsonableTypes::json outputJSON;
		outputJSON[ CPerson::JSON_KEY ] = person.ToJSON();
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPerson::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"First name: Lorenzo",
		"Surnames: Blanco",
		"Known name: Blanco",
		"Age: 35",
		"Nationality: ARG",
		"{\n"
		"	\"Person\": {\n"
		"		\"First name\": \"Lorenzo\",\n"
		"		\"Surnames\": \"Blanco\",\n"
		"		\"Age\": 35,\n"
		"		\"Nationality\": \"ARG\"\n"
		"	}\n"
		"}",
		"First name: Pedro",
		"Surnames: Pérez Martínez",
		"Known name: Perico",
		"Age: 20",
		"Nationality: ESP",
		"{\n"
		"	\"Person\": {\n"
		"		\"First name\": \"Pedro\",\n"
		"		\"Surnames\": \"Pérez Martínez\",\n"
		"		\"Known name\": \"Perico\",\n"
		"		\"Age\": 20,\n"
		"		\"Nationality\": \"ESP\"\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
