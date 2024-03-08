#pragma once

#include <random>

namespace futsim::football::CDrawConfigurationTypes
{

//! Type for a probability.
using probability = double;
//! Type for a stat.
using stat = probability;
//! Type for a draw outcome.
using outcome = unsigned int;
//! Type for the a discrete draw distribution.
using discrete_distribution = std::discrete_distribution<outcome>;
//! Type for the effective skill value.
using effective_skill = double;

} // futsim::football::CDrawConfigurationTypes namespace