#include "ITest.h"

#include "football/CStadium.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TStadium )

void TStadium::TestExceptions() const
{
	//! Test member constructor
	CheckException( []() { CStadium{ "", 1000, 1 }; }, "The stadium name cannot be empty." );
	CheckException( []() { CStadium{ "Camp Nou", 98000, -2 }; }, "The ambient factor cannot be negative." );

	//! Test JSON constructor
	CheckException( []() { futsim::ValueFromJSON<CStadium>( json::parse( R"( {
			"Stadium": {}
		} )" ) ); }, "key 'Name' not found" );
	CheckException( []() { futsim::ValueFromJSON<CStadium>( json::parse( R"( {
			"Stadium": {
				"Name": ""
			}
		} )" ) ); }, "The stadium name cannot be empty." );
	CheckException( []() { futsim::ValueFromJSON<CStadium>( json::parse( R"( {
			"Stadium": {
				"Name": "Camp Nou"
			}
		} )" ) ); }, "key 'Capacity' not found" );
	CheckException( []() { futsim::ValueFromJSON<CStadium>( json::parse( R"( {
			"Stadium": {
				"Name": "Camp Nou",
				"Capacity": 98000
			}
		} )" ) ); }, "key 'Ambient factor' not found" );

	CheckException( []() { futsim::ValueFromJSON<CStadium>( json::parse( R"( {
			"Stadium": {
				"Name": "Camp Nou",
				"Capacity": 98000,
				"Ambient factor": -2
			}
		} )" ) ); }, "The ambient factor cannot be negative." );
}

std::vector<std::string> TStadium::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& stadium : {
		CStadium{ "Camp Nou", 98000, 0.8 },
		CStadium{ "The New Lawn", 5147, 0.5 },
		futsim::ValueFromJSON<CStadium>( json::parse( R"( {
			"Stadium": {
				"Name": "Camp Nou",
				"Capacity": 98000,
				"Ambient factor": 0.8
			}
		} )" ) ),
		futsim::ValueFromJSON<CStadium>( json::parse( R"( {
			"Stadium": {
				"Name": "The New Lawn",
				"Capacity": 5147,
				"Ambient factor": 0.5
			}
		} )" ) ) } )
	{
		result.push_back( std::string{ CStadium::JSON_NAME } + ": " + std::string{ stadium.GetName() } );
		result.push_back( std::string{ CStadium::JSON_CAPACITY } + ": " + std::to_string( stadium.GetCapacity() ) );
		result.push_back( std::string{ CStadium::JSON_AMBIENT_FACTOR } + ": " + std::to_string( stadium.GetAmbientFactor() ) );
		futsim::IJsonableTypes::json outputJSON;
		outputJSON[ CStadium::JSON_KEY ] = stadium.ToJSON();
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TStadium::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Name: Camp Nou",
		"Capacity: 98000",
		"Ambient factor: 0.800000",
		"{\n"
		"	\"Stadium\": {\n"
		"		\"Name\": \"Camp Nou\",\n"
		"		\"Capacity\": 98000,\n"
		"		\"Ambient factor\": 0.8\n"
		"	}\n"
		"}",
		"Name: The New Lawn",
		"Capacity: 5147",
		"Ambient factor: 0.500000",
		"{\n"
		"	\"Stadium\": {\n"
		"		\"Name\": \"The New Lawn\",\n"
		"		\"Capacity\": 5147,\n"
		"		\"Ambient factor\": 0.5\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
