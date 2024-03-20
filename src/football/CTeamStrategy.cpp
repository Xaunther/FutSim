#include "football/CTeamStrategy.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

CTeamStrategy::CTeamStrategy(
	const std::string_view aTacticID,
	const CLineup& aLineup
) try :
	mTacticID( aTacticID ),
	mLineup( aLineup )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team strategy." )

CTeamStrategy::CTeamStrategy( const json& aJSON ) try :
	mTacticID( ValueFromRequiredJSONKey<id>( aJSON, JSON_TACTIC ) ),
	mLineup( ValueFromRequiredJSONKey<CLineup>( aJSON ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team strategy from JSON." )

void CTeamStrategy::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mTacticID, JSON_TACTIC );
	AddToJSONKey( aJSON, mLineup );
}

std::string_view CTeamStrategy::GetTacticID() const noexcept
{
	return mTacticID;
}

const CLineup& CTeamStrategy::GetLineup() const noexcept
{
	return mLineup;
}

} // futsim::football namespace