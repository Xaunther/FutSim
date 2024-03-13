#pragma once

#include "IJsonable.h"

#include "football/CLineup.h"
#include "football/CTacticConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that defines a match strategy
*/
class CMatchStrategy : public IJsonable
{
protected:
	using id = CTacticConfigurationTypes::id;

public:
	/**
	 * @brief Member constructor.
	 * @param aTacticID \ref mTacticID
	 * @param aLineup \ref mLineup
	*/
	explicit CMatchStrategy(
		const id& aTacticID,
		const CLineup& aLineup
	);

	//! Retrieves the \copybrief mTacticID
	const id& GetTacticID() const noexcept;

	//! Retrieves the \copybrief mLineup
	const CLineup& GetLineup() const noexcept;

private:
	//! Used tactic ID.
	id mTacticID;
	//! Lineup.
	CLineup mLineup;
};

} // futsim::football namespace