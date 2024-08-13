#include "ATest.h"

#include "CPlayTime.h"

#include "JsonUtils.h"

#include <iostream>

using namespace futsim;
using namespace nlohmann;

INITIALIZE_TEST( TPlayTime )

void TPlayTime::TestExceptions() const
{
	// Test member constructor
	CheckException( []()
	{
		CPlayTime{ 0, 45 };
	},
		"The number of periods cannot be zero." );
	CheckException( []()
	{
		CPlayTime{ 2, 0 };
	},
		"The length of the period cannot be zero." );

	// Test JSON constructor
	CheckException( []()
	{
		ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {}
		} )" );
	}, "key 'Period count' not found" );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 0
			}
		} )" );
	}, "The number of periods cannot be zero." );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 2
			}
		} )" );
	}, "key 'Period time' not found" );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 2,
				"Period time": 0
			}
		} )" );
	}, "The length of the period cannot be zero." );
}

std::vector<std::string> TPlayTime::ObtainedResults() const noexcept
{
	std::vector<std::string> result;

	for( const auto& playTime : {
		CPlayTime{ 2, 45 },
		ValueFromJSONKeyString<CPlayTime>( R"( {
			"Play time": {
				"Period count": 2,
				"Period time": 45
			}
		} )" ) } )
	{
		result.push_back( std::string{ futsim::json_traits<CPlayTime>::PERIOD_COUNT } + ": " + std::to_string( playTime.GetPeriodCount() ) );
		result.push_back( std::string{ futsim::json_traits<CPlayTime>::PERIOD_TIME } + ": " + std::to_string( playTime.GetPeriodTime() ) );
		futsim::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, playTime );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPlayTime::ExpectedResults() const noexcept
{
	std::vector<std::string> result{
		"Period count: 2",
		"Period time: 45",
		"{\n"
		"	\"Play time\": {\n"
		"		\"Period count\": 2,\n"
		"		\"Period time\": 45\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
