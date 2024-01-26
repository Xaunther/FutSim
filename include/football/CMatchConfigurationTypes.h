#pragma once

#include "football/CPlayTimeTypes.h"

namespace futsim::football
{

class CExtraTime;
class CPenaltyShootoutConfiguration;
class CTieCondition;

namespace CMatchConfigurationTypes
{

//! Type for the number of benched players.
using benched_count = CPlayTimeTypes::subs_count;
//! Type for the optional tie condition.
using optional_tie_condition = std::optional<CTieCondition>;
//! Type for the optional extra time configuration.
using optional_extra_time = std::optional<CExtraTime>;
//! Type for the optional penalty shootout configuration.
using optional_penalty_shootout_configuration = std::optional<CPenaltyShootoutConfiguration>;

} // CPenaltyShootoutConfigurationTypes namespace

} // futsim::football namespace