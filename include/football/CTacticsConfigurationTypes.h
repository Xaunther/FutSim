#pragma once

#include "types/CTacticConfiguration.h"

#include <map>

namespace futsim::football
{

class CTacticConfiguration;

namespace CTacticsConfigurationTypes
{

//! Type for the tactic configurations.
using tactic_configurations = std::map<types::CTacticConfiguration::id, CTacticConfiguration>;

} // CTacticsConfigurationTypes namespace


} // futsim::football namespace