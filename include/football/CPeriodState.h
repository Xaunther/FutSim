#pragma once

#include "IJsonable.h"

#include "types/CPeriodState.h"

#include "football/CPlayState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a match period.
*/
class CPeriodState : public IJsonable
{
protected:
	using plays = types::CPeriodState::plays;

public:
	const plays& GetPlays() const noexcept;

private:
	//! Plays of the period.
	plays mPlays;
};

} // futsim::football namespace