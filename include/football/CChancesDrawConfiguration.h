#pragma once

#include "IJsonable.h"

#include "football/CChancesDrawConfigurationTypes.h"
namespace futsim::football
{

/**
 * @brief Class that configures the draws of the different chances.
*/
class CChancesDrawConfiguration : public IJsonable
{
protected:
	using stat = CChancesDrawConfigurationTypes::stat;

public:
	//! Retrieves the \copybrief mAverageChances
	const stat& GetAverageChances() const noexcept;

	//! Retrieves the \copybrief mAverageCornerKicks
	const stat& GetAverageCornerKicks() const noexcept;

	//! Retrieves the \copybrief mAverage1vs1GKs
	const stat& GetAverage1vs1GKs() const noexcept;

	//! Retrieves the \copybrief mAverage1vs1DFs
	const stat& GetAverage1vs1DFs() const noexcept;

	//! Retrieves the \copybrief mAverageNearShots
	const stat& GetAverageNearShots() const noexcept;

	//! Retrieves the \copybrief mAverageSetPieces
	const stat& GetAverageSetPieces() const noexcept;

	//! Retrieves the \copybrief mAveragePenalties
	const stat& GetAveragePenalties() const noexcept;

	//! Retrieves the \copybrief mAverageDirectFreeKicks
	const stat& GetAverageDirectFreeKicks() const noexcept;

private:
	//! Average number of chances per 90 minutes.
	stat mAverageChances;

	//! Average number of corner kicks per 90 minutes.
	stat mAverageCornerKicks;
	//! Average number of 1 on 1 vs GK chances per 90 minutes.
	stat mAverage1vs1GKs;
	//! Average number of 1 on 1 vs DF chances per 90 minutes.
	stat mAverage1vs1DFs;
	//! Average number of near shots per 90 minutes.
	stat mAverageNearShots;

	//! Average number of set pieces per 90 minutes.
	stat mAverageSetPieces;
	//! Average number of penalties per 90 minutes.
	stat mAveragePenalties;
	//! Average number of direct free kicks per 90 minutes.
	stat mAverageDirectFreeKicks;
};

} // futsim namespace