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
	include/football/CFoulDrawConfiguration.h
	include/football/CFoulState.h
	include/football/CGoalDrawConfiguration.h
	include/football/CLineup.h
	include/football/CLineupConfiguration.h
	include/football/CMatch.h
	include/football/CMatchConfiguration.h
	include/football/CTeamStrategy.h
	include/football/CPenaltyShootoutConfiguration.h
	include/football/CPenaltyShootoutState.h
	include/football/CPenaltyState.h
	include/football/CPeriodState.h
	include/football/CPeriodStates.h
	include/football/CPlayer.h
	include/football/CPlayerSkills.h
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
	include/football/types/CChancesDrawConfiguration.h
	include/football/types/CChanceState.h
	include/football/types/CDrawConfiguration.h
	include/football/types/CFoulDrawConfiguration.h
	include/football/types/CGoalDrawConfiguration.h
	include/football/types/CLineup.h
	include/football/types/CLineupConfiguration.h
	include/football/types/CMatchConfiguration.h
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
	src/football/CFoulDrawConfiguration.cpp
	src/football/CFoulState.cpp
	src/football/CGoalDrawConfiguration.cpp
	src/football/CLineup.cpp
	src/football/CLineupConfiguration.cpp
	src/football/CMatch.cpp
	src/football/CMatchConfiguration.cpp
	src/football/CTeamStrategy.cpp
	src/football/CPenaltyShootoutConfiguration.cpp
	src/football/CPenaltyShootoutState.cpp
	src/football/CPenaltyState.cpp
	src/football/CPeriodState.cpp
	src/football/CPeriodStates.cpp
	src/football/CPlayerSkills.cpp
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
)

# External headers
SET(FUTSIM_EXTERNAL_HEADERS
	${FUTSIM_CORE_EXTERNAL_HEADERS}
	${FUTSIM_FOOTBALL_EXTERNAL_HEADERS}
)