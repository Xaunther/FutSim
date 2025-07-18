#include "ATest.h"

#include "football/CPenaltyShootoutConfiguration.h"

#include "JsonUtils.h"

using namespace futsim::football;
using namespace nlohmann;

INITIALIZE_TEST( TPenaltyShootoutConfiguration )

void TPenaltyShootoutConfiguration::TestExceptions()
{
}

std::vector<std::string> TPenaltyShootoutConfiguration::ObtainedResults() noexcept
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
		result.push_back( std::string{ futsim::json_traits<CPenaltyShootoutConfiguration>::SEQUENCE_KEY } + ": " + std::string{ ToString( penaltyShootoutConfiguration.GetPenaltySequence() ) } );
		result.push_back( std::string{ futsim::json_traits<CPenaltyShootoutConfiguration>::MIN_PENALTY_COUNT_KEY } + ": " + std::to_string( penaltyShootoutConfiguration.GetMinPenaltyCount() ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, penaltyShootoutConfiguration );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPenaltyShootoutConfiguration::ExpectedResults() noexcept
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
