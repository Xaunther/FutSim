#pragma once

#include "IJsonable.h"
#include "football/traits/CPossessionDrawConfiguration.h"

#include "football/types/CDrawConfiguration.h"
#include "football/types/CPossessionDrawConfiguration.h"

namespace futsim::football
{

/**
 * @brief Class that configures the possession draw.
*/
class CPossessionDrawConfiguration : public IJsonable, protected default_traits<CPossessionDrawConfiguration>, protected json_traits<CPossessionDrawConfiguration>
{
protected:
	using probability = types::CDrawConfiguration::probability;

public:
	/**
	 * @brief Member constructor.
	 * @param aKeepPossessionProbability \ref mKeepPossessionProbability
	*/
	explicit CPossessionDrawConfiguration(
		const probability& aKeepPossessionProbability = KEEP_POSSESSION_PROBABILITY );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPossessionDrawConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mKeepPossessionProbability
	const probability& GetKeepPossessionProbability() const noexcept;

private:
	//! Center probability to keep possession.
	probability mKeepPossessionProbability;
};

} // futsim::football namespace
