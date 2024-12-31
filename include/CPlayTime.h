#pragma once

#include "IJsonable.h"

#include "types/CPlayTime.h"

namespace futsim
{

class CPlayTime;

template <> struct json_traits<CPlayTime>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Play time";
	//! JSON key for the \copybrief CPlayTime::mPeriodCount
	static inline constexpr std::string_view PERIOD_COUNT_KEY = "Period count";
	//! JSON key for the \copybrief CPlayTime::mPeriodTime
	static inline constexpr std::string_view PERIOD_TIME_KEY = "Period time";
};

/**
 * @brief Class that defines a play time phase of a match.
*/
class CPlayTime : public IJsonable, protected json_traits<CPlayTime>
{
protected:
	using period_count = types::CPlayTime::period_count;
	using period_time = types::CPlayTime::period_time;

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

private:
	//! Number of periods.
	period_count mPeriodCount;
	//! Length of each period.
	period_time mPeriodTime;
};

} // futsim namespace
