#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include <string_view>

#include "football/types/CDrawConfiguration.h"

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

} // futsim namespace
