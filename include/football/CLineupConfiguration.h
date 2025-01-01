#pragma once

#include "IJsonable.h"
#include "football/traits/CLineupConfiguration.h"

#include "football/types/CLineupConfiguration.h"

namespace futsim::football
{

class CLineup;

/**
 * @brief Class that configures the lineup rules.
*/
class CLineupConfiguration : public IJsonable, protected default_traits<CLineupConfiguration>, protected json_traits<CLineupConfiguration>
{
protected:
	using optional_player_count = types::CLineupConfiguration::optional_player_count;
	using player_count = types::CLineupConfiguration::player_count;
	using player_count_range = types::CLineupConfiguration::player_count_range;

public:
	/**
	 * @brief Member constructor.
	 * @param aDFRange \ref mDFRange
	 * @param aMFRange \ref mMFRange
	 * @param aFWRange \ref mFWRange
	 * @param aMinPlayerCount \ref mMinPlayerCount
	 * @param aBenchedPlayersCount \ref mBenchedPlayersCount
	*/
	explicit CLineupConfiguration(
		const player_count_range& aDFRange = DF_RANGE,
		const player_count_range& aMFRange = MF_RANGE,
		const player_count_range& aFWRange = FW_RANGE,
		const player_count& aMinPlayerCount = MIN_PLAYERS,
		const optional_player_count& aBenchedPlayersCount = BENCHED_PLAYERS
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CLineupConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mDFRange
	const player_count_range& GetDFRange() const noexcept;

	//! Retrieves the \copybrief mMFRange
	const player_count_range& GetMFRange() const noexcept;

	//! Retrieves the \copybrief mFWRange
	const player_count_range& GetFWRange() const noexcept;

	//! Retrieves the \copybrief mMinPlayerCount
	const player_count& GetMinPlayerCount() const noexcept;

	//! Retrieves the \copybrief mBenchedPlayersCount
	const optional_player_count& GetBenchedPlayersCount() const noexcept;

	/**
	 * @brief Checks the validity of a lineup according to this configuration.
	 * @param aLineup Lineup to check.
	*/
	const CLineup& CheckLineup( const CLineup& aLineup ) const;

private:
	//! Allowed DFs count range.
	player_count_range mDFRange;
	//! Allowed midfielders (DMs+MFs+AMs) count range.
	player_count_range mMFRange;
	//! Allowed FWs count range.
	player_count_range mFWRange;
	//! Minimum number of players.
	player_count mMinPlayerCount;
	//! Number of players on the bench. Empty for unlimited number.
	optional_player_count mBenchedPlayersCount;
};

} // futsim::football namespace
