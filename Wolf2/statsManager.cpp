#include "statsManager.h"



idStat* statsManager::getPlayerStat(gameStat_t statEnum) {

	idPlayerMetrics* playerMetrics = idGameLocalManager::getidPlayerMetrics();
	if (!playerMetrics) {
		logWarn("getStatInt: playerMetrics is nullptr");
		return nullptr;
	}

	idList* statsList = (idList*) &playerMetrics->stats;
	if (!statsList) {
		return nullptr;
	}

	if (statEnum < 0 || (int)statEnum >= statsList->num) {
		logWarn("getStatInt: statEnum %d out of bounds", statEnum);
		return nullptr;
	}

	//logInfo("statsList: %p statsList->list: %p", statsList, statsList->list);
	//logInfo("sizeof(idStat): %zu", sizeof(idStat));
	//idStat* stat = (idStat*)(statsList->list + statEnum * sizeof(idStat));
	/*idStat stats[m_statsListSize];
	idStat* stat = (idStat*) &statsList->list[statEnum];*/
	//idStat* stat = (idStat*) ((__int64)statsList->list + (statEnum * sizeof(idStat)));	
	return (idStat*) ((__int64)statsList->list + (statEnum * sizeof(idStat)));	


	/*if (!stat) {
		return StatErrorVal;
	}*/

	/*logInfo("getStatInt dbg: stat addr: %p  &stat->sessionValue: %p", stat, &stat->sessionValue);*/

	//return stat->sessionValue;
	
}


int statsManager::getStatInt(gameStat_t statEnum) {

	idStat* idStatPtr = getPlayerStat(statEnum);
	if (idStatPtr) {
		 return idStatPtr->sessionValue;
	}
	logWarn("getStatInt: returning StatErrorVal");
	return m_StatErrorVal;
}


std::string statsManager::getStatAsStr(gameStat_t statEnum) {

	std::string statNameStr =  TypeInfoManager::getEnumMemberName("gameStat_t", (long long)statEnum);	
	
	int statSessionValueInt = m_StatErrorVal;
	idStat* idStatPtr = getPlayerStat(statEnum);
	if (idStatPtr) {
		statSessionValueInt = idStatPtr->sessionValue;
	}	

	return statNameStr + ": " + std::to_string(statSessionValueInt);
}


std::vector<std::string> statsManager::getStatsStrVecForImgui(const std::vector< gameStat_t>& gameStats) {

	std::vector<std::string> resultVec;

	for (gameStat_t stat_t : gameStats) {
		resultVec.push_back(getStatAsStr(stat_t));
	}

	return resultVec;
}


void statsManager::debugLogStats() {

	idPlayerMetrics* playerMetrics = idGameLocalManager::getidPlayerMetrics();

	logInfo("debugLogStats: (playerMetrics: %p) ", playerMetrics);

	for (const auto& statEnum : GameStatsEnums) {
		
		idStat* idStatPtr = getPlayerStat(statEnum);
		if (idStatPtr) {
			logInfo(" stat idStatPtr: %p  sessionValue: %d aggregatedValue: %d", idStatPtr, idStatPtr->sessionValue, idStatPtr->aggregatedValue );
		}
	}
}


std::vector<std::string> statsManager::getStatsStrForImgui() {

	std::vector<std::string> resultVec;

	std::string throwAxeStr = "Kills Throw Axe: ";
	throwAxeStr += std::to_string(statsManager::getStatInt(gameStat_t::STAT_KILLS_THROWN_AXE));
	resultVec.push_back(throwAxeStr);
	
	//? doessn't work, no data. will have to compute ourself...
	/*std::string AccuracyStr = "Accuracy: ";
	AccuracyStr += std::to_string(statsManager::getStatInt(gameStat_t::STAT_ACCURACY));
	resultVec.push_back(throwAxeStr);*/

	std::string ShotsStr = "Shots: ";
	ShotsStr += std::to_string(statsManager::getStatInt(gameStat_t::STAT_SHOTS));
	resultVec.push_back(ShotsStr);

	std::string weaponsHitsForAccStr = "Weapon Hits (for Acc): ";
	weaponsHitsForAccStr += std::to_string(statsManager::getStatInt(gameStat_t::STAT_WEAPON_HITS_FOR_ACCURACY));
	resultVec.push_back(weaponsHitsForAccStr);

	std::string weaponsHitsEnemyStr = "Weapon Hits Enemy: ";
	weaponsHitsEnemyStr += std::to_string(statsManager::getStatInt(gameStat_t::STAT_WEAPON_HIT_ENEMY));
	resultVec.push_back(weaponsHitsEnemyStr);

	std::string totalKillsStr = "Total Kills: ";
	totalKillsStr += std::to_string(statsManager::getStatInt(gameStat_t::STAT_TOTAL_KILLS));
	resultVec.push_back(totalKillsStr);


	std::string stealthKillsStr = "Stealth Kills: ";
	stealthKillsStr += std::to_string(statsManager::getStatInt(gameStat_t::STAT_KILLS_STEALTH));
	resultVec.push_back(stealthKillsStr);

	std::string distanceTravelledStr = "Distance Travelled: ";
	distanceTravelledStr += std::to_string(statsManager::getStatInt(gameStat_t::STAT_DISTANCE_TRAVELED));
	resultVec.push_back(distanceTravelledStr);



	return resultVec;
}