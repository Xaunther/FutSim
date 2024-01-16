#pragma once

#include "../CPlayTime.h"

#include "football/CPlayTimeTypes.h"

namespace futsim::football
{

/**
 * @brief Class that defines a play time phase of a football match.
*/
class CPlayTime : public futsim::CPlayTime
{
	using subs_count = CPlayTimeTypes::subs_count;

	//! Number of available subs.
	subs_count mAvailableSubs;
};

} // futsim::football namespace