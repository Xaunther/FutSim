#include "football/CPossessionDrawConfiguration.h"

namespace futsim::football
{

const CPossessionDrawConfiguration::probability& CPossessionDrawConfiguration::GetKeepPossessionProbability() const noexcept
{
	return mKeepPossessionProbability;
}

} // futsim namespace