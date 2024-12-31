#pragma once

#include "IJsonable.h"

#include "football/types/CPenaltyShootoutConfiguration.h"
#include "football/EPenaltySequence.h"
#include "DefaultTraits.h"

namespace futsim
{

namespace football
{
class CPenaltyShootoutConfiguration;
}

template <> struct default_traits<football::CPenaltyShootoutConfiguration>
{
protected:
	using penalty_count = football::types::CPenaltyShootoutConfiguration::penalty_count;
public:
	//! Default \copybrief football::CPenaltyShootoutConfiguration::mPenaltySequence
	static inline constexpr football::E_PENALTY_SEQUENCE PENALTY_SEQUENCE = football::E_PENALTY_SEQUENCE::AB;
	//! Default \copybrief football::CPenaltyShootoutConfiguration::mMinPenaltyCount
	static inline constexpr penalty_count PENALTY_COUNT = 5;
};

template <> struct json_traits<football::CPenaltyShootoutConfiguration>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Penalty shootout configuration";
	//! JSON key for the \copybrief football::CPenaltyShootoutConfiguration::mPenaltySequence
	static inline constexpr std::string_view SEQUENCE_KEY = "Sequence";
	//! JSON key for the \copybrief football::CPenaltyShootoutConfiguration::mMinPenaltyCount
	static inline constexpr std::string_view MIN_PENALTY_COUNT_KEY = "Min penalty count";
};

namespace football
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

} // football namespace

} // futsim namespace
