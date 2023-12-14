#include "ITest.h"

#include "football/CPlayerSkills.h"

#include <iostream>

using namespace futsim::football;

INITIALIZE_TEST( TPlayerSkills )

void TPlayerSkills::DoRun() const
{
	//! Test member constructor
	CheckException( []() { CPlayerSkills{ 0, 1, 1, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 0, 1, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 1, 0, 1, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
	CheckException( []() { CPlayerSkills{ 1, 1, 1, 0, 1, 1, 1, 1 }; }, "The skill value must be greater than 0." );
}
