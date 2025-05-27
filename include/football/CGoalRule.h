#pragma once

#include "IJsonable.h"
#include "football/traits/CGoalRule.h"

namespace futsim::football
{

/**
 * @brief Class that represents a goal rule.
*/
class CGoalRule : public IJsonable, protected json_traits<CGoalRule>
{

};

} // futsim::football namespace
