#pragma once

#include "football/types/CStadium.h"

#include <random>
#include <string>
#include <vector>

/**
 * @brief Types defined for \ref CTeam.
*/
namespace futsim::football
{

class CPlayer;

namespace types::CTeam
{

//! Type for a name.
using name_type = std::string;
//! Type for the roster of players.
using players = std::vector<CPlayer>;
//! Type for the support factor.
using support_factor = types::CStadium::ambient_factor;
//! Type for the attendance.
using attendance = unsigned int;
//! Type for the attendance distribution.
using attendance_distribution = std::normal_distribution<>;

} // types::CTeam namespace

} // futsim::football namespace