#pragma once

#include "IJsonable.h"

#include "football/types/CPeriodStates.h"

#include "football/CPeriodState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of series of match periods.
 * @details The periods have the same play policy and alternate the team that kicks off.
*/
class CPeriodStates : public IJsonable
{
protected:
	using period_states = types::CPeriodStates::period_states;
	using goal_count = types::CTieCondition::goal_count;

public:
	/**
	 * @brief Default policy functor for the periods.
	 * @details All configured periods are played.
	*/
	//! 
	struct SDefaultPeriodPolicy
	{
		/**
		 * @brief Returns whether another period must be played.
		 * @param aPeriodStates Current period states.
		 * @param aMatchConfiguration Match configuration.
		*/
		bool operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const;
	};

	/**
	 * @brief Default policy functor for the periods of extra time.
	 * @details All configured extra time periods are played.
	*/
	struct SDefaultExtraTimePeriodPolicy
	{
		/**
		 * @brief Returns whether another period must be played.
		 * @param aPeriodStates Current period states.
		 * @param aMatchConfiguration Match configuration.
		*/
		bool operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const;

		/**
		 * @brief Checks that the match configuration can produce extra time periods.
		 * @param aMatchConfiguration Match configuration.
		*/
		static const CMatchConfiguration& CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration );
	};

	/**
	 * @brief Default policy functor for the periods of extra time with silver goal.
	 * @details No more extra time periods are played when the tie condition is no longer satisfied after a period.
	*/
	struct SSilverGoalPeriodPolicy : public SDefaultExtraTimePeriodPolicy
	{
		/**
		 * @brief Returns whether another period must be played.
		 * @param aPeriodStates Current period states.
		 * @param aMatchConfiguration Match configuration.
		*/
		bool operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const;
	};

	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aHomeTeamStrategy Current match strategy for the home team.
	 * @param aAwayTeamStrategy Current match strategy for the away team.
	 * @param aGenerator RNG to use.
	 * @param aPeriodPlayPolicy Period play policy.
	 * @param aPeriodPolicy Period policy.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	template <typename T = CPeriodState::SDefaultPeriodPlayPolicy, typename U = SDefaultPeriodPolicy>
		requires types::CPeriodState::period_play_policy<T>&& types::CPeriodStates::period_policy<U>
	explicit CPeriodStates(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		std::uniform_random_bit_generator auto& aGenerator,
		const T& aPeriodPlayPolicy = T{},
		const U& aPeriodPolicy = U{}
	);

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mStates
	const period_states& GetStates() const noexcept;

	/**
	 * @brief Counts the goals scored by the given team.
	 * @param aHomeTeam Whether to count the home team goals.
	*/
	goal_count CountScoredGoals( const bool aHomeTeam ) const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Period states";

private:
	//! Period states.
	period_states mStates;
};

template <typename T, typename U> requires types::CPeriodState::period_play_policy<T>&& types::CPeriodStates::period_policy<U>
CPeriodStates::CPeriodStates(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aHomeTeamStrategy,
	const CTeamStrategy& aAwayTeamStrategy,
	std::uniform_random_bit_generator auto& aGenerator,
	const T& aPeriodPlayPolicy,
	const U& aPeriodPolicy
) try
{
	auto homeTeamAttack = std::bernoulli_distribution{}( aGenerator );
	do
	{
		if( homeTeamAttack )
			mStates.emplace_back( aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy,
				homeTeamAttack, aGenerator, aPeriodPlayPolicy );
		else
			mStates.emplace_back( aMatch, aMatchConfiguration, aAwayTeamStrategy, aHomeTeamStrategy,
				homeTeamAttack, aGenerator, aPeriodPlayPolicy );
		homeTeamAttack = !homeTeamAttack;
	} while( aPeriodPolicy( mStates, aMatchConfiguration ) );
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the period states." )

} // futsim::football namespace