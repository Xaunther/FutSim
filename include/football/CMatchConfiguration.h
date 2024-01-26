#pragma once

#include "IJsonable.h"

#include "football/CExtraTime.h"
#include "football/CMatchConfigurationTypes.h"
#include "football/CPenaltyShootoutConfiguration.h"
#include "football/CPlayTime.h"
#include "football/CTieCondition.h"

namespace futsim::football
{

/**
 * @brief Class that configures a football match.
*/
class CMatchConfiguration : public IJsonable
{
protected:
	using benched_count = CMatchConfigurationTypes::benched_count;
	using optional_tie_condition = CMatchConfigurationTypes::optional_tie_condition;
	using optional_extra_time = CMatchConfigurationTypes::optional_extra_time;
	using optional_penalty_shootout_configuration = CMatchConfigurationTypes::optional_penalty_shootout_configuration;

private:
	//! Play time configuration.
	CPlayTime mPlayTime;
	//! Number of players on the bench. Empty for unlimited number.
	benched_count mBenchedPlayersCount;
	//! Whether the ambient factor applies to the home team. Useful to play on neutral grounds.
	bool mApplyAmbientFactor;
	//! Tie condition.
	optional_tie_condition mTieCondition;
	//! Extra time configuration.
	optional_extra_time mExtraTime;
	//! Penalty shootout configuration.
	optional_penalty_shootout_configuration mPenaltyShootoutConfiguration;
};

} // futsim namespace