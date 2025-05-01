#pragma once

#include "IJsonable.h"
#include "traits/CPerson.h"

#include "ENationality.h"

#include "types/CPerson.h"

namespace futsim
{

/**
 * @brief Class that defines a person.
*/
class CPerson : public IJsonable, protected json_traits<CPerson>
{
protected:
	using name_type = types::CPerson::name_type;

public:
	/**
	 * @brief Member constructor.
	 * @param aFirstName \ref mFirstName
	 * @param aSurnames \ref mSurnames
	 * @param aKnownName \ref mKnownName
	 * @param aAge \ref mAge
	 * @param aNationality \ref mNationality
	 * @pre The first name string cannot be empty.
	 * @pre The surnames string cannot be empty.
	 * @details If the passed known name is empty, it will default to the surnames.
	*/
	explicit CPerson(
		const std::string_view aFirstName,
		const std::string_view aSurnames,
		const std::string_view aKnownName,
		const unsigned short& aAge,
		const E_NATIONALITY& aNationality );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CPerson( const json& aJSON );

	//! Virtual destructor for base class.
	~CPerson() override = default;

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mFirstName
	std::string_view GetFirstName() const noexcept;

	//! Retrieves the \copybrief mSurnames
	std::string_view GetSurnames() const noexcept;

	//! Retrieves the \copybrief mKnownName
	std::string_view GetKnownName() const noexcept;

	//! Retrieves the \copybrief mAge
	const unsigned short& GetAge() const noexcept;

	//! Retrieves the \copybrief mNationality
	const E_NATIONALITY& GetNationality() const noexcept;

private:
	//! First name.
	name_type mFirstName;
	//! Surnames.
	name_type mSurnames;
	//! Name by which the player is known.
	name_type mKnownName;
	//! Age.
	unsigned short mAge;
	//! Nationality.
	E_NATIONALITY mNationality;
};

} // futsim namespace
