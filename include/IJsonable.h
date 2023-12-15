#pragma once

#include <nlohmann/json.hpp>

namespace futsim
{

/**
 * @brief Interface for classes that can be converted into JSON.
 */
class IJsonable
{
protected:
	using json = nlohmann::orderded_json;

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