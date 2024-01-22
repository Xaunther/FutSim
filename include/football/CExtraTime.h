#pragma once

#include "football/CPlayTime.h"

#include "football/EGoalRule.h"

namespace futsim::football
{

/**
 * @brief Class that defines an extra time phase of a football match.
*/
class CExtraTime : public CPlayTime
{
	//! Goal rule.
	E_GOAL_RULE mGoalRule;
};

} // futsim::football namespace