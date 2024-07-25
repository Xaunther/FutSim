#pragma once

#include "football/CChanceState.h"

#include "football/CMatchConfiguration.h"
#include "football/CPlayer.h"
#include "football/CTeamStrategy.h"

#include "ExceptionUtils.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a penalty in a penalty shootout.
*/
class CPenaltyState : private CChanceState
{
public:
	/**
	 * @brief Constructor from the goalkeeper, penalty taker and configuration.
	 * @param aMatch Match definition.
	 * @param aMatchConfiguration Match configuration.
	 * @param aShooter Penalty taker.
	 * @param aGoalkeeper Goalkeeper.
	 * @param aHomeTeamShoot Whether the home team is shooting.
	 * @param aGenerator RNG to use.
	*/
	explicit CPenaltyState(
		const CMatch& aMatch,
		const CMatchConfiguration& aMatchConfiguration,
		const CPlayer& aShooter,
		const CPlayer& aGoalkeeper,
		const bool aHomeTeamShoot,
		std::uniform_random_bit_generator auto& aGenerator
	);

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mStopper
	const futsim::types::CPerson::name_type& GetGoalkeeper() const noexcept;

	//! Retrieves the \copybrief mShooter
	const futsim::types::CPerson::name_type& GetShooter() const noexcept;

	//! @copydoc CChanceState::GetChanceOutcome
	using CChanceState::GetChanceOutcome;

public:
	/**
	 * @brief Adds the class to JSON object.
	 */
	void ToJSON( json& aJSON ) const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Penalty state";
	//! JSON key for the \copybrief mOutcome
	static inline constexpr std::string_view JSON_OUTCOME = CChanceState::JSON_OUTCOME;
	//! JSON key for the \copybrief mShooter
	static inline constexpr std::string_view JSON_SHOOTER = CChanceState::JSON_ACTOR<E_PLAYER_SKILL::Sh>;
	//! JSON key for the \copybrief mStopper
	static inline constexpr std::string_view JSON_STOPPER = CChanceState::JSON_ACTOR<E_PLAYER_SKILL::St>;
};

CPenaltyState::CPenaltyState(
	const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration,
	const CPlayer& aShooter,
	const CPlayer& aGoalkeeper,
	const bool aHomeTeamShoot,
	std::uniform_random_bit_generator auto& aGenerator
) try :
	CChanceState( types::CChancesDrawConfiguration::E_SET_PIECE_TYPE::PENALTY,
		aMatchConfiguration.GetDrawConfiguration().CreatePenaltyOutcomeDistribution(
			aGoalkeeper.GetPlayerSkills().GetSkill( E_PLAYER_SKILL::St )* CTeamStrategy::CalculateAmbientFactor( aMatch, aMatchConfiguration, !aHomeTeamShoot ),
			aShooter.GetPlayerSkills().GetSkill( E_PLAYER_SKILL::Sh )* CTeamStrategy::CalculateAmbientFactor( aMatch, aMatchConfiguration, aHomeTeamShoot ) )( aGenerator ),
		aGoalkeeper.GetKnownName().data(), {}, {}, aShooter.GetKnownName().data() )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the penalty state." )

} // futsim::football namespace