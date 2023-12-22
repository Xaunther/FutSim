#pragma once

#include "IJsonable.h"

#include "CStadiumTypes.h"

namespace futsim
{

namespace football
{

class CStadium : public IJsonable
{
	using json = IJsonableTypes::json;
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

} // football namespace

} // futsim namespace