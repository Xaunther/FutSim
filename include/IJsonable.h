#pragma once

#include "IJsonableTypes.h"

namespace futsim
{

/**
 * @brief Interface for classes that can be converted into JSON.
 */
class IJsonable
{
protected:
	using json = IJsonableTypes::json;

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

} // futsim namespace