#include "football/CGoalRule.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Creates the goal rule from JSON.
 * @param aJSON JSON object.
 */
CGoalRule::variant CreateRuleFromJSON( const types::IJsonable::json& aJSON );

} // anonymous namespace

template <has_type_c<CGoalRule::variant> T> CGoalRule::CGoalRule( const T& aRule ) noexcept :
	mRule( aRule )
{
}

template CGoalRule::CGoalRule( const CGoalRule::NO& );
template CGoalRule::CGoalRule( const CGoalRule::SILVER_GOAL& );
template CGoalRule::CGoalRule( const CGoalRule::GOLDEN_GOAL& );

CGoalRule::CGoalRule( const json& aJSON ) try :
	mRule( CreateRuleFromJSON( aJSON ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the goal rule." )

namespace
{

CGoalRule::variant CreateRuleFromJSON( const types::IJsonable::json& aJSON )
{
	const auto value = ValueFromJSON<std::string_view>( aJSON );
	if( value == json_traits<CGoalRule>::NO_KEY ) return CGoalRule::NO{};
	if( value == json_traits<CGoalRule>::SILVER_GOAL_KEY ) return CGoalRule::SILVER_GOAL{};
	if( value == json_traits<CGoalRule>::GOLDEN_GOAL_KEY ) return CGoalRule::GOLDEN_GOAL{};
	throw std::invalid_argument{ "'" + std::string{ value.data() } + "' is not a valid goal rule." };
}

} // anonymous namespace

} // futsim::football namespace
