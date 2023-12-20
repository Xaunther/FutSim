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