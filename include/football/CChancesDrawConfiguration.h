#pragma once

#include "IJsonable.h"
#include "football/traits/CChancesDrawConfiguration.h"

#include "football/types/CDrawConfiguration.h"
#include "football/types/CChancesDrawConfiguration.h"
#include "CEnumDistribution.h"

namespace futsim::football
{

/**
 * @brief Class that configures the draws of the different chances.
*/
class CChancesDrawConfiguration : public IJsonable, protected default_traits<CChancesDrawConfiguration>, json_traits<CChancesDrawConfiguration>
{
protected:
	using stat = types::CDrawConfiguration::stat;
	using set_piece_type_draw_distribution = types::CChancesDrawConfiguration::set_piece_type_draw_distribution;

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
		const stat& aAverageChances = AVERAGE_CHANCES,
		const stat& aAverageCornerKicks = AVERAGE_CORNER_KICKS,
		const stat& aAverage1vs1GKs = AVERAGE_1VS1_GKS,
		const stat& aAverage1vs1DFs = AVERAGE_1VS1_DFS,
		const stat& aAverageNearShots = AVERAGE_NEAR_SHOTS,
		const stat& aAverageSetPieces = AVERAGE_SET_PIECES,
		const stat& aAveragePenalties = AVERAGE_PENALTIES,
		const stat& aAverageDirectFreeKicks = AVERAGE_DIRECT_FREE_KICKS
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CChancesDrawConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

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


	//! Creates the set piece type draw distribution.
	set_piece_type_draw_distribution CreateSetPieceTypeDistribution() const noexcept;

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

	//! Set piece type distribution parameters.
	set_piece_type_draw_distribution::param_type mSetPieceTypeDistributionParameters;
};

} // futsim::football namespace
