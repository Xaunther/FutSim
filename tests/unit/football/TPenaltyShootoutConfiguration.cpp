#include "ITest.h"

#include "football/CPenaltyShootoutConfiguration.h"

#include "JsonUtils.h"
#include "football/PenaltySequenceUtils.h"

#include <iostream>

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPenaltyShootoutConfiguration )

void TPenaltyShootoutConfiguration::TestExceptions() const
{
	//! Test JSON constructor.
	CheckException( []() { futsim::ValueFromJSONKeyString<CPenaltyShootoutConfiguration>( R"( {
			"Penalty shootout configuration": {}
		} )" ); }, "key 'Sequence' not found" );
	CheckException( []() { futsim::ValueFromJSONKeyString<CPenaltyShootoutConfiguration>( R"( {
			"Penalty shootout configuration": {
				"Sequence": "AAA"
			}
		} )" ); }, "No penalty sequence matching the string 'AAA'." );
	CheckException( []() { futsim::ValueFromJSONKeyString<CPenaltyShootoutConfiguration>( R"( {
			"Penalty shootout configuration": {
				"Sequence": "AB"
			}
		} )" ); }, "key 'Min penalty count' not found" );
}

std::vector<std::string> TPenaltyShootoutConfiguration::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& penaltyShootoutConfiguration : {
		CPenaltyShootoutConfiguration{},
		CPenaltyShootoutConfiguration{ E_PENALTY_SEQUENCE::ABBA },
		CPenaltyShootoutConfiguration{ E_PENALTY_SEQUENCE::AB, 3 },
		futsim::ValueFromJSONKeyString<CPenaltyShootoutConfiguration>( R"( {
			"Penalty shootout configuration": {
				"Sequence": "AB",
				"Min penalty count": 5
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CPenaltyShootoutConfiguration>( R"( {
			"Penalty shootout configuration": {
				"Sequence": "ABBA",
				"Min penalty count": 5
			}
		} )" ),
		futsim::ValueFromJSONKeyString<CPenaltyShootoutConfiguration>( R"( {
			"Penalty shootout configuration": {
				"Sequence": "AB",
				"Min penalty count": 3
			}
		} )" ) } )
	{
		result.push_back( std::string{ CPenaltyShootoutConfiguration::JSON_SEQUENCE } + ": " + ToString( penaltyShootoutConfiguration.GetPenaltySequence() ) );
		result.push_back( std::string{ CPenaltyShootoutConfiguration::JSON_MIN_PENALTY_COUNT } + ": " + std::to_string( penaltyShootoutConfiguration.GetMinPenaltyCount() ) );
		futsim::IJsonableTypes::json outputJSON;
		AddToJSONKey( outputJSON, penaltyShootoutConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPenaltyShootoutConfiguration::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Sequence: AB",
		"Min penalty count: 5",
		"{\n"
		"	\"Penalty shootout configuration\": {\n"
		"		\"Sequence\": \"AB\",\n"
		"		\"Min penalty count\": 5\n"
		"	}\n"
		"}",
		"Sequence: ABBA",
		"Min penalty count: 5",
		"{\n"
		"	\"Penalty shootout configuration\": {\n"
		"		\"Sequence\": \"ABBA\",\n"
		"		\"Min penalty count\": 5\n"
		"	}\n"
		"}",
		"Sequence: AB",
		"Min penalty count: 3",
		"{\n"
		"	\"Penalty shootout configuration\": {\n"
		"		\"Sequence\": \"AB\",\n"
		"		\"Min penalty count\": 3\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
