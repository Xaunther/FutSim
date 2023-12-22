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
	return result;
}

std::vector<std::string> TStadium::ExpectedResults() const noexcept
{
	std::vector<std::string> result;
	return result;
}
