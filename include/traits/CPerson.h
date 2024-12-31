#pragma once

#include <string_view>

#include "traits/json.h"

namespace futsim
{

class CPerson;

template <> struct json_traits<CPerson>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Person";
	//! JSON key for the \copybrief CPerson::mFirstName
	static inline constexpr std::string_view FIRST_NAME_KEY = "First name";
	//! JSON key for the \copybrief CPerson::mSurnames
	static inline constexpr std::string_view SURNAMES_KEY = "Surnames";
	//! JSON key for the \copybrief CPerson::mKnownName
	static inline constexpr std::string_view KNOWN_NAME_KEY = "Known name";
	//! JSON key for the \copybrief CPerson::mAge
	static inline constexpr std::string_view AGE_KEY = "Age";
	//! JSON key for the \copybrief CPerson::mNationality
	static inline constexpr std::string_view NATIONALITY_KEY = "Nationality";
};

} // futsim namespace
