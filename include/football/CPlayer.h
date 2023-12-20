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