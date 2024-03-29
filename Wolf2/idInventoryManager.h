#pragma once

#include <string>
#include "idResourceManager.h"
#include "idGameLocalManager.h"


/// looks like we could give ourself dev loadouts:
//v4 = idDeclInfo::FindWithInheritance_MB_A42B80(
//(__int64)&devInvLoadout_3DC6400,
//(__int64)"devInvLoadout/code_referenced/default_buildgame_devloadout",
//0,
//0);
//if (v4)
//idPlayer::GiveInventoryFromDevInvLoadout_FE7B90((void**)a1, v4, (__int64)&v11);



typedef __int64 (__fastcall* GiveItemFp)(
    __int64 idInventoryCollection_a1,
    __int64 idPlayer_a2,
    __int64 decl_a3,
    int count_MB_a4,
    unsigned int a5,
    unsigned int a6);


typedef void(__fastcall* GiveInventoryFromDevInvLoadoutFunctionFp)(
    __int64 idPlayer_a1,
    __int64 idDeclDevInvLoadout_a2,
    __int64 idList_idDeclDevInvLoadout_devInventoryItem_a3);

class idInventoryManager
{

private:


public:

    static void giveItem(std::string declClassName, std::string declName);

    static void GiveInventoryFromDevInvLoadoutV2();

    //! weapon/player/sp/lasergewehr is "available" in reunion usual place.
	static void giveWeaponItem(std::string declName);

    static void giveUpgradeItem(std::string declName);

};

