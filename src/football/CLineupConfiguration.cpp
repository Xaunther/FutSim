#include "football/CLineupConfiguration.h"

#include "football/CLineup.h"

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
const types::CLineupConfiguration::player_count_range& CheckRange( const types::CLineupConfiguration::player_count_range& aRange,
	const std::string_view aRangeDescription );

/**
 * @brief Checks the validity of the number of players in a position.
 * @param aPositionCount Number of players in a position.
 * @param aRange Range.
 * @param aRangeDescription Range description to add to the error message.
*/
void CheckLineupPosition( const types::CLineup::names::size_type& aPositionCount,
	const types::CLineupConfiguration::player_count_range& aRange, const std::string_view aRangeDescription );

/**
 * @brief Checks that the number of players in a position does not exceed the maximum allowed.
 * @param aPositionCount Number of players in a position.
 * @param aMaxCount Maximum allowed.
 * @param aRangeDescription Range description to add to the error message.
*/
void CheckMaxLineupPosition( const types::CLineup::names::size_type& aPositionCount,
	const types::CLineupConfiguration::player_count_range::max_type& aMaxCount, const std::string_view aRangeDescription );

} // anonymous namespace

CLineupConfiguration::CLineupConfiguration(
	const player_count_range& aDFRange,
	const player_count_range& aMFRange,
	const player_count_range& aFWRange,
	const player_count& aMinPlayerCount,
	const optional_player_count& aBenchedPlayersCount
) try :
	mDFRange( CheckRange( aDFRange, "DF" ) ),
	mMFRange( CheckRange( aMFRange, "MF" ) ),
	mFWRange( CheckRange( aFWRange, "FW" ) ),
	mMinPlayerCount( CheckRange( player_count_range{ aMinPlayerCount, MAX_PLAYERS }, "player" ).min ),
	mBenchedPlayersCount( aBenchedPlayersCount )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup configuration." )

CLineupConfiguration::CLineupConfiguration( const json& aJSON ) try :
	mDFRange( aJSON.contains( JSON_MIN_DFS ) || aJSON.contains( JSON_MAX_DFS ) ?
		CheckRange( { ValueFromRequiredJSONKey<player_count_range::min_type>( aJSON, JSON_MIN_DFS ),
		ValueFromOptionalJSONKey<player_count_range::max_type>( aJSON, JSON_MAX_DFS ) }, "DF" ) : DEFAULT_DF_RANGE ),
	mMFRange( aJSON.contains( JSON_MIN_MFS ) || aJSON.contains( JSON_MAX_MFS ) ?
		CheckRange( { ValueFromRequiredJSONKey<player_count_range::min_type>( aJSON, JSON_MIN_MFS ),
		ValueFromOptionalJSONKey<player_count_range::max_type>( aJSON, JSON_MAX_MFS ) }, "MF" ) : DEFAULT_MF_RANGE ),
	mFWRange( aJSON.contains( JSON_MIN_FWS ) || aJSON.contains( JSON_MAX_FWS ) ?
		CheckRange( { ValueFromRequiredJSONKey<player_count_range::min_type>( aJSON, JSON_MIN_FWS ),
		ValueFromOptionalJSONKey<player_count_range::max_type>( aJSON, JSON_MAX_FWS ) }, "FW" ) : DEFAULT_FW_RANGE ),
	mMinPlayerCount( CheckRange( { ValueFromOptionalJSONKey<player_count>( aJSON, JSON_MIN_PLAYERS, DEFAULT_MIN_PLAYERS ), MAX_PLAYERS }, "player" ).min ),
	mBenchedPlayersCount( ValueFromOptionalJSONKey<optional_player_count>( aJSON, JSON_BENCHED_PLAYERS ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the lineup configuration from JSON." )

void CLineupConfiguration::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mDFRange.min, JSON_MIN_DFS );
	if( mDFRange.max )
		AddToJSONKey( aJSON, *mDFRange.max, JSON_MAX_DFS );
	AddToJSONKey( aJSON, mMFRange.min, JSON_MIN_MFS );
	if( mMFRange.max )
		AddToJSONKey( aJSON, *mMFRange.max, JSON_MAX_MFS );
	AddToJSONKey( aJSON, mFWRange.min, JSON_MIN_FWS );
	if( mFWRange.max )
		AddToJSONKey( aJSON, *mFWRange.max, JSON_MAX_FWS );
	AddToJSONKey( aJSON, mMinPlayerCount, JSON_MIN_PLAYERS );
	if( mBenchedPlayersCount )
		AddToJSONKey( aJSON, *mBenchedPlayersCount, JSON_BENCHED_PLAYERS );
}

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

const CLineupConfiguration::player_count& CLineupConfiguration::GetMinPlayerCount() const noexcept
{
	return mMinPlayerCount;
}

const CLineupConfiguration::optional_player_count& CLineupConfiguration::GetBenchedPlayersCount() const noexcept
{
	return mBenchedPlayersCount;
}

const CLineup& CLineupConfiguration::CheckLineup( const CLineup& aLineup ) const try
{
	CheckLineupPosition( aLineup.GetPlayers< E_PLAYER_POSITION::DF >().size(), mDFRange, "DF" );
	CheckLineupPosition( aLineup.GetPlayers< E_PLAYER_POSITION::DM >().size()
		+ aLineup.GetPlayers< E_PLAYER_POSITION::MF >().size()
		+ aLineup.GetPlayers< E_PLAYER_POSITION::AM >().size(), mMFRange, "DM+MF+AM" );
	CheckLineupPosition( aLineup.GetPlayers< E_PLAYER_POSITION::FW >().size(), mFWRange, "FW" );
	CheckMaxLineupPosition( aLineup.GetSubs().size(), mBenchedPlayersCount, "subs" );
	CheckLineupPosition( std::ranges::distance( aLineup.CreatePlayersView<false>() ), { mMinPlayerCount, MAX_PLAYERS }, "players" );
	return aLineup;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the lineup against the configuration." )

namespace
{

const types::CLineupConfiguration::player_count_range& CheckRange( const types::CLineupConfiguration::player_count_range& aRange,
	const std::string_view aRangeDescription ) try
{
	if( aRange.max && ( *aRange.max ) < aRange.min )
		throw std::invalid_argument{ "The maximum number of " + std::string{ aRangeDescription } + "s cannot be smaller than the minimum number." };
	return aRange;
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aRangeDescription << " range." )

void CheckLineupPosition( const types::CLineup::names::size_type& aPositionCount,
	const types::CLineupConfiguration::player_count_range& aRange, const std::string_view aRangeDescription )
{
	if( aPositionCount < aRange.min )
		throw std::invalid_argument{ "The lineup has less " + std::string{ aRangeDescription } + " (" + std::to_string( aPositionCount ) + ") "
			"than the minimum allowed (" + std::to_string( aRange.min ) + ")." };
	CheckMaxLineupPosition( aPositionCount, aRange.max, aRangeDescription );
}

void CheckMaxLineupPosition( const types::CLineup::names::size_type& aPositionCount,
	const types::CLineupConfiguration::player_count_range::max_type& aMaxCount, const std::string_view aRangeDescription )
{
	if( aMaxCount && aPositionCount > *aMaxCount )
		throw std::invalid_argument{ "The lineup has more " + std::string{ aRangeDescription } + " (" + std::to_string( aPositionCount ) + ") "
			"than the maximum allowed (" + std::to_string( *aMaxCount ) + ")." };
}

} // anonymous namespace

} // futsim::football namespace