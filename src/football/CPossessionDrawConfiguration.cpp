#include "football/CPossessionDrawConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
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

CPossessionDrawConfiguration::CPossessionDrawConfiguration( const json& aJSON ) try :
	mKeepPossessionProbability( CheckProbability( ValueFromRequiredJSONKey<probability>( aJSON, JSON_KEEP_POSSESSION_PROBABILITY ), "probability to keep possession" ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the possession draw configuration from JSON." )

const CPossessionDrawConfiguration::probability& CPossessionDrawConfiguration::GetKeepPossessionProbability() const noexcept
{
	return mKeepPossessionProbability;
}

} // futsim namespace