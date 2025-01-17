# Core external headers
SET(FUTSIM_CORE_EXTERNAL_HEADERS
	include/CEnumDistribution.h
	include/Config.h
	include/CPerson.h
	include/CPlayTime.h
	include/ENationality.h
	include/EnumUtils.h
	include/ExceptionUtils.h
	include/IJsonable.h
	include/JsonUtils.h
	include/NameUtils.h
	include/NumberUtils.h
	include/ProbabilityUtils.h
	include/traits/CPerson.h
	include/traits/CPlayTime.h
	include/traits/default.h
	include/traits/json.h
	include/types/CPerson.h
	include/types/CPlayTime.h
	include/types/IJsonable.h
)

# Football external headers
SET(FUTSIM_FOOTBALL_EXTERNAL_HEADERS
	include/football/CChancesDrawConfiguration.h
	include/football/CChanceState.h
	include/football/CDrawConfiguration.h
	include/football/CExtraTime.h
	include/football/CExtraTimePeriodPlayPolicy.h
	include/football/CExtraTimePeriodPolicy.h
	include/football/CFoulDrawConfiguration.h
	include/football/CFoulState.h
	include/football/CGoalDrawConfiguration.h
	include/football/CLineup.h
	include/football/CLineupConfiguration.h
	include/football/CMatch.h
	include/football/CMatchConfiguration.h
	include/football/CMatchState.h
	include/football/CTeamStrategy.h
	include/football/CPenaltyShootoutConfiguration.h
	include/football/CPenaltyShootoutState.h
	include/football/CPenaltyState.h
	include/football/CPeriodPlayPolicy.h
	include/football/CPeriodPolicy.h
	include/football/CPeriodState.h
	include/football/CPeriodStates.h
	include/football/CPlayer.h
	include/football/CPlayerSkills.h
	include/football/CPlayerState.h
	include/football/CPlayState.h
	include/football/CPlayTime.h
	include/football/CPossessionDrawConfiguration.h
	include/football/CPossessionState.h
	include/football/CStadium.h
	include/football/CTacticConfiguration.h
	include/football/CTacticsConfiguration.h
	include/football/CTeam.h
	include/football/CTieCondition.h
	include/football/EGoalRule.h
	include/football/EPenaltySequence.h
	include/football/EPlayerPosition.h
	include/football/EPlayerSkill.h
	include/football/IExtraTimePeriodPlayPolicy.h
	include/football/IExtraTimePeriodPolicy.h
	include/football/IPeriodPlayPolicy.h
	include/football/IPeriodPolicy.h
	include/football/traits/CChancesDrawConfiguration.h
	include/football/traits/CChanceState.h
	include/football/traits/CDrawConfiguration.h
	include/football/traits/CExtraTime.h
	include/football/traits/CFoulDrawConfiguration.h
	include/football/traits/CFoulState.h
	include/football/traits/CGoalDrawConfiguration.h
	include/football/traits/CLineupConfiguration.h
	include/football/traits/CLineup.h
	include/football/traits/CMatchConfiguration.h
	include/football/traits/CMatch.h
	include/football/traits/CMatchState.h
	include/football/traits/CPenaltyShootoutConfiguration.h
	include/football/traits/CPenaltyShootoutState.h
	include/football/traits/CPenaltyState.h
	include/football/traits/CPeriodState.h
	include/football/traits/CPeriodStates.h
	include/football/traits/CPlayer.h
	include/football/traits/CPlayerSkills.h
	include/football/traits/CPlayState.h
	include/football/traits/CPlayTime.h
	include/football/traits/CPossessionDrawConfiguration.h
	include/football/traits/CPossessionState.h
	include/football/traits/CStadium.h
	include/football/traits/CTacticConfiguration.h
	include/football/traits/CTacticsConfiguration.h
	include/football/traits/CTeam.h
	include/football/traits/CTeamStrategy.h
	include/football/traits/CTieCondition.h
	include/football/types/CChancesDrawConfiguration.h
	include/football/types/CChanceState.h
	include/football/types/CDrawConfiguration.h
	include/football/types/CFoulDrawConfiguration.h
	include/football/types/CGoalDrawConfiguration.h
	include/football/types/CLineup.h
	include/football/types/CLineupConfiguration.h
	include/football/types/CMatchConfiguration.h
	include/football/types/CMatchState.h
	include/football/types/CPenaltyShootoutConfiguration.h
	include/football/types/CPenaltyShootoutState.h
	include/football/types/CPeriodState.h
	include/football/types/CPeriodStates.h
	include/football/types/CPlayerSkills.h
	include/football/types/CPlayState.h
	include/football/types/CPlayTime.h
	include/football/types/CPossessionDrawConfiguration.h
	include/football/types/CPossessionState.h
	include/football/types/CStadium.h
	include/football/types/CTacticConfiguration.h
	include/football/types/CTacticsConfiguration.h
	include/football/types/CTeam.h
	include/football/types/CTieCondition.h
)

# Core source files
SET(FUTSIM_CORE_SOURCE
	src/CPerson.cpp
	src/CPlayTime.cpp
	src/IJsonable.cpp
	src/NameUtils.cpp
)

# Football source files
SET(FUTSIM_FOOTBALL_SOURCE
	src/football/CChancesDrawConfiguration.cpp
	src/football/CChanceState.cpp
	src/football/CDrawConfiguration.cpp
	src/football/CExtraTime.cpp
	src/football/CExtraTimePeriodPlayPolicy.cpp
	src/football/CExtraTimePeriodPolicy.cpp
	src/football/CFoulDrawConfiguration.cpp
	src/football/CFoulState.cpp
	src/football/CGoalDrawConfiguration.cpp
	src/football/CLineup.cpp
	src/football/CLineupConfiguration.cpp
	src/football/CMatch.cpp
	src/football/CMatchConfiguration.cpp
	src/football/CMatchState.cpp
	src/football/CTeamStrategy.cpp
	src/football/CPenaltyShootoutConfiguration.cpp
	src/football/CPenaltyShootoutState.cpp
	src/football/CPenaltyState.cpp
	src/football/CPeriodPlayPolicy.cpp
	src/football/CPeriodPolicy.cpp
	src/football/CPeriodState.cpp
	src/football/CPeriodStates.cpp
	src/football/CPlayerSkills.cpp
	src/football/CPlayerState.cpp
	src/football/CPlayer.cpp
	src/football/CPlayState.cpp
	src/football/CPlayTime.cpp
	src/football/CPossessionDrawConfiguration.cpp
	src/football/CPossessionState.cpp
	src/football/CStadium.cpp
	src/football/CTacticConfiguration.cpp
	src/football/CTacticsConfiguration.cpp
	src/football/CTeam.cpp
	src/football/CTieCondition.cpp
	src/football/IExtraTimePeriodPlayPolicy.cpp
	src/football/IExtraTimePeriodPolicy.cpp
	src/football/IPeriodPlayPolicy.cpp
	src/football/IPeriodPolicy.cpp
)

# External headers
SET(FUTSIM_EXTERNAL_HEADERS
	${FUTSIM_CORE_EXTERNAL_HEADERS}
	${FUTSIM_FOOTBALL_EXTERNAL_HEADERS}
)
