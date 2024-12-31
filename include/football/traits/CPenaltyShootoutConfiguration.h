#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include "football/EPenaltySequence.h"
#include "football/types/CPenaltyShootoutConfiguration.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPenaltyShootoutConfiguration;
}

template <> struct default_traits<football::CPenaltyShootoutConfiguration>
{
protected:
	using penalty_count = football::types::CPenaltyShootoutConfiguration::penalty_count;
public:
	//! Default \copybrief football::CPenaltyShootoutConfiguration::mPenaltySequence
	static inline constexpr football::E_PENALTY_SEQUENCE PENALTY_SEQUENCE = football::E_PENALTY_SEQUENCE::AB;
	//! Default \copybrief football::CPenaltyShootoutConfiguration::mMinPenaltyCount
	static inline constexpr penalty_count PENALTY_COUNT = 5;
};

template <> struct json_traits<football::CPenaltyShootoutConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Penalty shootout configuration";
	//! JSON key for the \copybrief football::CPenaltyShootoutConfiguration::mPenaltySequence
	static inline constexpr std::string_view SEQUENCE_KEY = "Sequence";
	//! JSON key for the \copybrief football::CPenaltyShootoutConfiguration::mMinPenaltyCount
	static inline constexpr std::string_view MIN_PENALTY_COUNT_KEY = "Min penalty count";
};

} // futsim namespace
