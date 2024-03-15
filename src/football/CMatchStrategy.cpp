#include "football/CMatchStrategy.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

CMatchStrategy::CMatchStrategy(
	const std::string_view aTacticID,
	const CLineup& aLineup
) try :
	mTacticID( aTacticID ),
	mLineup( aLineup )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match strategy." )

CMatchStrategy::CMatchStrategy( const json& aJSON ) try :
	mTacticID( ValueFromRequiredJSONKey<id>( aJSON, JSON_TACTIC ) ),
	mLineup( ValueFromRequiredJSONKey<CLineup>( aJSON ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match strategy from JSON." )

void CMatchStrategy::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mTacticID, JSON_TACTIC );
	AddToJSONKey( aJSON, mLineup );
}

const CMatchStrategy::id& CMatchStrategy::GetTacticID() const noexcept
{
	return mTacticID;
}

const CLineup& CMatchStrategy::GetLineup() const noexcept
{
	return mLineup;
}

} // futsim::football namespace