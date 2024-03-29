#include "idInventoryManager.h"



void idInventoryManager::giveWeaponItem(std::string declName)
{
	giveItem("idDeclWeapon", declName);

}

void idInventoryManager::giveUpgradeItem(std::string declName)
{
	giveItem("idDeclUpgrade", declName);

}


void idInventoryManager::giveItem(std::string declClassName, std::string declName)
{
	//auto declWeapon = idResourceManager::getDeclByName("idDeclWeapon", "weapon/player/sp/lasergewehr");
	auto decl = idResourceManager::getDeclByName(declClassName, declName);
	if (!decl) {
		logErr("giveItem: can not give item decl is null");
		return;
	}

	logInfo("giveItem: debug found: %p", decl);

	auto idplayer = idGameLocalManager::getIdPlayer();
	if (!idplayer) {
		logErr("giveItem: can not give item idPlayer is bad ptr");
		return;
	}
	__int64 idplayerAddr = (__int64)idplayer;


	auto idInventoryCollectionAddr = (*(__int64(__fastcall**)(__int64))(*(__int64*)idplayerAddr + 0x5B8i64))(idplayerAddr);



	if (idInventoryCollectionAddr) {
		//giveItem_1064010(idInventoryCollection_v58, idEntity_a1, idDeclInventoryMB_v56, countMB_57, 0xFFFFFFFF, 0);

		//logInfo("logInfo: idInventoryCollectionAddr is %p", (void*)idInventoryCollectionAddr);

		//! result: matches @ 0x1064010, sig direct: 44 89 4C 24 ? 4C 89 44 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 C7 45 ? ? ? ? ? 41 8B F1
		auto giveItemFp = reinterpret_cast<GiveItemFp>(MemHelper::getFuncAddr(0x1064010));
		//logInfo("logInfo: giveItemFp is %p", giveItemFp);

		giveItemFp(idInventoryCollectionAddr, idplayerAddr, (__int64)decl, 1, 0, 0);
	}

}

//? doesn't work
//void idInventoryManager::GiveInventoryFromDevInvLoadout() {
//
//	auto idplayer = idGameLocalManager::getIdPlayer();
//	if (!idplayer) {
//		logErr("GiveInventoryFromDevInvLoadout: can not give item idPlayer is bad ptr");
//		return;
//	}
//
//	__int64 idplayerAddr = (__int64)idplayer;
//
//	__int64 v11 = 0i64;
//
//	__int64 idDeclDevInvLoadoutResult = idResourceManager::getDevLoadOutResource();
//	if (idDeclDevInvLoadoutResult) {
//		auto fp = reinterpret_cast<GiveInventoryFromDevInvLoadoutFunctionFp>(MemHelper::getFuncAddr(0xFE7B90));
//		logInfo("GiveInventoryFromDevInvLoadout calling fp...");
//		fp(idplayerAddr, idDeclDevInvLoadoutResult, (__int64)&v11);
//	}
//
//}

void idInventoryManager::GiveInventoryFromDevInvLoadoutV2() {

	auto idplayer = idGameLocalManager::getIdPlayer();
	if (!idplayer) {
		logErr("GiveInventoryFromDevInvLoadoutV2: can not give item idPlayer is bad ptr");
		return;
	}

	__int64 idplayerAddr = (__int64)idplayer;

	//__int64 v11 = 0i64;

	//__int64 idDeclDevInvLoadoutResult = idResourceManager::getDevLoadOutResource();
	__int64 worldSpawn = idGameLocalManager::getIdWorldspawn();
	if (!worldSpawn) {
		logErr("GiveInventoryFromDevInvLoadoutV2: no world spawn");
		return;
	}

	__int64 idPlayerAt0x306 = idplayerAddr + 0x306;
	logInfo("idPlayerAt0x306: %p", (void*)idPlayerAt0x306);

	__int64 idDeclDevInvLoadOutFromWorldSpawn = *(__int64*)(worldSpawn + 0x9B8);
	__int64 idList_Items = worldSpawn + 0x998;

	logInfo("GiveInventoryFromDevInvLoadoutV2: idDeclDevInvLoadOutFromWorldSpawn: %p", (void*)idDeclDevInvLoadOutFromWorldSpawn);
	logInfo("GiveInventoryFromDevInvLoadoutV2 :idList_Items: %p", (void*)idList_Items);

	if (idDeclDevInvLoadOutFromWorldSpawn) {
		//! result: matches @ 0xFE7B90, sig direct: 40 53 56 57 41 56 48 83 EC 48 48 8B 01
		auto fp = reinterpret_cast<GiveInventoryFromDevInvLoadoutFunctionFp>(MemHelper::getFuncAddr(0xFE7B90));
		logInfo("GiveInventoryFromDevInvLoadoutV2 calling fp...");
		fp(idplayerAddr, idDeclDevInvLoadOutFromWorldSpawn, idList_Items);
		//fp(idplayerAddr, idDeclDevInvLoadoutResult, (__int64)&v11);
	}

}


