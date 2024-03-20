#pragma once

#include "IJsonable.h"

#include "football/CLineup.h"
#include "football/CTacticConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that defines a team strategy.
*/
class CTeamStrategy : public IJsonable
{
protected:
	using id = CTacticConfigurationTypes::id;

public:
	/**
	 * @brief Member constructor.
	 * @param aTacticID \ref mTacticID
	 * @param aLineup \ref mLineup
	*/
	explicit CTeamStrategy(
		const std::string_view aTacticID,
		const CLineup& aLineup
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CTeamStrategy( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mTacticID
	std::string_view GetTacticID() const noexcept;

	//! Retrieves the \copybrief mLineup
	const CLineup& GetLineup() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Team strategy";
	//! JSON key for the \copybrief mTacticID
	static inline constexpr std::string_view JSON_TACTIC = "Tactic";

private:
	//! Used tactic ID.
	id mTacticID;
	//! Lineup.
	CLineup mLineup;
};

} // futsim::football namespace