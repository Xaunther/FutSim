#pragma once

#include "types/IJsonable.h"

namespace futsim
{

/**
 * @brief Interface for classes that can be converted into JSON.
 */
class IJsonable
{
protected:
	using json = types::IJsonable::json;

public:
	/**
	 * @brief Virtual destructor for base class.
	 */
	virtual ~IJsonable() = default;

	/**
	 * @brief Adds the class to JSON object.
	 */
	void ToJSON( json& aJSON ) const noexcept;

private:
	/**
	 * @copydoc ToJSON
	*/
	virtual void JSON( json& aJSON ) const noexcept = 0;
};

//! Macro to instantiate a template trait for every value of an enum.
#define FUTSIM_INSTANTIATE_ENUM_TRAIT(name, id, class, member, enum, suffix, ... ) \
template <> inline constexpr std::string_view json_traits<class>::member<enum::name> = id suffix;

//! JSON traits for any class.
template <typename T> struct json_traits
{
};

} // futsim namespace