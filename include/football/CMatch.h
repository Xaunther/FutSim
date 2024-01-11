#pragma once

#include "IJsonable.h"

#include "football/CTeam.h"
#include "football/CStadium.h"

namespace futsim::football
{

class CMatch : public IJsonable
{
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