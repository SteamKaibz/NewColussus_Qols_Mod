#include "weaponStateManager.h"

bool weaponStateManager::isCurrentWeaponFiring(char* idPlayerCharPtr)
{
	using QWORD = unsigned  long long;

	// ida. too annoyed to create structs atm.
	__int64 curentlyEquippedIdWeapon = *(QWORD*)(idPlayerCharPtr + 0x1A38);
	
	return (curentlyEquippedIdWeapon && !*(DWORD*)(curentlyEquippedIdWeapon + 4i64 * *(int*)(curentlyEquippedIdWeapon + 0x118) + 0x130));

	/*if (isWeaponFiring != lastIsEquippedWeaponFiring) {
		logInfo("weapon state has change and is now: %s", isWeaponFiring ? "firing" : "not firing");
		lastIsEquippedWeaponFiring = isWeaponFiring;
	}*/
}
