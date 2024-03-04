#pragma once

#include "IJsonable.h"

#include "football/CFoulDrawConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that configures the foul severity draw.
*/
class CFoulDrawConfiguration : public IJsonable
{
protected:
	using stat = CFoulDrawConfigurationTypes::stat;

public:
	/**
	 * @brief Member constructor.
	 * @param aAverageFouls \ref mAverageFouls
	 * @param aAverageYellowCards \ref mAverageYellowCards
	 * @param aAverageRedCards \ref mAverageRedCards
	*/
	explicit CFoulDrawConfiguration(
		const stat& aAverageFouls = DEFAULT_AVERAGE_FOULS,
		const stat& aAverageYellowCards = DEFAULT_AVERAGE_YELLOW_CARDS,
		const stat& aAverageRedCards = DEFAULT_AVERAGE_RED_CARDS
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CFoulDrawConfiguration( const json& aJSON );

	//! Retrieves the \copybrief mAverageFouls
	const stat& GetAverageFouls() const noexcept;

	//! Retrieves the \copybrief mAverageYellowCards
	const stat& GetAverageYellowCards() const noexcept;

	//! Retrieves the \copybrief mAverageRedCards
	const stat& GetAverageRedCards() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Foul draw configuration";
	//! JSON key for the \copybrief mAverageFouls
	static inline constexpr std::string_view JSON_AVERAGE_FOULS = "Average fouls";
	//! JSON key for the \copybrief mAverageYellowCards
	static inline constexpr std::string_view JSON_AVERAGE_YELLOW_CARDS = "Average yellow cards";
	//! JSON key for the \copybrief mAverageRedCards
	static inline constexpr std::string_view JSON_AVERAGE_RED_CARDS = "Average red cards";

	//! Default \copybrief mAverageFouls
	static inline constexpr stat DEFAULT_AVERAGE_FOULS = stat{ 8195 } / 380;
	//! Default \copybrief mAverageYellowCards
	static inline constexpr stat DEFAULT_AVERAGE_YELLOW_CARDS = stat{ 1375 } / 380;
	//! Default \copybrief mAverageRedCards
	static inline constexpr stat DEFAULT_AVERAGE_RED_CARDS = stat{ 31 } / 380;

private:
	//! Average number of fouls per 90 minutes.
	stat mAverageFouls;
	//! Average number of yellow cards per 90 minutes.
	stat mAverageYellowCards;
	//! Average number of red cards per 90 minutes.
	stat mAverageRedCards;
};

} // futsim namespace