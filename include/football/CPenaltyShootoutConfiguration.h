#pragma once

#include "IJsonable.h"

#include "football/CPenaltyShootoutConfigurationTypes.h"
#include "football/EPenaltySequence.h"

namespace futsim::football
{

class CPenaltyShootoutConfiguration : public IJsonable
{
	using json = IJsonableTypes::json;
	using penalty_count = CPenaltyShootoutConfigurationTypes::penalty_count;

public:
	/**
	 * @brief Member constructor.
	 * @param aPenaltySequence \ref mPenaltySequence
	 * @param aMinPenaltyCount \ref mMinPenaltyCount
	*/
	explicit CPenaltyShootoutConfiguration(
		const E_PENALTY_SEQUENCE& aPenaltySequence = E_PENALTY_SEQUENCE::AB,
		const penalty_count& aMinPenaltyCount = 5 ) noexcept;

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
	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Penalty shootout configuration";
	//! JSON key for the \copybrief mPenaltySequence
	static inline constexpr std::string_view JSON_SEQUENCE = "Sequence";
	//! JSON key for the \copybrief mMinPenaltyCount
	static inline constexpr std::string_view JSON_MIN_PENALTY_COUNT = "Min penalty count";

private:
	//! Penalty sequence.
	E_PENALTY_SEQUENCE mPenaltySequence;
	//! Minimum number of penalties to be taken by each team.
	penalty_count mMinPenaltyCount;
};

} // futsim::football namespace