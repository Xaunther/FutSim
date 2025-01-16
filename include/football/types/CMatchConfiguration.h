#pragma once

#include <optional>

namespace futsim::football
{

class CExtraTime;
class CPenaltyShootoutConfiguration;
class CTieCondition;

namespace types::CMatchConfiguration
{

//! Type for the optional tie condition.
using optional_tie_condition = std::optional<football::CTieCondition>;
//! Type for the optional extra time configuration.
using optional_extra_time = std::optional<CExtraTime>;
//! Type for the optional penalty shootout configuration.
using optional_penalty_shootout_configuration = std::optional<football::CPenaltyShootoutConfiguration>;

} // types::CMatchConfiguration namespace

} // futsim::football namespace
