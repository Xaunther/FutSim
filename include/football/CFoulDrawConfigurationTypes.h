#pragma once

#include "CPossessionDrawConfigurationTypes.h"

#include <random>

namespace futsim::football::CFoulDrawConfigurationTypes
{

//! Type for a probability.
using probability = CPossessionDrawConfigurationTypes::probability;
//! Type for a stat.
using stat = probability;
//! Type for the foul draw outcome.
using foul_outcome = unsigned short;
//! Type for the foul draw distribution.
using foul_distribution = std::discrete_distribution<foul_outcome>;

} // futsim::football::CFoulDrawConfigurationTypes namespace