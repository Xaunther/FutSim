#pragma once

#include "IJsonable.h"

#include "CPersonTypes.h"
#include "CFoulDrawConfigurationTypes.h"

#include "football/CMatchConfiguration.h"
#include "football/CTeamStrategy.h"

namespace futsim::football
{

/**
 * @brief Class that represents the state of a foul.
*/
class CFoulState : public IJsonable
{
protected:
	using name_type = CPersonTypes::name_type;
	using E_FOUL_DRAW_OUTCOME = CFoulDrawConfigurationTypes::E_FOUL_DRAW_OUTCOME;

public:
	/**
	 * @brief Constructor from the match definition, configuration and current strategies.
	 * @param aMatchConfiguration Match configuration.
	 * @param aTeamStrategy Current match strategy for the team committing the foul.
	 * @param aGenerator RNG to use.
	 * @pre The team strategy must pass \ref CMatchConfiguration::CheckTeamStrategy.
	*/
	explicit CFoulState(
		const CMatchConfiguration& aMatchConfiguration,
		const CTeamStrategy& aTeamStrategy,
		std::uniform_random_bit_generator auto& aGenerator
	) noexcept;

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mCommitter
	std::string_view GetCommitter() const noexcept;

	//! Retrieves the \copybrief mOutcome
	const E_FOUL_DRAW_OUTCOME& GetOutcome() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Foul state";
	//! JSON key for the \copybrief mCommitter
	static inline constexpr std::string_view JSON_COMMIITER = "Committer";
	//! JSON key for the \copybrief mOutcome
	static inline constexpr std::string_view JSON_OUTCOME = "Outcome";

private:
	//! Player that committed the foul.
	name_type mCommitter;
	//! Foul draw outcome.
	E_FOUL_DRAW_OUTCOME mOutcome;
};

CFoulState::CFoulState(
	const CMatchConfiguration& aMatchConfiguration,
	const CTeamStrategy& aTeamStrategy,
	std::uniform_random_bit_generator auto& aGenerator
) noexcept :
	mCommitter( aMatchConfiguration.GetDrawConfiguration().GetFoulDrawConfiguration().DrawFoulCommitter( aTeamStrategy.GetLineup(), aGenerator ) ),
	mOutcome( aMatchConfiguration.GetDrawConfiguration().CreateFoulDistribution()( aGenerator ) )
{
}

} // futsim::football namespace