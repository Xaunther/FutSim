#pragma once

#include "football/types/CTacticConfiguration.h"

#include <map>

namespace futsim::football
{

class CTacticConfiguration;

namespace types::CTacticsConfiguration
{

//! Type for the tactic configurations.
using tactic_configurations = std::map<types::CTacticConfiguration::id, football::CTacticConfiguration>;

} // types::CTacticsConfiguration namespace


} // futsim::football namespace