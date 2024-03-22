#pragma once

#include "IJsonable.h"

#include "football/CTeam.h"
#include "football/CStadium.h"

namespace futsim::football
{

class CTeamStrategy;

/**
 * @brief Class that defines a football match.
*/
class CMatch : public IJsonable
{
protected:
	using name_type = types::CTeam::name_type;

public:
	/**
	 * @brief Member constructor.
	 * @param aHomeTeam \ref mHomeTeam
	 * @param aAwayTeam \ref mAwayTeam
	 * @param aStadium \ref mStadium
	 * @param aReferee \ref mReferee
	 * @pre The referee name cannot be empty.
	*/
	explicit CMatch(
		const CTeam& aHomeTeam,
		const CTeam& aAwayTeam,
		const CStadium& aStadium,
		const std::string_view aReferee );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CMatch( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mHomeTeam
	const CTeam& GetHomeTeam() const noexcept;

	//! Retrieves the \copybrief mAwayTeam
	const CTeam& GetAwayTeam() const noexcept;

	//! Retrieves the \copybrief mStadium
	const CStadium& GetStadium() const noexcept;

	//! Retrieves the \copybrief mReferee
	std::string_view GetReferee() const noexcept;

	/**
	 * @brief Checks the validity of a team strategy according to this match definition.
	 * @param aTeamStrategy Team strategy to check.
	*/
	template <bool tHomeTeam> const CTeamStrategy& CheckTeamStrategy( const CTeamStrategy& aTeamStrategy ) const;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Match";
	//! JSON key for the \copybrief mHomeTeam
	static inline constexpr std::string_view JSON_HOME_TEAM = "Home team";
	//! JSON key for the \copybrief mAwayTeam
	static inline constexpr std::string_view JSON_AWAY_TEAM = "Away team";
	//! JSON key for the \copybrief mReferee
	static inline constexpr std::string_view JSON_REFEREE = "Referee";

private:
	//! Home team.
	CTeam mHomeTeam;
	//! Away team.
	CTeam mAwayTeam;
	//! Stadium that hosts the match.
	CStadium mStadium;
	//! Name of the referee for the match.
	name_type mReferee;
};

} // futsim::football namespace