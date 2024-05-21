#pragma once

#include "IJsonable.h"

#include "football/CPlayer.h"
#include "football/types/CTeam.h"

#include <random>
#include <span>

namespace futsim::football
{

class CLineup;

/**
 * @brief Class that defines a football team.
*/
class CTeam : public IJsonable
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

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Team";
	//! JSON key for the \copybrief mName
	static inline constexpr std::string_view JSON_NAME = "Name";
	//! JSON key for the \copybrief mAbbreviation
	static inline constexpr std::string_view JSON_ABBREVIATION = "Abbreviation";
	//! JSON key for the \copybrief mManager
	static inline constexpr std::string_view JSON_MANAGER = "Manager";
	//! JSON key for the \copybrief mPlayers
	static inline constexpr std::string_view JSON_PLAYERS = "Players";
	//! JSON key for the \copybrief mSupportFactor
	static inline constexpr std::string_view JSON_SUPPORT_FACTOR = "Support factor";
	//! JSON key for the mean attendance.
	static inline constexpr std::string_view JSON_MEAN_ATTENDANCE = "Mean attendance";
	//! JSON key for the standard deviation of the attendance.
	static inline constexpr std::string_view JSON_STD_DEV_ATTENDANCE = "StdDev attendance";

private:
	//! Team name.
	name_type mName;
	//! 3-letter team abbreviation.
	name_type mAbbreviation;
	//! Manager.
	name_type mManager;
	//! Roster of players.
	players mPlayers;
	//! Support factor that dictates the support the team receives from the fans.
	support_factor mSupportFactor;
	//! Local fan attendance distribution parameters.
	attendance_distribution::param_type mAttendanceDistributionParameters;
};

} // futsim::football namespace