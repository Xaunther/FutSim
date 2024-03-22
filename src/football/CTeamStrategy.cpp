#include "football/CTeamStrategy.h"

#include "football/CMatch.h"
#include "football/CMatchConfiguration.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace futsim::football
{

namespace
{

/**
 * @brief Applies the given predicate to the effective skill of each player in a given position.
 * @tparam tPlayerPosition Players position.
 * @param aPlayerSkill Player skill to consider.
 * @param aTeam Team definition.
 * @param aTacticConfiguration Tactic configuration.
 * @param aGlobalSkillBonus Skill bonus to apply to each player apart from the tactic's.
 * @param aPredicate Predicate to evalluate.
*/
template <E_PLAYER_POSITION tPlayerPosition>
void ForEachPlayerSkill( const E_PLAYER_SKILL& aPlayerSkill, const CTeam& aTeam, const CLineup& aLineup,
	const CTacticConfiguration& aTacticConfiguration, const types::CTacticConfiguration::skill_bonus& aGlobalSkillBonus,
	const std::function<void( const types::CTacticConfiguration::skill_bonus& )>& aPredicate );

template <E_PLAYER_POSITION tPlayerPosition> auto CreatePlayersView( const CLineup& aLineup )
{
	if constexpr( tPlayerPosition == E_PLAYER_POSITION::GK )
		return std::ranges::views::single( aLineup.GetPlayers<tPlayerPosition>() );
	else
		return std::ranges::views::all( aLineup.GetPlayers<tPlayerPosition>() );
}

} // anonymous namespace

CTeamStrategy::CTeamStrategy(
	const std::string_view aTacticID,
	const CLineup& aLineup
) try :
	mTacticID( aTacticID ),
	mLineup( aLineup )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team strategy." )

CTeamStrategy::CTeamStrategy( const json& aJSON ) try :
	mTacticID( ValueFromRequiredJSONKey<id>( aJSON, JSON_TACTIC ) ),
	mLineup( ValueFromRequiredJSONKey<CLineup>( aJSON ) )
{
}
FUTSIM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the team strategy from JSON." )

void CTeamStrategy::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mTacticID, JSON_TACTIC );
	AddToJSONKey( aJSON, mLineup );
}

std::string_view CTeamStrategy::GetTacticID() const noexcept
{
	return mTacticID;
}

const CLineup& CTeamStrategy::GetLineup() const noexcept
{
	return mLineup;
}

void CTeamStrategy::ForEachPlayerSkill( const E_PLAYER_SKILL& aPlayerSkill, const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration, const bool aIsHomeTeam,
	const CTeamStrategy& aOtherStrategy, const std::function<void( const skill_bonus& )>& aPredicate ) const
{
	const auto& team = aIsHomeTeam ? aMatch.GetHomeTeam() : aMatch.GetAwayTeam();
	const auto& tacticConfiguration = aMatchConfiguration.GetTacticsConfiguration().GetTacticConfigurations().at( mTacticID );
	const auto& globalSkillBonus = ( aMatchConfiguration.AppliesAmbientFactor() && aIsHomeTeam ?
		team.GetSupportFactor() * aMatch.GetStadium().GetAmbientFactor() : 1 )
		* ( tacticConfiguration.GetFavourableTactics().contains( aOtherStrategy.GetTacticID().data() ) ?
			aMatchConfiguration.GetTacticsConfiguration().GetFavourableTacticSkillBonus() : 1 );

	football::ForEachPlayerSkill<E_PLAYER_POSITION::GK>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::DF>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::DM>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::MF>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::AM>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::FW>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
}

namespace
{

template <E_PLAYER_POSITION tPlayerPosition>
void ForEachPlayerSkill( const E_PLAYER_SKILL& aPlayerSkill, const CTeam& aTeam, const CLineup& aLineup,
	const CTacticConfiguration& aTacticConfiguration, const types::CTacticConfiguration::skill_bonus& aGlobalSkillBonus,
	const std::function<void( const types::CTacticConfiguration::skill_bonus& )>& aPredicate )
{
	const auto& skillBonus = aTacticConfiguration.GetSkillBonus( tPlayerPosition, aPlayerSkill );
	for( const auto& player : CreatePlayersView<tPlayerPosition>( aLineup ) )
		aPredicate( aTeam.GetPlayer( player ).GetPlayerSkills().GetSkill( aPlayerSkill ) * aGlobalSkillBonus * skillBonus );
}

} // anonymous namespace

} // futsim::football namespace