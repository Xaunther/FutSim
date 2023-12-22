#pragma once

#include "football/CStadiumTypes.h"

#include <string>
#include <vector>

/**
 * @brief Types defined for \ref CTeamTypes.
*/
namespace futsim::football
{

class CPlayer;

namespace CTeamTypes
{

//! Type for a name.
using name_type = std::string;
//! Type for the roster of players
using players = std::vector<CPlayer>;
//! Type for the support factor.
using support_factor = CStadiumTypes::ambient_factor;

} // CTeamTypes namespace

} // futsim::football namespace