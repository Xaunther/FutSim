#pragma once

#include "CPerson.h"
#include "football/traits/CPlayer.h"

#include "football/CPlayerSkills.h"

namespace futsim::football
{

/**
 * @brief Class that defines a football player.
*/
class CPlayer : public CPerson, protected json_traits<CPlayer>
{
public:
	/**
	 * @copydoc futsim::CPerson::CPerson
	 * @param aPlayerSkills \ref mPlayerSkills
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

private:
	//! Skills.
	CPlayerSkills mPlayerSkills;
};

} // futsim::football namespace
