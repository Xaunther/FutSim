#pragma once

#include "IJsonable.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of series of match periods.
 * @details The periods have the same play policy and alternate the team that kicks off.
*/
class CPeriodStates : public IJsonable
{
};

} // futsim::football namespace