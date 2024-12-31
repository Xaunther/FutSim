#pragma once

#include "IJsonable.h"
#include "traits/json.h"

#include "types/CMatchState.h"

#include "football/CPeriodStates.h"
#include "football/CPenaltyShootoutState.h"
#include "football/CExtraTimePeriodPlayPolicy.h"
#include "football/CExtraTimePeriodPolicy.h"

#include "ExceptionUtils.h"

namespace futsim
{

namespace football
{
class CMatchState;
}

template <> struct json_traits<football::CMatchState>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Match state";
	//! JSON key for the \copybrief football::CMatchState::mMandatoryPlayTimeState
	static inline constexpr std::string_view MANDATORY_PERIOD_STATES_KEY = "Mandatory time period states";
	//! JSON key for the \copybrief football::CMatchState::mExtraTimeState
	static inline constexpr std::string_view EXTRA_PERIOD_STATES_KEY = "Extra time period states";
};

namespace football
{

/**
 * @brief Class that represents the state of a match.
*/
class CMatchState : public IJsonable, protected json_traits<CMatchState>
{
protected:
	using optional_period_states = types::CMatchState::optional_period_states;
	using optional_penalty_shootout_state = types::CMatchState::optional_penalty_shootout_state;

public:
	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aHomeTeamStrategy Current match strategy for the home team.
	 * @param aAwayTeamStrategy Current match strategy for the away team.
	 * @param aGenerator RNG to use.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	explicit CMatchState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		std::uniform_random_bit_generator auto& aGenerator
	);

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mMandatoryPlayTimeState
	const CPeriodStates& GetMandatoryPlayTimeState() const noexcept;

	//! Retrieves the \copybrief mExtraTimeState
	const optional_period_states& GetExtraTimeState() const noexcept;

	//! Retrieves the \copybrief mPenaltyShootoutState
	const optional_penalty_shootout_state& GetPenaltyShootoutState() const noexcept;

private:
	//! Mandatory play time of the match.
	CPeriodStates mMandatoryPlayTimeState;
	//! Optional extra time state.
	optional_period_states mExtraTimeState;
	//! Optional penalty shootout state.
	optional_penalty_shootout_state mPenaltyShootoutState;
};

CMatchState::CMatchState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aHomeTeamStrategy,
	const CTeamStrategy& aAwayTeamStrategy,
	std::uniform_random_bit_generator auto& aGenerator
) try :
	mMandatoryPlayTimeState( aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy, aGenerator )
{
	if( aMatchConfiguration.GetTieCondition() )
	{
		const auto& tieCondition = *aMatchConfiguration.GetTieCondition();
		auto homeTeamGoals = mMandatoryPlayTimeState.CountScoredGoals( true );
		auto awayTeamGoals = mMandatoryPlayTimeState.CountScoredGoals( false );
		if( tieCondition( homeTeamGoals, awayTeamGoals ) )
		{
			if( aMatchConfiguration.GetExtraTime() )
			{
				const auto& extraTime = *aMatchConfiguration.GetExtraTime();
				switch( extraTime.GetGoalRule() )
				{
				case E_GOAL_RULE::SILVER_GOAL:
					mExtraTimeState = CPeriodStates{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy, aGenerator,
						CExtraTimePeriodPlayPolicy<E_GOAL_RULE::SILVER_GOAL>{}, CExtraTimePeriodPolicy<E_GOAL_RULE::SILVER_GOAL>{} };
					break;
				case E_GOAL_RULE::GOLDEN_GOAL:
					mExtraTimeState = CPeriodStates{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy, aGenerator,
						CExtraTimePeriodPlayPolicy<E_GOAL_RULE::GOLDEN_GOAL>{}, CExtraTimePeriodPolicy<E_GOAL_RULE::GOLDEN_GOAL>{} };
					break;
				default:
					mExtraTimeState = CPeriodStates{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy, aGenerator,
						CExtraTimePeriodPlayPolicy<E_GOAL_RULE::NO>{}, CExtraTimePeriodPolicy<E_GOAL_RULE::NO>{} };
					break;
				}
				homeTeamGoals += mExtraTimeState->CountScoredGoals( true );
				awayTeamGoals += mExtraTimeState->CountScoredGoals( false );

				if( tieCondition( homeTeamGoals, awayTeamGoals ) )
					mPenaltyShootoutState = CPenaltyShootoutState{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy,
					std::bernoulli_distribution{}( aGenerator ), aGenerator };
			}
			else
				mPenaltyShootoutState = CPenaltyShootoutState{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy,
				std::bernoulli_distribution{}( aGenerator ), aGenerator };
		}
	}
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the match state." )

} // football namespace

} // futsim namespace
