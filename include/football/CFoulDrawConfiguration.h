#pragma once

#include "IJsonable.h"
#include "football/traits/CFoulDrawConfiguration.h"

#include "football/types/CDrawConfiguration.h"
#include "football/types/CFoulDrawConfiguration.h"
#include "football/CLineup.h"
#include "CEnumDistribution.h"

namespace futsim::football
{

/**
 * @brief Class that configures the foul severity draw.
*/
class CFoulDrawConfiguration : public IJsonable, protected default_traits<CFoulDrawConfiguration>, protected json_traits<CFoulDrawConfiguration>
{
protected:
	using stat = types::CDrawConfiguration::stat;
	using probability = types::CDrawConfiguration::probability;
	using foul_draw_distribution = types::CFoulDrawConfiguration::foul_draw_distribution;

public:
	/**
	 * @brief Member constructor.
	 * @param aAverageFouls \ref mAverageFouls
	 * @param aAverageYellowCards \ref mAverageYellowCards
	 * @param aAverageRedCards \ref mAverageRedCards
	*/
	explicit CFoulDrawConfiguration(
		const stat& aAverageFouls = AVERAGE_FOULS,
		const stat& aAverageYellowCards = AVERAGE_YELLOW_CARDS,
		const stat& aAverageRedCards = AVERAGE_RED_CARDS
	);

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CFoulDrawConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mAverageFouls
	const stat& GetAverageFouls() const noexcept;

	//! Retrieves the \copybrief mAverageYellowCards
	const stat& GetAverageYellowCards() const noexcept;

	//! Retrieves the \copybrief mAverageRedCards
	const stat& GetAverageRedCards() const noexcept;

	//! Retrieves the \copybrief mFoulProbability
	const probability& GetFoulProbability() const noexcept;

	//! @brief Creates the foul draw distribution.
	foul_draw_distribution CreateFoulDistribution() const noexcept;

	/**
	 * @brief Draws the foul committer from a team lineup.
	 * @details The players in the same position have equal probabilities.
	 * @param aLineup Current team lineup
	 * @param aGenerator RNG to use.
	 * @return A view to the drawn player's name.
	*/
	std::string_view DrawFoulCommitter( const CLineup& aLineup,
		std::uniform_random_bit_generator auto& aGenerator ) const noexcept;

	//! Number of minutes of the matches used to take the data from.
	static inline constexpr unsigned int MATCH_MINUTES = 90;

private:
	//! Average number of fouls per 90 minutes.
	stat mAverageFouls;
	//! Average number of yellow cards per 90 minutes.
	stat mAverageYellowCards;
	//! Average number of red cards per 90 minutes.
	stat mAverageRedCards;

	//! Foul probability.
	probability mFoulProbability;

	//! Foul distribution parameters.
	foul_draw_distribution::param_type mFoulDistributionParameters;
};

std::string_view CFoulDrawConfiguration::DrawFoulCommitter( const CLineup& aLineup,
	std::uniform_random_bit_generator auto& aGenerator ) const noexcept
{
	const auto& players = aLineup.CreatePlayersView<false>();
	return *( players | std::ranges::views::drop( std::uniform_int_distribution<types::CLineup::names::size_type>{
		0, static_cast<types::CLineup::names::size_type>( std::ranges::distance( players ) - 1 ) }( aGenerator ) ) ).begin();
}

} // futsim::football namespace
