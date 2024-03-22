#pragma once

#include "IJsonable.h"

#include "football/types/CPenaltyShootoutConfiguration.h"
#include "football/EPenaltySequence.h"

namespace futsim::football
{

/**
 * @brief Class to configure a penalty shootout.
*/
class CPenaltyShootoutConfiguration : public IJsonable
{
protected:
	using penalty_count = types::CPenaltyShootoutConfiguration::penalty_count;

public:
	/**
	 * @brief Member constructor.
	 * @param aPenaltySequence \ref mPenaltySequence
	 * @param aMinPenaltyCount \ref mMinPenaltyCount
	*/
	explicit CPenaltyShootoutConfiguration(
		const E_PENALTY_SEQUENCE& aPenaltySequence = DEFAULT_PENALTY_SEQUENCE,
		const penalty_count& aMinPenaltyCount = DEFAULT_PENALTY_COUNT ) noexcept;

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPenaltyShootoutConfiguration( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPenaltySequence
	const E_PENALTY_SEQUENCE& GetPenaltySequence() const noexcept;

	//! Retrieves the \copybrief mMinPenaltyCount
	const penalty_count& GetMinPenaltyCount() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Penalty shootout configuration";
	//! JSON key for the \copybrief mPenaltySequence
	static inline constexpr std::string_view JSON_SEQUENCE = "Sequence";
	//! JSON key for the \copybrief mMinPenaltyCount
	static inline constexpr std::string_view JSON_MIN_PENALTY_COUNT = "Min penalty count";

	//! Default \copybrief mPenaltySequence
	static inline constexpr E_PENALTY_SEQUENCE DEFAULT_PENALTY_SEQUENCE = E_PENALTY_SEQUENCE::AB;

	//! Default \copybrief mMinPenaltyCount
	static inline constexpr penalty_count DEFAULT_PENALTY_COUNT = 5;

private:
	//! Penalty sequence.
	E_PENALTY_SEQUENCE mPenaltySequence;
	//! Minimum number of penalties to be taken by each team.
	penalty_count mMinPenaltyCount;
};

} // futsim::football namespace