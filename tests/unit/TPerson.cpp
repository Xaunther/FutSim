#include "ATest.h"

#include "CPerson.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim;
using namespace nlohmann;

INITIALIZE_TEST( TPerson )

void TPerson::TestExceptions() const
{
	// Test member constructor
	CheckException( []()
	{
		CPerson{ "", "López", {}, 35, futsim::E_NATIONALITY::ARG };
	},
		"The name cannot be empty." );
	CheckException( []()
	{
		CPerson{ "Marcos", "", {}, 35, futsim::E_NATIONALITY::ARG };
	},
		"The surnames cannot be empty." );

	// Test JSON constructor
	CheckException( []()
	{
		ValueFromJSONKeyString<CPerson>( R"( {
			"Person": {}
		} )" );
	}, "key 'First name' not found" );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPerson>( R"( {
			"Person": {
				"First name": ""
			}
		} )" );
	}, "The name cannot be empty." );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPerson>( R"( {
			"Person": {
				"First name": "Lionel"
			}
		} )" );
	}, "key 'Surnames' not found" );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPerson>( R"( {
			"Person": {
				"First name": "Lionel",
				"Surnames": ""
			}
		} )" );
	}, "The surnames cannot be empty." );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPerson>( R"( {
			"Person": {
				"First name": "Lionel",
				"Surnames": "Messi"
			}
		} )" );
	}, "key 'Age' not found" );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPerson>( R"( {
			"Person": {
				"First name": "Lionel",
				"Surnames": "Messi",
				"Age": 35
			}
		} )" );
	}, "key 'Nationality' not found" );
}

std::vector<std::string> TPerson::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& person : {
		CPerson{ "Lorenzo", "Blanco", {}, 35, futsim::E_NATIONALITY::ARG },
		CPerson{ "Pedro", "Pérez Martínez", "Perico", 20, futsim::E_NATIONALITY::ESP },
		ValueFromJSONKeyString<CPerson>( R"( {
			"Person": {
				"Surnames": "Blanco",
				"First name": "Lorenzo",
				"Age": 35,
				"Nationality": "ARG"
			}
		} )" ),
		ValueFromJSONKeyString<CPerson>( R"( {
			"Person": {
				"First name": "Pedro",
				"Surnames": "Pérez Martínez",
				"Known name": "Perico",
				"Age": 20,
				"Nationality": "ESP"
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CPerson>::FIRST_NAME } + ": " + std::string{ person.GetFirstName() } );
		result.push_back( std::string{ futsim::json_traits<CPerson>::SURNAMES } + ": " + std::string{ person.GetSurnames() } );
		result.push_back( std::string{ futsim::json_traits<CPerson>::KNOWN_NAME } + ": " + std::string{ person.GetKnownName() } );
		result.push_back( std::string{ futsim::json_traits<CPerson>::AGE } + ": " + std::to_string( person.GetAge() ) );
		result.push_back( std::string{ futsim::json_traits<CPerson>::NATIONALITY } + ": " + std::string{ ToString( person.GetNationality() ) } );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, person );
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
