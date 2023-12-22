#pragma once

#include "CPerson.h"

#include "football/CPlayerSkills.h"

namespace futsim
{

namespace football
{

/**
 * @brief Class that defines a football player
*/
class CPlayer : public CPerson
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

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPlayerSkills
	const CPlayerSkills GetPlayerSkills() const noexcept;

	//! JSON key for the class-
	static inline constexpr std::string_view JSON_KEY = "Player";

private:
	//! Skills
	CPlayerSkills mPlayerSkills;
};

} // football namespace

} // futsim namespace