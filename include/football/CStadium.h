#pragma once

#include "IJsonable.h"
#include "traits/json.h"

#include "types/CStadium.h"

namespace futsim
{

namespace football
{
class CStadium;
}

template <> struct json_traits<football::CStadium>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Stadium";
	//! JSON key for the \copybrief football::CStadium::mName
	static inline constexpr std::string_view NAME_KEY = "Name";
	//! JSON key for the \copybrief football::CStadium::mCapacity
	static inline constexpr std::string_view CAPACITY_KEY = "Capacity";
	//! JSON key for the \copybrief football::CStadium::mAmbientFactor
	static inline constexpr std::string_view AMBIENT_FACTOR_KEY = "Ambient factor";
};

namespace football
{

/**
 * @brief Class that defines a football stadium.
*/
class CStadium : public IJsonable, protected json_traits<CStadium>
{
protected:
	using capacity = types::CStadium::capacity;
	using ambient_factor = types::CStadium::ambient_factor;

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

private:
	//! Stadium name.
	std::string mName;
	//! Stadium capacity.
	capacity mCapacity;
	//! Ambient factor that dictates the support the home team receives.
	ambient_factor mAmbientFactor;
};

} // football namespace

} // futsim namespace
