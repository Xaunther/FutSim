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