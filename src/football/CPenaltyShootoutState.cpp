#include "football/CPenaltyShootoutState.h"

#include "JsonUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Advances to the next shooter.
 * @details Cycles through the shooters when end is reached.
 * @param aShooterIt Shooter iterator.
 * @param aShooters Shooters.
*/
void AdvanceShooter( detail::shooters::const_iterator& aShooterIt, const detail::shooters& aShooters ) noexcept;

/**
 * @brief Returns the team taking the next penalty.
 * @tparam tPenaltySequence Penalty sequence in use.
 * @param aHomeTeamShoot Whether the home team took the last penalty.
 * @param aPenaltyCount Total number of penalties taken.
*/
template <E_PENALTY_SEQUENCE tPenaltySequence> bool NextHomeTeamShoot( const bool aHomeTeamShoot, const std::size_t& aPenaltyCount );

template <> bool NextHomeTeamShoot<E_PENALTY_SEQUENCE::AB>( const bool aHomeTeamShoot, const std::size_t& )
{
	return !aHomeTeamShoot;
}

template <> bool NextHomeTeamShoot<E_PENALTY_SEQUENCE::ABBA>( const bool aHomeTeamShoot, const std::size_t& aPenaltyCount )
{
	return aPenaltyCount & 1 ? !aHomeTeamShoot : aHomeTeamShoot;
}

} // anonymous namespace

template <bool tHomeTeam> void CPenaltyShootoutState::score::Add() noexcept
{
	if constexpr( tHomeTeam )
		++home;
	else
		++away;
}

template void CPenaltyShootoutState::score::Add<true>() noexcept;
template void CPenaltyShootoutState::score::Add<false>() noexcept;

void CPenaltyShootoutState::JSON( json& aJSON ) const noexcept
{
	for( auto& JSONPenalties = aJSON[ json_traits<CPenaltyShootoutState>::PENALTIES ]; const auto & penalty : mPenalties )
	{
		json elementJSON;
		AddToJSONKey( elementJSON, penalty.homeTeam, json_traits<CPenaltyShootoutState>::HOME_TEAM_PENALTY );
		AddToJSON( elementJSON, penalty.state );
		JSONPenalties.push_back( std::move( elementJSON ) );
	}
}

const CPenaltyShootoutState::penalty_states& CPenaltyShootoutState::GetPenalties() const noexcept
{
	return mPenalties;
}

template <bool tHomeTeam> void CPenaltyShootoutState::PushPenaltyState( CPenaltyState&& aPenaltyState,
	detail::shooters::const_iterator& aShooterIt, const detail::shooters& aShooters, score& aScore ) noexcept
{
	mPenalties.emplace_back( tHomeTeam, std::move( aPenaltyState ) );
	if( mPenalties.back().state.GetChanceOutcome() == types::CGoalDrawConfiguration::E_CHANCE_OUTCOME::GOAL )
		aScore.Add<tHomeTeam>();
	else
		aScore.Add<!tHomeTeam>();
	AdvanceShooter( aShooterIt, aShooters );
}

template void CPenaltyShootoutState::PushPenaltyState<true>( CPenaltyState&&, detail::shooters::const_iterator&, const detail::shooters&, score& ) noexcept;
template void CPenaltyShootoutState::PushPenaltyState<false>( CPenaltyState&&, detail::shooters::const_iterator&, const detail::shooters&, score& ) noexcept;

bool CPenaltyShootoutState::IsDecided( const types::CPenaltyShootoutConfiguration::penalty_count& aMinPenaltyCount,
	const score& aScore ) const noexcept
{
	return std::abs( static_cast<int>( aScore.home - aScore.away ) ) >= 2 &&
		( aScore.home > aMinPenaltyCount || aScore.away > aMinPenaltyCount );
}

namespace detail
{

std::function<bool( const bool, const std::size_t& )> NextHomeTeamShoot( const E_PENALTY_SEQUENCE& aPenaltySequence )
{
	switch( aPenaltySequence )
	{
	case E_PENALTY_SEQUENCE::AB:
		return &football::NextHomeTeamShoot<E_PENALTY_SEQUENCE::AB>;
	default:
		return &football::NextHomeTeamShoot<E_PENALTY_SEQUENCE::ABBA>;
	}
}

} // detail namespace

namespace
{

void AdvanceShooter( detail::shooters::const_iterator& aShooterIt, const detail::shooters& aShooters ) noexcept
{
	if( ++aShooterIt == aShooters.cend() )
		aShooterIt = aShooters.cbegin();
}

} // anonymous namespace

}  // futsim::football namespace