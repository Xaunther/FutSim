#pragma once

#include "IJsonable.h"

#include "football/types/CDrawConfiguration.h"
#include "football/types/CChancesDrawConfiguration.h"
#include "CEnumDistribution.h"

namespace futsim
{

namespace football
{

/**
 * @brief Class that configures the draws of the different chances.
*/
class CChancesDrawConfiguration : public IJsonable
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
		const stat& aAverageChances = DEFAULT_AVERAGE_CHANCES,
		const stat& aAverageCornerKicks = DEFAULT_AVERAGE_CORNER_KICKS,
		const stat& aAverage1vs1GKs = DEFAULT_AVERAGE_1VS1_GKS,
		const stat& aAverage1vs1DFs = DEFAULT_AVERAGE_1VS1_DFS,
		const stat& aAverageNearShots = DEFAULT_AVERAGE_NEAR_SHOTS,
		const stat& aAverageSetPieces = DEFAULT_AVERAGE_SET_PIECES,
		const stat& aAveragePenalties = DEFAULT_AVERAGE_PENALTIES,
		const stat& aAverageDirectFreeKicks = DEFAULT_AVERAGE_DIRECT_FREE_KICKS
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

	//! JSON key for the \copybrief mAverageChances
	static inline constexpr std::string_view JSON_AVERAGE_CHANCES = "Average chances";
	//! JSON key for the \copybrief mAverageCornerKicks
	static inline constexpr std::string_view JSON_AVERAGE_CORNER_KICKS = "Average corner kicks";
	//! JSON key for the \copybrief mAverage1vs1GKs
	static inline constexpr std::string_view JSON_AVERAGE_1VS1_GKS = "Average 1 on 1 vs GK chances";
	//! JSON key for the \copybrief mAverage1vs1DFs
	static inline constexpr std::string_view JSON_AVERAGE_1VS1_DFS = "Average 1 on 1 vs DF chances";
	//! JSON key for the \copybrief mAverageNearShots
	static inline constexpr std::string_view JSON_AVERAGE_NEAR_SHOTS = "Average near shots";
	//! JSON key for the \copybrief mAverageSetPieces
	static inline constexpr std::string_view JSON_AVERAGE_SET_PIECES = "Average set pieces";
	//! JSON key for the \copybrief mAveragePenalties
	static inline constexpr std::string_view JSON_AVERAGE_PENALTIES = "Average penalties";
	//! JSON key for the \copybrief mAverageDirectFreeKicks
	static inline constexpr std::string_view JSON_AVERAGE_DIRECT_FREE_KICKS = "Average direct free kicks";

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

	//! Set piece type distribution parameters.
	set_piece_type_draw_distribution::param_type mSetPieceTypeDistributionParameters;
};

} // football namespace

template <> struct json_traits<football::CChancesDrawConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Chances draw configuration";
};

} // futsim namespace