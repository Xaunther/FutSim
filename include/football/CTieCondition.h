#pragma once

#include "IJsonable.h"

#include <optional>

namespace futsim::football
{

/**
 * @brief Class that defines a tie condition for a match.
 * @details A match resulting in a tie condition should go on to undo the tie.
*/
class CTieCondition : public IJsonable
{
	//! Home team goal lead that results in a tie.
	int mHomeTeamLead;
	//! Number of goals of the home team that results in a tie.
	std::optional<unsigned int> mHomeTeamGoals;
};

} // futsim::football namespace