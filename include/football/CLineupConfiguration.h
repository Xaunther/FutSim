#pragma once

#include "IJsonable.h"

#include "football/CLineupConfigurationTypes.h"

namespace futsim::football
{

/**
 * @brief Class that configures the lineup rules.
*/
class CLineupConfiguration : public IJsonable
{
protected:
	using player_count_range = CLineupConfigurationTypes::player_count_range;

public:
	//! Retrieves the \copybrief mDFRange
	const player_count_range& GetDFRange() const noexcept;

	//! Retrieves the \copybrief mMFRange
	const player_count_range& GetMFRange() const noexcept;

	//! Retrieves the \copybrief mFWRange
	const player_count_range& GetFWRange() const noexcept;

private:
	//! Allowed DFs count range.
	player_count_range mDFRange;
	//! Allowed midfielders (DMs+MFs+AMs) count range.
	player_count_range mMFRange;
	//! Allowed FWs count range.
	player_count_range mFWRange;
};

} // futsim namespace