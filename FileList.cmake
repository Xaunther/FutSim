# Core external headers
SET(FUTSIM_CORE_EXTERNAL_HEADERS
	include/Config.h
	include/CPerson.h
	include/CPlayTime.h
	include/CPlayTimeTypes.h
	include/ENationality.h
	include/ExceptionUtils.h
	include/IJsonable.h
	include/IJsonableTypes.h
	include/JsonUtils.h
	include/NameUtils.h
)

# Football external headers
SET(FUTSIM_FOOTBALL_EXTERNAL_HEADERS
	include/football/CExtraTime.h
	include/football/CMatch.h
	include/football/CMatchConfiguration.h
	include/football/CMatchConfigurationTypes.h
	include/football/CPenaltyShootoutConfiguration.h
	include/football/CPenaltyShootoutConfigurationTypes.h
	include/football/CPlayer.h
	include/football/CPlayerSkills.h
	include/football/CPlayerSkillsTypes.h
	include/football/CPlayTime.h
	include/football/CPlayTimeTypes.h
	include/football/CStadium.h
	include/football/CStadiumTypes.h
	include/football/CTeam.h
	include/football/CTeamTypes.h
	include/football/CTieCondition.h
	include/football/CTieConditionTypes.h
	include/football/EGoalRule.h
	include/football/EPenaltySequence.h
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
	src/football/CExtraTime.cpp
	src/football/CMatch.cpp
	src/football/CPenaltyShootoutConfiguration.cpp
	src/football/CPlayerSkills.cpp
	src/football/CPlayer.cpp
	src/football/CPlayTime.cpp
	src/football/CStadium.cpp
	src/football/CTeam.cpp
	src/football/CTieCondition.cpp
)

# External headers
SET(FUTSIM_EXTERNAL_HEADERS
	${FUTSIM_CORE_EXTERNAL_HEADERS}
	${FUTSIM_FOOTBALL_EXTERNAL_HEADERS}
)