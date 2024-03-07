#pragma once

#include "football/CFoulDrawConfigurationTypes.h"

namespace futsim::football::CGoalDrawConfigurationTypes
{

//! Type for a probability.
using probability = CFoulDrawConfigurationTypes::probability;
//! Type for a stat.
using stat = CFoulDrawConfigurationTypes::stat;
//! Type for the effective skill value.
using effective_skill = double;
//! Type for the chance outcome draw distribution.
using chance_outcome_distribution = CFoulDrawConfigurationTypes::foul_distribution;

} // futsim::football::CGoalDrawConfigurationTypes namespace