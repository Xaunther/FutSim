#include "IJsonable.h"

namespace futsim
{

void IJsonable::ToJSON( json& aJSON ) const noexcept
{
	this->JSON( aJSON );
}


} // futsim namespace