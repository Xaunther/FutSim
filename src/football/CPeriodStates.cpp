#include "football/CPeriodStates.h"

#include "JsonUtils.h"

namespace futsim::football
{

bool CPeriodStates::SDefaultPeriodPolicy::operator()( const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPeriodStates.size() < aMatchConfiguration.GetPlayTime().GetPeriodCount();
}

bool CPeriodStates::SDefaultExtraTimePeriodPolicy::operator()(
	const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const
{
	return aPeriodStates.size() < aMatchConfiguration.GetExtraTime()->GetPeriodCount();
}

const CMatchConfiguration& CPeriodStates::SDefaultExtraTimePeriodPolicy::CheckMatchConfiguration( const CMatchConfiguration& aMatchConfiguration )
{
	return CPeriodState::SDefaultExtraTimePeriodPlayPolicy::CheckMatchConfiguration( aMatchConfiguration );
}

bool CPeriodStates::SSilverGoalPeriodPolicy::operator()(
	const period_states& aPeriodStates, const CMatchConfiguration& aMatchConfiguration ) const
{
	if( !SDefaultExtraTimePeriodPolicy::operator()( aPeriodStates, aMatchConfiguration ) )
		return false;

	// We only need to check the goals scored in the last period
	const auto& homeScoredGoals = aPeriodStates.back().CountScoredGoals( true );
	const auto& awayScoredGoals = aPeriodStates.back().CountScoredGoals( false );
	return homeScoredGoals == awayScoredGoals && ( !aMatchConfiguration.GetTieCondition()->GetHomeTeamGoals() || homeScoredGoals == 0 );
}

void CPeriodStates::JSON( json& aJSON ) const noexcept
{
	AddKeyArrayToJSON( aJSON, mStates );
}

const CPeriodStates::period_states& CPeriodStates::GetStates() const noexcept
{
	return mStates;
}

CPeriodStates::goal_count CPeriodStates::CountScoredGoals( const bool aHomeTeam ) const noexcept
{
	return std::accumulate( mStates.cbegin(), mStates.cend(), goal_count{ 0 }, [ &aHomeTeam ]
	( const auto& aSum, const auto& aPeriodState ) { return aSum + aPeriodState.CountScoredGoals( aHomeTeam ); } );
}

} // futsim::football namespace