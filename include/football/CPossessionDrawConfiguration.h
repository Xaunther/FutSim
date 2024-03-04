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

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPossessionDrawConfiguration( const json& aJSON );

	//! Retrieves the \copybrief mKeepPossessionProbability
	const probability& GetKeepPossessionProbability() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Possession draw configuration";
	//! JSON key for the \copybrief mKeepPossessionProbability
	static inline constexpr std::string_view JSON_KEEP_POSSESSION_PROBABILITY = "Keep possession probability";

private:
	//! Center probability to keep possession.
	probability mKeepPossessionProbability;
};

} // futsim namespace