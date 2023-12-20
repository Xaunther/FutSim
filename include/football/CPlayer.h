#pragma once

#include "IJsonable.h"

#include "ENationality.h"
#include "football/CPlayerSkills.h"

namespace futsim
{

namespace football
{

/**
 * @brief Class that defines a football player
*/
class CPlayer : public IJsonable
{
	using json = IJsonableTypes::json;

public:
	/**
	 * @brief Member constructor.
	 * @param aFirstName \ref mFirstName
	 * @param aSurnames \ref mSurnames
	 * @param aKnownName \ref mKnownName
	 * @param aAge \ref mAge
	 * @param aNationality \ref mNationality
	 * @param aPlayerSkills \ref mPlayerSkills
	 * @pre The first name string cannot be empty.
	 * @pre The surnames string cannot be empty.
	 * @details If the passed known name is empty, it will default to the surnames.
	*/
	explicit CPlayer(
		const std::string_view aFirstName,
		const std::string_view aSurnames,
		const std::string_view aKnownName,
		const unsigned short& aAge,
		const E_NATIONALITY& aNationality,
		const CPlayerSkills& aPlayerSkills );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPlayer( const json& aJSON );

private:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	json JSON() const noexcept override;

public:
	//! JSON key for the class-
	static inline constexpr std::string_view JSON_NAME = "Player";
	//! JSON key for the \copybrief mFirstName
	static inline constexpr std::string_view JSON_FIRST_NAME = "First name";
	//! JSON key for the \copybrief mSurnames
	static inline constexpr std::string_view JSON_SURNAMES = "Surnames";
	//! JSON key for the \copybrief mKnownName
	static inline constexpr std::string_view JSON_KNOWN_NAME = "Known name";
	//! JSON key for the \copybrief mAge
	static inline constexpr std::string_view JSON_AGE = "Age";
	//! JSON key for the \copybrief mNationality
	static inline constexpr std::string_view JSON_NATIONALITY = "Nationality";

private:
	//! First name.
	std::string mFirstName;
	//! Surnames.
	std::string mSurnames;
	//! Name by which the player is known.
	std::string mKnownName;
	//! Age.
	unsigned short mAge;
	//! Nationality (TBD)
	E_NATIONALITY mNationality;
	//! Skills
	CPlayerSkills mPlayerSkills;
};

} // football namespace

} // futsim namespace