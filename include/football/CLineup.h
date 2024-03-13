#pragma once

#include "IJsonable.h"

#include "football/CLineupTypes.h"

namespace futsim::football
{

/**
 * @brief Class that defines a lineup.
*/
class CLineup : public IJsonable
{
protected:
	using names = CLineupTypes::names;
	using position_names = CLineupTypes::position_names;

public:
	/**
	 * @brief Member constructor.
	 * @param aPlayersLineup \ref mPlayersLineup
	*/
	explicit CLineup( const position_names& aPlayersLineup );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CLineup( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	/**
	 * @brief Retrieves the players at a certain position.
	 * @param aPlayerPosition Position.
	*/
	const names& GetPlayers( const E_PLAYER_POSITION& aPlayerPosition ) const noexcept;

	//! Retrieves the substitute players.
	const names& GetSubs() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Lineup";
	//! JSON key for the GK.
	static inline constexpr std::string_view JSON_GK = "GK";
	//! JSON key for the DFs.
	static inline constexpr std::string_view JSON_DFS = "DFs";
	//! JSON key for the DMs.
	static inline constexpr std::string_view JSON_DMS = "DMs";
	//! JSON key for the MFs.
	static inline constexpr std::string_view JSON_MFS = "MFs";
	//! JSON key for the AMs.
	static inline constexpr std::string_view JSON_AMS = "AMs";
	//! JSON key for the FWs.
	static inline constexpr std::string_view JSON_FWS = "FWs";
	//! JSON key for the substitutes.
	static inline constexpr std::string_view JSON_SUBS = "Subs";

private:
	/**
	 * @brief Checks the validity of the players lineup.
	 * @param aPlayersLineup Players lineup.
	*/
	void CheckPlayersLineup() const;

	//! Lined up players by position.
	position_names mPlayersLineup;
};

} // futsim namespace