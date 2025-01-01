#pragma once

#include "IJsonable.h"
#include "football/traits/CPenaltyShootoutConfiguration.h"

#include "football/types/CPenaltyShootoutConfiguration.h"
#include "football/EPenaltySequence.h"

namespace futsim::football
{

/**
 * @brief Class to configure a penalty shootout.
*/
class CPenaltyShootoutConfiguration : public IJsonable, protected default_traits<CPenaltyShootoutConfiguration>, protected json_traits<CPenaltyShootoutConfiguration>
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
		const E_PENALTY_SEQUENCE& aPenaltySequence = PENALTY_SEQUENCE,
		const penalty_count& aMinPenaltyCount = PENALTY_COUNT ) noexcept;

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

private:
	//! Penalty sequence.
	E_PENALTY_SEQUENCE mPenaltySequence;
	//! Minimum number of penalties to be taken by each team.
	penalty_count mMinPenaltyCount;
};

} // futsim::football namespace
