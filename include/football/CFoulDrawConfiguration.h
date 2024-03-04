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
	//! Retrieves the \copybrief mAverageFouls
	const stat& GetAverageFouls() const noexcept;

	//! Retrieves the \copybrief mAverageYellowCards
	const stat& GetAverageYellowCards() const noexcept;

	//! Retrieves the \copybrief mAverageRedCards
	const stat& GetAverageRedCards() const noexcept;

private:
	//! Average number of fouls per 90 minutes.
	stat mAverageFouls;
	//! Average number of yellow cards per 90 minutes.
	stat mAverageYellowCards;
	//! Average number of red cards per 90 minutes.
	stat mAverageRedCards;
};

} // futsim namespace