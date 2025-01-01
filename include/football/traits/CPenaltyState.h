#pragma once

#include "traits/json.h"

#include "football/traits/CChanceState.h"

#include <string_view>

namespace futsim
{

namespace football
{
class CPenaltyState;
}

template <> struct json_traits<football::CPenaltyState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Penalty state";
	//! JSON key for the \copybrief football::CPenaltyState::mOutcome
	static inline constexpr std::string_view OUTCOME_KEY = json_traits<football::CChanceState>::OUTCOME_KEY;
	//! JSON key for the \copybrief football::CPenaltyState::mShooter
	static inline constexpr std::string_view SHOOTER_KEY = json_traits<football::CChanceState>::ACTOR<football::E_PLAYER_SKILL::Sh>;
	//! JSON key for the \copybrief football::CPenaltyState::mStopper
	static inline constexpr std::string_view STOPPER_KEY = json_traits<football::CChanceState>::ACTOR<football::E_PLAYER_SKILL::St>;
};

} // futsim namespace
