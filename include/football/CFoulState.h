#pragma once

#include "IJsonable.h"

#include "CPersonTypes.h"
#include "CFoulDrawConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a foul.
*/
class CFoulState : public IJsonable
{
protected:
	using name_type = CPersonTypes::name_type;
	using E_FOUL_DRAW_OUTCOME = CFoulDrawConfigurationTypes::E_FOUL_DRAW_OUTCOME;

public:
	//! Retrieves the \copybrief mCommitter
	std::string_view GetCommitter() const noexcept;

	//! Retrieves the \copybrief mOutcome
	const E_FOUL_DRAW_OUTCOME& GetOutcome() const noexcept;

private:
	//! Player that committed the foul.
	name_type mCommitter;
	//! Foul draw outcome.
	E_FOUL_DRAW_OUTCOME mOutcome;
};

} // futsim::football namespace