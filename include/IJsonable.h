#pragma once

namespace futsim
{

namespace nlohmann { class json; }

/**
 * @brief Interface for classes that can be converted into JSON.
 */
class IJsonable
{
	using json = nlohmann::json;

public:
	/**
	 * @brief Virtual destructor for base class.
	 */
	virtual ~IJsonable() = default;

	/**
	 * @brief Appends class to JSON.
	 */
	void ToJSON( json& aJSON ) const noexcept;

private:
	/**
	 * @copydoc ToJSON
	*/
	virtual void JSON( json& aJSON ) const noexcept = 0;
};

} // futsim namespace