#pragma once

#include "IJsonable.h"

#include "types/CPeriodState.h"

#include "football/CPlayState.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a match period.
*/
class CPeriodState : public IJsonable
{
protected:
	using plays = types::CPeriodState::plays;

public:
	/**
	 * @brief Default policy functor for the plays of the period.
	 * @details All configured minutes are played.
	*/
	//! 
	struct SDefaultPeriodPlayPolicy
	{
		/**
		 * @brief Returns whether another minute must be played.
		 * @param aPlays Plays of the period.
		 * @param aMatchConfiguration Match configuration.
		*/
		bool operator()( const plays& aPlays, const CMatchConfiguration& aMatchConfiguration ) const;
	};

	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aHomeTeamStrategy Current match strategy for the home team.
	 * @param aAwayTeamStrategy Current match strategy for the away team.
	 * @param aHomeTeamAttack Whether the home team is attacking.
	 * @param aGenerator RNG to use.
	 * @pre The team strategies must both pass \ref CMatchConfiguration::CheckTeamStrategy and \ref CMatch::CheckTeamStrategy
	*/
	explicit CPeriodState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aHomeTeamStrategy,
		const CTeamStrategy& aAwayTeamStrategy,
		bool aHomeTeamAttack,
		std::uniform_random_bit_generator auto& aGenerator
	);

protected:
	/**
	 * @brief Empty period constructor.
	 * @param aPeriodTime Play time of the period.
	*/
	explicit CPeriodState(
		const futsim::types::CPlayTime::period_time& aPeriodTime
	);

	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPlays
	const plays& GetPlays() const noexcept;

protected:
	/**
	 * @brief Adds a play to the plays of the period
	 * @param aPlayState Play to add.
	 * @param aHomeTeamAttack Whether the home team is attacking.
	*/
	void PushPlayState( CPlayState&& aPlayState, const bool aHomeTeamAttack ) noexcept;

	/**
	 * @brief Returns whether the home team is starting the next attack.
	*/
	bool IsHomeTeamAttackNext() const;

public:
	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Period state";
	//! JSON key for the \copybrief mPlays
	static inline constexpr std::string_view JSON_PLAYS = "Plays";
	//! JSON key to indicate if the play corresponds to the home team.
	static inline constexpr std::string_view JSON_HOME_TEAM_PLAY = "Home team play";

private:
	//! Plays of the period.
	plays mPlays;
};

CPeriodState::CPeriodState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aHomeTeamStrategy,
	const CTeamStrategy& aAwayTeamStrategy,
	bool aHomeTeamAttack,
	std::uniform_random_bit_generator auto& aGenerator
)
{
	mPlays.reserve( aMatchConfiguration.GetPlayTime().GetPeriodTime() );

	for( futsim::types::CPlayTime::period_time time = 0; time < aMatchConfiguration.GetPlayTime().GetPeriodTime(); ++time )
	{
		if( aHomeTeamAttack )
			PushPlayState( CPlayState{ aMatch, aMatchConfiguration, aHomeTeamStrategy, aAwayTeamStrategy,
				aHomeTeamAttack, aGenerator }, aHomeTeamAttack );
		else
			PushPlayState( CPlayState{ aMatch, aMatchConfiguration, aAwayTeamStrategy, aHomeTeamStrategy,
				aHomeTeamAttack, aGenerator }, aHomeTeamAttack );
		aHomeTeamAttack = IsHomeTeamAttackNext();
	}
}

} // futsim::football namespace