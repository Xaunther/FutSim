#pragma once

#include "football/CPeriodStates.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a series of extra time periods.
 * @details The periods have the same play policy and alternate the team that kicks off.
*/
class CExtraTimePeriodStates : public CPeriodStates
{
};

} // futsim::football namespace