#pragma once

#include "IJsonable.h"

#include "football/CTeam.h"
#include "football/CStadium.h"

namespace futsim::football
{

class CMatch : public IJsonable
{
	using name_type = CTeamTypes::name_type;

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