#pragma once

#include "CTacticConfigurationTypes.h"

#include <map>

namespace futsim::football
{

class CTacticConfiguration;

namespace CTacticsConfigurationTypes
{

//! Type for the tactic configurations.
using tactic_configurations = std::map<CTacticConfigurationTypes::id, CTacticConfiguration>;

} // CTacticsConfigurationTypes namespace


} // futsim::football namespace