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

public:
	/**
	 * @brief Member constructor.
	 * @param aPlayTime \ref mPlayTime
	 * @param aBenchedPlayersCount \ref mBenchedPlayersCount
	 * @param aApplyAmbientFactor \ref mApplyAmbientFactor
	 * @param aTieCondition \ref mTieCondition
	 * @param aExtraTime \ref mExtraTime
	 * @param aPenaltyShootoutConfiguration \ref mPenaltyShootoutConfiguration
	*/
	explicit CMatchConfiguration(
		const CPlayTime& aPlayTime = CPlayTime{},
		const benched_count& aBenchedPlayersCount = 9,
		const bool aApplyAmbientFactor = true,
		const optional_tie_condition& aTieCondition = {},
		const optional_extra_time& aExtraTime = {},
		const optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration = {} );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CMatchConfiguration( const json& aJSON );

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Match configuration";
	//! JSON key for the \copybrief mBenchedPlayersCount
	static inline constexpr std::string_view JSON_BENCHED_PLAYERS = "Benched players";
	//! JSON key for the \copybrief mApplyAmbientFactor
	static inline constexpr std::string_view JSON_APPLY_AMBIENT_FACTOR = "Apply ambient factor";

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