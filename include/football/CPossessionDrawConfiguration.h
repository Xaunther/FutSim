#pragma once

#include "IJsonable.h"

#include "CPossessionDrawConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that configures the possession draw.
*/
class CPossessionDrawConfiguration : public IJsonable
{
protected:
	using probability = CPossessionDrawConfigurationTypes::probability;

public:
	/**
	 * @brief Member constructor.
	 * @param aKeepPossessionProbability \ref mKeepPossessionProbability
	*/
	explicit CPossessionDrawConfiguration(
		const probability& aKeepPossessionProbability );

	//! Retrieves the \copybrief mKeepPossessionProbability
	const probability& GetKeepPossessionProbability() const noexcept;

private:
	//! Center probability to keep possession.
	probability mKeepPossessionProbability;
};

} // futsim namespace