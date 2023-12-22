#pragma once

#include "IJsonable.h"

#include "football/CPlayer.h"
#include "football/CTeamTypes.h"

#include <random>

namespace futsim::football
{

class CTeam : public IJsonable
{
	using name_type = CTeamTypes::name_type;
	using players = CTeamTypes::players;
	using support_factor = CTeamTypes::support_factor;

	//! Team name.
	name_type mName;
	//! 3-letter team abbreviation.
	name_type mAbbreviation;
	//! Manager.
	name_type mManager;
	//! Roster of players.
	players mPlayers;
	//! Support factor that dictates the support the team receives from the fans.
	support_factor mSupportFactor;
	//! Local fan attendance distribution
	std::normal_distribution<> mAttendanceDistribution;
};

} // futsim::football namespace