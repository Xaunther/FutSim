#include "football/CGoalRule.h"

namespace futsim::football
{

template <has_type_c<CGoalRule::variant> T> CGoalRule::CGoalRule( const T& aRule ) noexcept :
	mRule( aRule )
{
}

template CGoalRule::CGoalRule( const CGoalRule::NO& );
template CGoalRule::CGoalRule( const CGoalRule::SILVER_GOAL& );
template CGoalRule::CGoalRule( const CGoalRule::GOLDEN_GOAL& );

} // futsim::football namespace
