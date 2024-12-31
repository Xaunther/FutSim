#pragma once

#include "IJsonable.h"

#include "football/CPlayer.h"
#include "football/types/CTeam.h"

#include <random>
#include <span>

namespace futsim
{

namespace football
{
class CTeam;
}

template <> struct json_traits<football::CTeam>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Team";
	//! JSON key for the \copybrief football::CTeam::mName
	static inline constexpr std::string_view NAME_KEY = "Name";
	//! JSON key for the \copybrief football::CTeam::mAbbreviation
	static inline constexpr std::string_view ABBREVIATION_KEY = "Abbreviation";
	//! JSON key for the \copybrief football::CTeam::mManager
	static inline constexpr std::string_view MANAGER_KEY = "Manager";
	//! JSON key for the \copybrief football::CTeam::mPlayers
	static inline constexpr std::string_view PLAYERS_KEY = "Players";
	//! JSON key for the \copybrief football::CTeam::mSupportFactor
	static inline constexpr std::string_view SUPPORT_FACTOR_KEY = "Support factor";
	//! JSON key for the mean attendance.
	static inline constexpr std::string_view MEAN_ATTENDANCE_KEY = "Mean attendance";
	//! JSON key for the standard deviation of the attendance.
	static inline constexpr std::string_view STD_DEV_ATTENDANCE_KEY = "StdDev attendance";
};

namespace football
{

class CLineup;

/**
 * @brief Class that defines a football team.
*/
class CTeam : public IJsonable, protected json_traits<CTeam>
{
protected:
	using name_type = types::CTeam::name_type;
	using players = types::CTeam::players;
	using name_index_map = types::CTeam::name_index_map;
	using support_factor = types::CTeam::support_factor;
	using attendance = types::CTeam::attendance;
	using attendance_distribution = types::CTeam::attendance_distribution;

public:
	/**
	 * @brief Member constructor.
	 * @param aName \ref mName
	 * @param aAbbreviation \ref mAbbreviation
	 * @param aManager \ref mManager
	 * @param aPlayers \ref mPlayers
	 * @param aSupportFactor \ref mSupportFactor
	 * @param aMeanAttendance Average number of fans willing to attend the match.
	 * @param aStdDevAttendance Standard deviation of fans willing to attend the match.
	 * @pre The name cannot be empty.
	 * @pre The abbreviation must be a 3-letter string.
	 * @pre The manager cannot me empty.
	 * @pre The support factor must be positive.
	 * @pre The mean attendance cannot be negative.
	 * @pre The attendance standard deviation must be positive.
	*/
	explicit CTeam(
		const std::string_view aName,
		const std::string_view aAbbreviation,
		const std::string_view aManager,
		const players& aPlayers,
		const support_factor& aSupportFactor,
		const double& aMeanAttendance,
		const double& aStdDevAttendance );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CTeam( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mName
	std::string_view GetName() const noexcept;

	//! Retrieves the \copybrief mAbbreviation
	std::string_view GetAbbreviation() const noexcept;

	//! Retrieves the \copybrief mManager
	std::string_view GetManager() const noexcept;

	//! Retrieves the \copybrief mPlayers
	std::span<const CPlayer> GetPlayers() const noexcept;

	/**
	 * @brief Retrieves a player by its known name.
	 * @details Throws an exception if no player is found.
	 * @param aKnownName Known name.
	*/
	//! Retrieves a player by its known name.
	const CPlayer& GetPlayer( const std::string_view aKnownName ) const;

	//! Retrieves the \copybrief mSupportFactor
	const support_factor& GetSupportFactor() const noexcept;

	//! Retrieves the attendance distribution parameters.
	attendance_distribution::param_type GetAttendanceDistributionParameters() const noexcept;

	//! Generates a random attendance.
	attendance GenerateAttendance( std::uniform_random_bit_generator auto& aGenerator ) const noexcept;

	/**
	 * @brief Checks the validity of a lineup according to this team definition.
	 * @param aLineup Lineup to check.
	*/
	const CLineup& CheckLineup( const CLineup& aLineup ) const;

private:
	//! Team name.
	name_type mName;
	//! 3-letter team abbreviation.
	name_type mAbbreviation;
	//! Manager.
	name_type mManager;
	//! Roster of players.
	players mPlayers;
	//! Map to improve player search.
	name_index_map mNameIndexMap;
	//! Support factor that dictates the support the team receives from the fans.
	support_factor mSupportFactor;
	//! Local fan attendance distribution parameters.
	attendance_distribution::param_type mAttendanceDistributionParameters;
};

} // football namespace

} // futsim namespace
