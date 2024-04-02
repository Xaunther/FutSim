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
 * @brief Calculates the effective player skill.
 * @param aAmbientFactor Stadium ambient factor
 * @param aMatchConfiguration Match configuration
 * @param aSupportFactor Fan support factor.
 * @param aTacticConfiguration Tactic configuration.
 * @param aIsHomeTeam Whether the team is the home team.
 * @param aOtherStrategy Rival team's strategy.
*/
types::CTacticConfiguration::skill_bonus CalculateGlobalSkillBonus( const types::CStadium::ambient_factor& aAmbientFactor,
	const CMatchConfiguration& aMatchConfiguration, const types::CTeam::support_factor& aSupportFactor,
	const CTacticConfiguration& aTacticConfiguration, const bool aIsHomeTeam, const CTeamStrategy& aOtherStrategy );

/**
 * @brief Calculates the effective player skill.
 * @param aTeam Team definition.
 * @param aPlayer Player to consider.
 * @param aPlayerSkill Player skill to consider.
 * @param aTacticSkillBonus Tactic skill bonus.
 * @param aGlobalSkillBonus Skill bonus to apply apart from the tactic's.
*/
types::CTacticConfiguration::skill_bonus CalculateEffectivePlayerSkill( const CTeam& aTeam, const std::string_view aPlayer,
	const E_PLAYER_SKILL& aPlayerSkill, const types::CStadium::ambient_factor& aTacticSkillBonus,
	const types::CStadium::ambient_factor& aGlobalSkillBonus );

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

CTeamStrategy::skill_bonus CTeamStrategy::CalculateEffectivePlayerSkill( const std::string_view aPlayer, const E_PLAYER_SKILL& aPlayerSkill,
	const E_PLAYER_POSITION& aPlayerPosition, const CMatch& aMatch, const CMatchConfiguration& aMatchConfiguration,
	const bool aIsHomeTeam, const std::string_view aTacticID, const CTeamStrategy& aOtherStrategy )
{
	const auto& team = aIsHomeTeam ? aMatch.GetHomeTeam() : aMatch.GetAwayTeam();
	const auto& tacticConfiguration = aMatchConfiguration.GetTacticsConfiguration().GetTacticConfigurations().at( aTacticID.data() );
	return football::CalculateEffectivePlayerSkill( team, aPlayer, aPlayerSkill, tacticConfiguration.GetSkillBonus( aPlayerPosition, aPlayerSkill ),
		CalculateGlobalSkillBonus( aMatch.GetStadium().GetAmbientFactor(), aMatchConfiguration,
			team.GetSupportFactor(), tacticConfiguration, aIsHomeTeam, aOtherStrategy )
		* team.GetPlayer( aPlayer ).GetPlayerSkills().GetSkill( aPlayerSkill )
		* tacticConfiguration.GetSkillBonus( aPlayerPosition, aPlayerSkill ) );
}

void CTeamStrategy::ForEachPlayerSkill( const E_PLAYER_SKILL& aPlayerSkill, const CMatch& aMatch,
	const CMatchConfiguration& aMatchConfiguration, const bool aIsHomeTeam,
	const CTeamStrategy& aOtherStrategy, const std::function<void( const skill_bonus& )>& aPredicate ) const
{
	const auto& team = aIsHomeTeam ? aMatch.GetHomeTeam() : aMatch.GetAwayTeam();
	const auto& tacticConfiguration = aMatchConfiguration.GetTacticsConfiguration().GetTacticConfigurations().at( mTacticID );
	const auto& globalSkillBonus = CalculateGlobalSkillBonus( aMatch.GetStadium().GetAmbientFactor(), aMatchConfiguration,
		team.GetSupportFactor(), tacticConfiguration, aIsHomeTeam, aOtherStrategy );

	football::ForEachPlayerSkill<E_PLAYER_POSITION::GK>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::DF>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::DM>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::MF>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::AM>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
	football::ForEachPlayerSkill<E_PLAYER_POSITION::FW>( aPlayerSkill, team, mLineup, tacticConfiguration, globalSkillBonus, aPredicate );
}

namespace
{

types::CTacticConfiguration::skill_bonus CalculateGlobalSkillBonus( const types::CStadium::ambient_factor& aAmbientFactor,
	const CMatchConfiguration& aMatchConfiguration, const types::CTeam::support_factor& aSupportFactor,
	const CTacticConfiguration& aTacticConfiguration, const bool aIsHomeTeam, const CTeamStrategy& aOtherStrategy )
{
	return ( aMatchConfiguration.AppliesAmbientFactor() && aIsHomeTeam ? aSupportFactor * aAmbientFactor : 1 )
		* ( aTacticConfiguration.GetFavourableTactics().contains( aOtherStrategy.GetTacticID().data() ) ?
			aMatchConfiguration.GetTacticsConfiguration().GetFavourableTacticSkillBonus() : 1 );
}

types::CTacticConfiguration::skill_bonus CalculateEffectivePlayerSkill( const CTeam& aTeam, const std::string_view aPlayer,
	const E_PLAYER_SKILL& aPlayerSkill, const types::CStadium::ambient_factor& aTacticSkillBonus,
	const types::CStadium::ambient_factor& aGlobalSkillBonus )
{
	return aTeam.GetPlayer( aPlayer ).GetPlayerSkills().GetSkill( aPlayerSkill ) * aGlobalSkillBonus * aTacticSkillBonus;
}

template <E_PLAYER_POSITION tPlayerPosition>
void ForEachPlayerSkill( const E_PLAYER_SKILL& aPlayerSkill, const CTeam& aTeam, const CLineup& aLineup,
	const CTacticConfiguration& aTacticConfiguration, const types::CTacticConfiguration::skill_bonus& aGlobalSkillBonus,
	const std::function<void( const types::CTacticConfiguration::skill_bonus& )>& aPredicate )
{
	const auto& skillBonus = aTacticConfiguration.GetSkillBonus( tPlayerPosition, aPlayerSkill );
	for( const auto& player : CreatePlayersView<tPlayerPosition>( aLineup ) )
		aPredicate( CalculateEffectivePlayerSkill( aTeam, player, aPlayerSkill, skillBonus, aGlobalSkillBonus ) );
}

} // anonymous namespace

} // futsim::football namespace