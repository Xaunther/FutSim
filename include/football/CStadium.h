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

	//! Stadium name.
	std::string mName;
	//! Stadium capacity.
	capacity mCapacity;
	//! Ambient factor that dictates the support the home team receives.
	ambient_factor mAmbientFactor;
};

} // football namespace

} // futsim namespace