#include "IJsonable.h"

namespace futsim
{

IJsonable::json IJsonable::ToJSON() const noexcept
{
	return this->JSON();
}


} // futsim namespace