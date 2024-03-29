#pragma once

#include "../Config/Config.h"



//! mainly used to check if weapon is firing so we can restore cam anim to defaul value
class weaponStateManager
{
private:
	//static inline bool m_isFiring = false;	

public:
	
	
	static bool isCurrentWeaponFiring(char* idPlayerCharPtr);
};

