#pragma once

#include "IJsonable.h"

#include "football/CTeam.h"
#include "football/CStadium.h"

namespace futsim::football
{

class CMatch : public IJsonable
{
	using json = IJsonableTypes::json;
	using name_type = CTeamTypes::name_type;

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