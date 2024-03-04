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
	/**
	 * @brief Member constructor.
	 * @param aAverageChances \ref mAverageChances
	 * @param aAverageCornerKicks \ref mAverageCornerKicks
	 * @param aAverage1vs1GKs \ref mAverage1vs1GKs
	 * @param aAverage1vs1DFs \ref mAverage1vs1DFs
	 * @param aAverageNearShots \ref mAverageNearShots
	 * @param aAverageSetPieces \ref mAverageSetPieces
	 * @param aAveragePenalties \ref mAveragePenalties
	 * @param aAverageDirectFreeKicks \ref mAverageDirectFreeKicks
	*/
	explicit CChancesDrawConfiguration(
		const stat& aAverageChances = DEFAULT_AVERAGE_CHANCES,
		const stat& aAverageCornerKicks = DEFAULT_AVERAGE_CORNER_KICKS,
		const stat& aAverage1vs1GKs = DEFAULT_AVERAGE_1VS1_GKS,
		const stat& aAverage1vs1DFs = DEFAULT_AVERAGE_1VS1_DFS,
		const stat& aAverageNearShots = DEFAULT_AVERAGE_NEAR_SHOTS,
		const stat& aAverageSetPieces = DEFAULT_AVERAGE_SET_PIECES,
		const stat& aAveragePenalties = DEFAULT_AVERAGE_PENALTIES,
		const stat& aAverageDirectFreeKicks = DEFAULT_AVERAGE_DIRECT_FREE_KICKS
	);

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

	//! Default \copybrief mAverageChances
	static inline constexpr stat DEFAULT_AVERAGE_CHANCES = stat{ 9609 } / 380;
	//! Default \copybrief mAverageCornerKicks
	static inline constexpr stat DEFAULT_AVERAGE_CORNER_KICKS = stat{ 3830 } / 380;
	//! Default \copybrief mAverage1vs1GKs
	static inline constexpr stat DEFAULT_AVERAGE_1VS1_GKS = 2;
	//! Default \copybrief mAverage1vs1DFs
	static inline constexpr stat DEFAULT_AVERAGE_1VS1_DFS = 2.85;
	//! Default \copybrief mAverageNearShots
	static inline constexpr stat DEFAULT_AVERAGE_NEAR_SHOTS = 3;
	//! Default \copybrief mAverageSetPieces
	static inline constexpr stat DEFAULT_AVERAGE_SET_PIECES = stat{ 1545 } / 380;
	//! Default \copybrief mAveragePenalties
	static inline constexpr stat DEFAULT_AVERAGE_PENALTIES = stat{ 104 } / 380;
	//! Default \copybrief mAverageDirectFreeKicks
	static inline constexpr stat DEFAULT_AVERAGE_DIRECT_FREE_KICKS = stat{ 301 } / 380;

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