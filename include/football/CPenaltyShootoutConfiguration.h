#pragma once

#include "IJsonable.h"

#include "football/CPenaltyShootoutConfigurationTypes.h"

namespace futsim::football
{

class CPenaltyShootoutConfiguration : public IJsonable
{
	using E_SEQUENCE = CPenaltyShootoutConfigurationTypes::E_SEQUENCE;
	using penalty_count = CPenaltyShootoutConfigurationTypes::penalty_count;

public:
	/**
	 * @brief Member constructor.
	 * @param aPenaltySequence \ref mPenaltySequence
	 * @param aMinPenaltyCount \ref mMinPenaltyCount
	*/
	explicit CPenaltyShootoutConfiguration(
		const E_SEQUENCE& aPenaltySequence = E_SEQUENCE::AB,
		const penalty_count& aMinPenaltyCount = 5 ) noexcept;

private:
	//! Penalty sequence.
	E_SEQUENCE mPenaltySequence;
	//! Minimum number of penalties to be taken by each team.
	penalty_count mMinPenaltyCount;
};

} // futsim::football namespace