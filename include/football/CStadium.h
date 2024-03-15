#pragma once

#include "IJsonable.h"

#include "CStadiumTypes.h"

namespace futsim::football
{

/**
 * @brief Class that defines a football stadium.
*/
class CStadium : public IJsonable
{
protected:
	using capacity = CStadiumTypes::capacity;
	using ambient_factor = CStadiumTypes::ambient_factor;

public:
	/**
	 * @brief Member constructor.
	 * @param aName \ref mName
	 * @param aCapacity \ref mCapacity
	 * @param aAmbientFactor \ref mAmbientFactor
	 * @pre The name cannot be empty.
	 * @pre The ambient factor cannot be negative.
	*/
	explicit CStadium(
		const std::string_view aName,
		const capacity aCapacity,
		const ambient_factor aAmbientFactor );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object.
	*/
	explicit CStadium( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	*/
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mName
	std::string_view GetName() const noexcept;

	//! Retrieves the \copybrief mCapacity
	const capacity& GetCapacity() const noexcept;

	//! Retrieves the \copybrief mAmbientFactor
	const ambient_factor& GetAmbientFactor() const noexcept;

	//! JSON key for the class.
	static inline constexpr std::string_view JSON_KEY = "Stadium";
	//! JSON key for the \copybrief mName
	static inline constexpr std::string_view JSON_NAME = "Name";
	//! JSON key for the \copybrief mCapacity
	static inline constexpr std::string_view JSON_CAPACITY = "Capacity";
	//! JSON key for the \copybrief mAmbientFactor
	static inline constexpr std::string_view JSON_AMBIENT_FACTOR = "Ambient factor";

private:
	//! Stadium name.
	std::string mName;
	//! Stadium capacity.
	capacity mCapacity;
	//! Ambient factor that dictates the support the home team receives.
	ambient_factor mAmbientFactor;
};

} // futsim::football namespace