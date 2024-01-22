#pragma once

#include "../CPlayTime.h"

#include "football/CPlayTimeTypes.h"

namespace futsim::football
{

/**
 * @brief Class that defines a play time phase of a football match.
*/
class CPlayTime : public futsim::CPlayTime
{
	using subs_count = CPlayTimeTypes::subs_count;

public:
	/**
	 * @copydoc futsim::CPlayTime::CPlayTime
	 * @param aAvailableSubs \ref mAvailableSubs
	 * @pre At least 1 period must compose the play time.
	 * @pre Each period must be at least 1 minute long.
	*/
	explicit CPlayTime(
		const period_count& aPeriodCount = 2,
		const period_time& aPeriodTime = 45,
		const subs_count& aAvailableSubs = 5 );

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
	//! Retrieves the \copybrief mAvailableSubs
	const subs_count& GetAvailableSubs() const noexcept;

	//! JSON key for the \copybrief mAvailableSubs
	static inline constexpr std::string_view JSON_AVAILABLE_SUBS = "Available subs";

private:
	//! Number of available subs.
	subs_count mAvailableSubs;
};

} // futsim::football namespace