#include "football/CPossessionDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "ProbabilityUtils.h"

namespace futsim::football
{

CPossessionDrawConfiguration::CPossessionDrawConfiguration(
	const probability& aKeepPossessionProbability
) try :
	mKeepPossessionProbability( CheckProbability( aKeepPossessionProbability, "probability to keep possession" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the possession draw configuration." )

const CPossessionDrawConfiguration::probability& CPossessionDrawConfiguration::GetKeepPossessionProbability() const noexcept
{
	return mKeepPossessionProbability;
}

} // futsim namespace