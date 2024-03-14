#pragma once

#include "IJsonable.h"

#include "football/CDrawConfiguration.h"
#include "football/CExtraTime.h"
#include "football/CLineupConfiguration.h"
#include "football/CMatchConfigurationTypes.h"
#include "football/CPenaltyShootoutConfiguration.h"
#include "football/CPlayTime.h"
#include "football/CTacticsConfiguration.h"
#include "football/CTieCondition.h"

namespace futsim::football
{

class CMatchStrategy;

/**
 * @brief Class that configures a football match.
*/
class CMatchConfiguration : public IJsonable
{
protected:
	using optional_tie_condition = CMatchConfigurationTypes::optional_tie_condition;
	using optional_extra_time = CMatchConfigurationTypes::optional_extra_time;
	using optional_penalty_shootout_configuration = CMatchConfigurationTypes::optional_penalty_shootout_configuration;

public:
	/**
	 * @brief Member constructor.
	 * @param aPlayTime \ref mPlayTime
	 * @param aLineupConfiguration \ref mLineupConfiguration
	 * @param aApplyAmbientFactor \ref mApplyAmbientFactor
	 * @param aTacticsConfiguration \ref mTacticsConfiguration
	 * @param aTieCondition \ref mTieCondition
	 * @param aExtraTime \ref mExtraTime
	 * @param aPenaltyShootoutConfiguration \ref mPenaltyShootoutConfiguration
	 * @param aDrawConfiguration \ref mDrawConfiguration
	*/
	explicit CMatchConfiguration(
		const CPlayTime& aPlayTime = CPlayTime{},
		const CLineupConfiguration& aLineupConfiguration = CLineupConfiguration{},
		const bool aApplyAmbientFactor = DEFAULT_APPLY_AMBIENT_FACTOR,
		const CTacticsConfiguration& aTacticsConfiguration = CTacticsConfiguration{},
		const optional_tie_condition& aTieCondition = {},
		const optional_extra_time& aExtraTime = {},
		const optional_penalty_shootout_configuration& aPenaltyShootoutConfiguration = {},
		const CDrawConfiguration& aDrawConfiguration = CDrawConfiguration{} );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CMatchConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPlayTime
	const CPlayTime& GetPlayTime() const noexcept;

	//! Retrieves the \copybrief mLineupConfiguration
	const CLineupConfiguration& GetLineupConfiguration() const noexcept;

	//! Retrieves the \copybrief mApplyAmbientFactor
	bool AppliesAmbientFactor() const noexcept;

	//! Retrieves the \copybrief mTacticsConfiguration
	const CTacticsConfiguration& GetTacticsConfiguration() const noexcept;

	//! Retrieves the \copybrief mTieCondition
	const optional_tie_condition& GetTieCondition() const noexcept;

	//! Retrieves the \copybrief mExtraTime
	const optional_extra_time& GetExtraTime() const noexcept;

	//! Retrieves the \copybrief mPenaltyShootoutConfiguration
	const optional_penalty_shootout_configuration& GetPenaltyShootoutConfiguration() const noexcept;

	//! Retrieves the \copybrief mDrawConfiguration
	const CDrawConfiguration& GetDrawConfiguration() const noexcept;

	/**
	 * @brief Checks the validity of a match strategy according to this configuration.
	 * @param aMatchStrategy Match strategy to check.
	*/
	const CMatchStrategy& CheckMatchStrategy( const CMatchStrategy& aMatchStrategy ) const;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Match configuration";
	//! JSON key for the \copybrief mApplyAmbientFactor
	static inline constexpr std::string_view JSON_APPLY_AMBIENT_FACTOR = "Apply ambient factor";

	//! Default \copybrief mApplyAmbientFactor
	static inline constexpr bool DEFAULT_APPLY_AMBIENT_FACTOR = true;

private:
	//! Play time configuration.
	CPlayTime mPlayTime;
	//! Lineup configuration.
	CLineupConfiguration mLineupConfiguration;
	//! Whether the ambient factor applies to the home team. Useful to play on neutral grounds.
	bool mApplyAmbientFactor;
	//! Tactics configuration.
	CTacticsConfiguration mTacticsConfiguration;
	//! Tie condition.
	optional_tie_condition mTieCondition;
	//! Extra time configuration.
	optional_extra_time mExtraTime;
	//! Penalty shootout configuration.
	optional_penalty_shootout_configuration mPenaltyShootoutConfiguration;

	//! Draw configuration
	CDrawConfiguration mDrawConfiguration;
};

} // futsim namespace