#pragma once

#include "IJsonable.h"

#include "football/types/CDrawConfiguration.h"
#include "football/types/CPossessionDrawConfiguration.h"

namespace futsim
{

namespace football
{

/**
 * @brief Class that configures the possession draw.
*/
class CPossessionDrawConfiguration : public IJsonable
{
protected:
	using probability = types::CDrawConfiguration::probability;

public:
	/**
	 * @brief Member constructor.
	 * @param aKeepPossessionProbability \ref mKeepPossessionProbability
	*/
	explicit CPossessionDrawConfiguration(
		const probability& aKeepPossessionProbability = DEFAULT_KEEP_POSSESSION_PROBABILITY );

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

	//! JSON key for the \copybrief mKeepPossessionProbability
	static inline constexpr std::string_view JSON_KEEP_POSSESSION_PROBABILITY = "Keep possession probability";
	//! Default keep posssession probability.
	static inline constexpr probability DEFAULT_KEEP_POSSESSION_PROBABILITY = probability{ 295952 } / 460939;

private:
	//! Center probability to keep possession.
	probability mKeepPossessionProbability;
};

} // football namespace

template <> struct json_traits<football::CPossessionDrawConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Possession draw configuration";
};

} // futsim namespace