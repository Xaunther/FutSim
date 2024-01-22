#pragma once

#include "IJsonable.h"

#include "CPlayTimeTypes.h"

namespace futsim
{

/**
 * @brief Class that defines a play time phase of a match.
*/
class CPlayTime : public IJsonable
{
protected:
	using period_count = CPlayTimeTypes::period_count;
	using period_time = CPlayTimeTypes::period_time;

public:
	/**
	 * @brief Member constructor.
	 * @param aPeriodCount \ref mPeriodCount
	 * @param aPeriodTime \ref mPeriodTime
	 * @pre At least 1 period must compose the play time.
	 * @pre Each period must be at least 1 minute long.
	*/
	explicit CPlayTime(
		const period_count& aPeriodCount,
		const period_time& aPeriodTime );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPlayTime( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPeriodCount
	const period_count& GetPeriodCount() const noexcept;

	//! Retrieves the \copybrief mPeriodTime
	const period_time& GetPeriodTime() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Play time";
	//! JSON key for the \copybrief mPeriodCount
	static inline constexpr std::string_view JSON_PERIOD_COUNT = "Period count";
	//! JSON key for the \copybrief mPeriodTime
	static inline constexpr std::string_view JSON_PERIOD_TIME = "Period time";

private:
	//! Number of periods.
	period_count mPeriodCount;
	//! Length of each period.
	period_time mPeriodTime;
};

} // futsim namespace