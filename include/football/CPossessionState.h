#pragma once

#include "IJsonable.h"

#include "football/CPossessionStateTypes.h"

#include "football/CPossessionDrawConfigurationTypes.h"
#include "CPersonTypes.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a possession draw.
*/
class CPossessionState : public IJsonable
{
protected:
	using optional_name = std::optional<CPersonTypes::name_type>;
	using E_POSSESSION_DRAW_OUTCOME = CPossessionDrawConfigurationTypes::E_POSSESSION_DRAW_OUTCOME;

public:
	//! Retrieves the \copybrief mOutcome
	const E_POSSESSION_DRAW_OUTCOME& GetOutcome() const noexcept;

	//! Retrieves the \copybrief mTackler
	const optional_name& GetTackler() const noexcept;

	//! Retrieves the \copybrief mPasser
	const optional_name& GetPasser() const noexcept;

private:
	//! Possession draw outcome.
	E_POSSESSION_DRAW_OUTCOME mOutcome;
	//! Player that made the tackle, if any.
	optional_name mTackler;
	//! Player that made the pass, if any.
	optional_name mPasser;
};

} // futsim::football namespace