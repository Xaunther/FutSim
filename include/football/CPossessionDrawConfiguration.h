#pragma once

#include "IJsonable.h"
#include "traits/default.h"
#include "traits/json.h"

#include "football/types/CDrawConfiguration.h"
#include "football/types/CPossessionDrawConfiguration.h"

namespace futsim
{

namespace football
{
class CPossessionDrawConfiguration;
}

template <> struct default_traits<football::CPossessionDrawConfiguration>
{
protected:
	using probability = football::types::CDrawConfiguration::probability;
public:
	//! Default keep posssession probability.
	static inline constexpr probability KEEP_POSSESSION_PROBABILITY = probability{ 295952 } / 460939;
};

template <> struct json_traits<football::CPossessionDrawConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Possession draw configuration";
	//! JSON key for the \copybrief football::CPossessionDrawConfiguration::mKeepPossessionProbability
	static inline constexpr std::string_view KEEP_POSSESSION_PROBABILITY_KEY = "Keep possession probability";
};

namespace football
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

} // football namespace

} // futsim namespace
