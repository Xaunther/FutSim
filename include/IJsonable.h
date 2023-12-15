#pragma once

#include "IJsonableTypes.h"

namespace futsim
{

/**
 * @brief Interface for classes that can be converted into JSON.
 */
class IJsonable
{
	using json = IJsonableTypes::json;

public:
	/**
	 * @brief Virtual destructor for base class.
	 */
	virtual ~IJsonable() = default;

	/**
	 * @brief Returns the class represented as JSON.
	 */
	json ToJSON() const noexcept;

private:
	/**
	 * @copydoc ToJSON
	*/
	virtual json JSON() const noexcept = 0;
};

} // futsim namespace