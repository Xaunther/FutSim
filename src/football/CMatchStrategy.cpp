#include "football/CMatchStrategy.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

CMatchStrategy::CMatchStrategy(
	const id& aTacticID,
	const CLineup& aLineup
) try :
	mTacticID( aTacticID ),
	mLineup( aLineup )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match strategy." )

const CMatchStrategy::id& CMatchStrategy::GetTacticID() const noexcept
{
	return mTacticID;
}

const CLineup& CMatchStrategy::GetLineup() const noexcept
{
	return mLineup;
}

} // futsim::football namespace