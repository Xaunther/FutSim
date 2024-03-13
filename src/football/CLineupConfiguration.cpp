#include "football/CLineupConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Checks the validity of a range.
 * @param aRange Range.
 * @param aRangeDescription Range description to add to the error message.
*/
const CLineupConfigurationTypes::player_count_range& CheckRange( const CLineupConfigurationTypes::player_count_range& aRange,
	const std::string_view aRangeDescription );

} // anonymous namespace

CLineupConfiguration::CLineupConfiguration(
	const player_count_range& aDFRange,
	const player_count_range& aMFRange,
	const player_count_range& aFWRange
) try :
	mDFRange( CheckRange( aDFRange, "DF" ) ),
	mMFRange( CheckRange( aMFRange, "MF" ) ),
	mFWRange( CheckRange( aFWRange, "FW" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup configuration." )

CLineupConfiguration::CLineupConfiguration( const json& aJSON ) try :
	mDFRange( aJSON.contains( JSON_MIN_DFS ) || aJSON.contains( JSON_MAX_DFS ) ?
		CheckRange( { ValueFromRequiredJSONKey<player_count_range::first_type>( aJSON, JSON_MIN_DFS ),
		ValueFromOptionalJSONKey<player_count_range::second_type>( aJSON, JSON_MAX_DFS ) }, "DF" ) : DEFAULT_DF_RANGE ),
	mMFRange( aJSON.contains( JSON_MIN_MFS ) || aJSON.contains( JSON_MAX_MFS ) ?
		CheckRange( { ValueFromRequiredJSONKey<player_count_range::first_type>( aJSON, JSON_MIN_MFS ),
		ValueFromOptionalJSONKey<player_count_range::second_type>( aJSON, JSON_MAX_MFS ) }, "MF" ) : DEFAULT_MF_RANGE ),
	mFWRange( aJSON.contains( JSON_MIN_FWS ) || aJSON.contains( JSON_MAX_FWS ) ?
		CheckRange( { ValueFromRequiredJSONKey<player_count_range::first_type>( aJSON, JSON_MIN_FWS ),
		ValueFromOptionalJSONKey<player_count_range::second_type>( aJSON, JSON_MAX_FWS ) }, "FW" ) : DEFAULT_FW_RANGE )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup configuration from JSON." )

const CLineupConfiguration::player_count_range& CLineupConfiguration::GetDFRange() const noexcept
{
	return mDFRange;
}

const CLineupConfiguration::player_count_range& CLineupConfiguration::GetMFRange() const noexcept
{
	return mMFRange;
}

const CLineupConfiguration::player_count_range& CLineupConfiguration::GetFWRange() const noexcept
{
	return mFWRange;
}

namespace
{

const CLineupConfigurationTypes::player_count_range& CheckRange( const CLineupConfigurationTypes::player_count_range& aRange,
	const std::string_view aRangeDescription ) try
{
	if( aRange.second && ( *aRange.second ) < aRange.first )
		throw std::invalid_argument{ "The maximum number of " + std::string{ aRangeDescription } + "s cannot be smaller than the minimum number." };
	return aRange;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aRangeDescription << " range." )

} // anonymous namespace

} // futsim::football namespace