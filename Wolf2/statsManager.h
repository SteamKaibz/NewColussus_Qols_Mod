#pragma once

#include "idGameLocalManager.h"
#include "TypeInfoManager.h"



enum class StatColor_K {
	DEFAULT,
	RED
};


struct StatLine_K {
	StatColor_K color = StatColor_K::DEFAULT;
	std::string statStr = "???";
};

/// <summary>
/// There are actually very few stats tracked per session even if the enums has a lot of fields.
/// </summary>
class statsManager
{
private:

	static inline const int m_StatErrorVal = -1;
	static inline const int m_statsListSize = 420;

public:


	static inline const std::vector< gameStat_t> GameStatsEnums = { STAT_SHOTS , STAT_ACCURACY, STAT_WEAPON_HITS_FOR_ACCURACY , STAT_TOTAL_KILLS, STAT_WEAPON_HIT_ENEMY ,STAT_KILLS_STEALTH, STAT_KILLS, STAT_KILLS_HEADSHOT, STAT_EQUIPMENT_KILL_COUNT, STAT_WEAPON_DAMAGE_TO_GENERAL, STAT_WEAPON_KILLED_ENEMY, STAT_WEAPON_HEADSHOT_ENEMY, STAT_SECRETS, STAT_SECRETS_FOUND, STAT_LEVEL, STAT_TIME_PLAYED, STAT_XP, STAT_TIME_IN_GAME };


public:

	static idStat* getPlayerStat(gameStat_t statEnum);

	static int getStatInt(gameStat_t gameStat);

	static std::string getStatAsStr(gameStat_t statEnum);

	static std::vector<std::string> getStatsStrVecForImgui(const std::vector<gameStat_t>& gameStats);

	static void debugLogStats();

	static std::vector<std::string> getStatsStrForImgui();


};

