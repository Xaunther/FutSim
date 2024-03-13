#include "football/CMatchStrategy.h"

namespace futsim::football
{

const CMatchStrategy::id& CMatchStrategy::GetTacticID() const noexcept
{
	return mTacticID;
}

const CLineup& CMatchStrategy::GetLineup() const noexcept
{
	return mLineup;
}

} // futsim::football namespace