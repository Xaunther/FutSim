#pragma once

#include "IJsonable.h"

#include "ENationality.h"

namespace futsim
{

/**
 * @brief Class that defines a person.
*/
class CPerson : public IJsonable
{
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

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mFirstName
	const std::string_view GetFirstName() const noexcept;

	//! Retrieves the \copybrief mSurnames
	const std::string_view GetSurnames() const noexcept;

	//! Retrieves the \copybrief mKnownName
	const std::string_view GetKnownName() const noexcept;

	//! Retrieves the \copybrief mAge
	const unsigned short& GetAge() const noexcept;

	//! Retrieves the \copybrief mNationality
	const E_NATIONALITY& GetNationality() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Person";
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
	//! Nationality.
	E_NATIONALITY mNationality;
};

} // futsim namespace