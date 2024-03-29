#include "idUsercmdGenLocalManager.h"


//__int64 idUsercmdGenLocalManager::m_idUsercmdGenLocal = 0;

//usercmd_t* idUsercmdGenLocalManager::usercmd_t_Static = 0;

unsigned int idUsercmdGenLocalManager::m_lastA2In_idKeyboardSmth_AE72A0 = -1;

__int64 idUsercmdGenLocalManager::m_sendKeyFuncAddr = 0;

keyNum_t idUsercmdGenLocalManager::m_current_use_keyNum = K_NONE;

//uint64_t idUsercmdGenLocalManager::m_lastFakeUsePressMs = 0;
// const unsigned int idUsercmdGenLocalManager::m_fakeUsePressMinDelayMs = 350; //using logs as base.



std::string idUsercmdGenLocalManager::debugGetLastA2InidKeyboardSmth_AE72A0Str() {
	return  std::to_string(m_lastA2In_idKeyboardSmth_AE72A0);
}


void idUsercmdGenLocalManager::debugUpdate(unsigned int lastA2In_idKeyboardSmth_AE72A0) {
	//logWarn("debugUpdate: sending fake use keypress request....");
	/*if (lastA2In_idKeyboardSmth_AE72A0 != m_lastA2In_idKeyboardSmth_AE72A0) {		
		logWarn("debugUpdate: lastA2In_idKeyboardSmth_AE72A0 has changed to %u", lastA2In_idKeyboardSmth_AE72A0);
	}*/
	m_lastA2In_idKeyboardSmth_AE72A0 = lastA2In_idKeyboardSmth_AE72A0;
}


//void idUsercmdGenLocalManager::acquireIdUsercmdGenLocal(__int64 IdUsercmdGenLocal) {
//    m_idUsercmdGenLocal = IdUsercmdGenLocal;
//}


//? if the key is not bound the result will be null.
//x the cmdGenButton_t value in result will be 56 (UB_NONE) if key is not bound. 
//void idUsercmdGenLocalManager::testGetBtnRefForKeynum(keyNum_t keyNum)
//{
//	//keyNum_t keyNum = keyNum_t::K_F;
//
//	typedef __int64 ( __fastcall* getBtnRefSmth_AA46F0)(__int16 deviceNum_a1, char bindsetIndexMBa2, keyNum_t keyNuma3, char a4);
//	auto funcAddr = MemHelper::getFuncAddr(0xAA46F0);
//	auto getBtnRefFunc = reinterpret_cast<getBtnRefSmth_AA46F0>(funcAddr);
//
//	//! from bp i got a1 = 0, a2 = 0, a3 =1, a4 = 0
//	__int64 result = getBtnRefFunc(0, 0, keyNum, 0);
//	logInfo("testGetBtnRefForKeynum: result for keynum: %d : %p", (int)keyNum, (void*)result);
//}


//bool idUsercmdGenLocalManager::acquireUsercmdStatic(__int64 usercmd_t_StaticPtr) {
//
//    if (MemHelper::isBadReadPtr((void*)usercmd_t_StaticPtr)) {       
//        logErr("acquireUsercmdStatic: failed to acquirre usercmd_t_StaticPtr: %p", (void*)usercmd_t_StaticPtr);
//        return false;
//    }
//
//    usercmd_t_Static = (usercmd_t*)*(__int64*)usercmd_t_StaticPtr;
//
//    if (MemHelper::isBadReadPtr(usercmd_t_Static)) {
//        logErr("acquireUsercmdStatic: failed to acquirre usercmd_t_Static: %p", usercmd_t_Static);
//        return false;
//    }
//
//    logInfo("acquireUsercmdStatic: succes acquiring usercmd_t_Static: %p", usercmd_t_Static);
//    return true;
//}


std::string idUsercmdGenLocalManager::getCmdGenButtonAsStr(cmdGenButton_t value) {

	switch (value) {
	case UB_ATTACK1: return "UB_ATTACK1";
	case UB_ZOOM: return "UB_ZOOM";
	case UB_MELEE: return "UB_MELEE";
	case UB_USE: return "UB_USE";
	case UB_RELOAD: return "UB_RELOAD";
	case UB_USE_AND_RELOAD: return "UB_USE_AND_RELOAD";
	case UB_SPRINT: return "UB_SPRINT";
	case UB_QGRENADE: return "UB_QGRENADE";
	case UB_WEAPONSELECT: return "UB_WEAPONSELECT";
	case UB_QGRENADE_AND_WEAPONSELECT: return "UB_QGRENADE_AND_WEAPONSELECT";
	case UB_WEAP_PREV_EQUIP: return "UB_WEAP_PREV_EQUIP";
	case UB_WEAP_NEXT: return "UB_WEAP_NEXT";
	case UB_WEAP_PREV: return "UB_WEAP_PREV";
	case UB_WEAP_FUNC_LEFT: return "UB_WEAP_FUNC_LEFT";
	case UB_WEAP_0: return "UB_WEAP_0";
	case UB_WEAP_1: return "UB_WEAP_1";
	case UB_WEAP_2: return "UB_WEAP_2";
	case UB_WEAP_3: return "UB_WEAP_3";
	case UB_WEAP_4: return "UB_WEAP_4";
	case UB_WEAP_5: return "UB_WEAP_5";
	case UB_WEAP_TOGGLE_UPGRADE_LEFT: return "UB_WEAP_TOGGLE_UPGRADE_LEFT";
	case UB_WEAP_TOGGLE_UPGRADE_RIGHT: return "UB_WEAP_TOGGLE_UPGRADE_RIGHT";
	case UB_COVERMODE: return "UB_COVERMODE";
	case UB_WALK: return "UB_WALK";
	case UB_TOGGLEDW: return "UB_TOGGLEDW";
	case UB_INVENTORY: return "UB_INVENTORY";
	case UB_MOVEUP: return "UB_MOVEUP";
	case UB_MOVEDOWN: return "UB_MOVEDOWN";
	case UB_HINT: return "UB_HINT";
	case UB_MOVELEFT: return "UB_MOVELEFT";
	case UB_MOVERIGHT: return "UB_MOVERIGHT";
	case UB_MOVEFORWARD: return "UB_MOVEFORWARD";
	case UB_MOVEBACK: return "UB_MOVEBACK";
	case UB_LOOKUP: return "UB_LOOKUP";
	case UB_LOOKDOWN: return "UB_LOOKDOWN";
	case UB_LOOKLEFT: return "UB_LOOKLEFT";
	case UB_LOOKRIGHT: return "UB_LOOKRIGHT";
	case UB_NONE: return "UB_NONE";
	case UB_MAX: return "UB_MAX";
	default: return "Unknown Value";
	}
}


std::string idUsercmdGenLocalManager::getkeyNum_tAsStr(keyNum_t keyNum) {
    switch (keyNum) {
    case K_NONE: return "K_NONE";
    case K_ESCAPE: return "K_ESCAPE";
    case K_1: return "K_1";
    case K_2: return "K_2";
    case K_3: return "K_3";
    case K_4: return "K_4";
    case K_5: return "K_5";
    case K_6: return "K_6";
    case K_7: return "K_7";
    case K_8: return "K_8";
    case K_9: return "K_9";
    case K_0: return "K_0";
    case K_MINUS: return "K_MINUS";
    case K_EQUALS: return "K_EQUALS";
    case K_BACKSPACE: return "K_BACKSPACE";
    case K_TAB: return "K_TAB";
    case K_Q: return "K_Q";
    case K_W: return "K_W";
    case K_E: return "K_E";
    case K_R: return "K_R";
    case K_T: return "K_T";
    case K_Y: return "K_Y";
    case K_U: return "K_U";
    case K_I: return "K_I";
    case K_O: return "K_O";
    case K_P: return "K_P";
    case K_LBRACKET: return "K_LBRACKET";
    case K_RBRACKET: return "K_RBRACKET";
    case K_ENTER: return "K_ENTER";
    case K_LCTRL: return "K_LCTRL";
    case K_A: return "K_A";
    case K_S: return "K_S";
    case K_D: return "K_D";
    case K_F: return "K_F";
    case K_G: return "K_G";
    case K_H: return "K_H";
    case K_J: return "K_J";
    case K_K: return "K_K";
    case K_L: return "K_L";
    case K_SEMICOLON: return "K_SEMICOLON";
    case K_APOSTROPHE: return "K_APOSTROPHE";
    case K_GRAVE: return "K_GRAVE";
    case K_LSHIFT: return "K_LSHIFT";
    case K_BACKSLASH: return "K_BACKSLASH";
    case K_Z: return "K_Z";
    case K_X: return "K_X";
    case K_C: return "K_C";
    case K_V: return "K_V";
    case K_B: return "K_B";
    case K_N: return "K_N";
    case K_M: return "K_M";
    case K_COMMA: return "K_COMMA";
    case K_PERIOD: return "K_PERIOD";
    case K_SLASH: return "K_SLASH";
    case K_RSHIFT: return "K_RSHIFT";
    case K_KP_STAR: return "K_KP_STAR";
    case K_LALT: return "K_LALT";
    case K_SPACE: return "K_SPACE";
    case K_CAPSLOCK: return "K_CAPSLOCK";
    case K_F1: return "K_F1";
    case K_F2: return "K_F2";
    case K_F3: return "K_F3";
    case K_F4: return "K_F4";
    case K_F5: return "K_F5";
    case K_F6: return "K_F6";
    case K_F7: return "K_F7";
    case K_F8: return "K_F8";
    case K_F9: return "K_F9";
    case K_F10: return "K_F10";
    case K_NUMLOCK: return "K_NUMLOCK";
    case K_SCROLL: return "K_SCROLL";
    case K_KP_7: return "K_KP_7";
    case K_KP_8: return "K_KP_8";
    case K_KP_9: return "K_KP_9";
    case K_KP_MINUS: return "K_KP_MINUS";
    case K_KP_4: return "K_KP_4";
    case K_KP_5: return "K_KP_5";
    case K_KP_6: return "K_KP_6";
    case K_KP_PLUS: return "K_KP_PLUS";
    case K_KP_1: return "K_KP_1";
    case K_KP_2: return "K_KP_2";
    case K_KP_3: return "K_KP_3";
    case K_KP_0: return "K_KP_0";
    case K_KP_DOT: return "K_KP_DOT";
    case K_F11: return "K_F11";
    case K_F12: return "K_F12";
    case K_F13: return "K_F13";
    case K_F14: return "K_F14";
    case K_F15: return "K_F15";
    case K_KANA: return "K_KANA";
    case K_CONVERT: return "K_CONVERT";
    case K_NOCONVERT: return "K_NOCONVERT";
    case K_YEN: return "K_YEN";
    case K_KP_EQUALS: return "K_KP_EQUALS";
    case K_CIRCUMFLEX: return "K_CIRCUMFLEX";
    case K_AT: return "K_AT";
    case K_COLON: return "K_COLON";
    case K_UNDERLINE: return "K_UNDERLINE";
    case K_KANJI: return "K_KANJI";
    case K_STOP: return "K_STOP";
    case K_AX: return "K_AX";
    case K_UNLABELED: return "K_UNLABELED";
    case K_KP_ENTER: return "K_KP_ENTER";
    case K_RCTRL: return "K_RCTRL";
    case K_KP_COMMA: return "K_KP_COMMA";
    case K_KP_SLASH: return "K_KP_SLASH";
    case K_PRINTSCREEN: return "K_PRINTSCREEN";
    case K_RALT: return "K_RALT";
    case K_PAUSE: return "K_PAUSE";
    case K_HOME: return "K_HOME";
    case K_UPARROW: return "K_UPARROW";
    case K_PGUP: return "K_PGUP";
    case K_LEFTARROW: return "K_LEFTARROW";
    case K_RIGHTARROW: return "K_RIGHTARROW";
    case K_END: return "K_END";
    case K_DOWNARROW: return "K_DOWNARROW";
    case K_PGDN: return "K_PGDN";
    case K_INS: return "K_INS";
    case K_DEL: return "K_DEL";
    case K_LWIN: return "K_LWIN";
    case K_RWIN: return "K_RWIN";
    case K_APPS: return "K_APPS";
    case K_POWER: return "K_POWER";
    case K_SLEEP: return "K_SLEEP";
    case K_JOY1: return "K_JOY1";
    case K_JOY2: return "K_JOY2";
    case K_JOY3: return "K_JOY3";
    case K_JOY4: return "K_JOY4";
    case K_JOY5: return "K_JOY5";
    case K_JOY6: return "K_JOY6";
    case K_JOY7: return "K_JOY7";
    case K_JOY8: return "K_JOY8";
    case K_JOY9: return "K_JOY9";
    case K_JOY10: return "K_JOY10";
    case K_JOY11: return "K_JOY11";
    case K_JOY12: return "K_JOY12";
    case K_JOY13: return "K_JOY13";
    case K_JOY14: return "K_JOY14";
    case K_JOY15: return "K_JOY15";
    case K_JOY16: return "K_JOY16";
    case K_JOY_STICK1_UP: return "K_JOY_STICK1_UP";
    case K_JOY_STICK1_DOWN: return "K_JOY_STICK1_DOWN";
    case K_JOY_STICK1_LEFT: return "K_JOY_STICK1_LEFT";
    case K_JOY_STICK1_RIGHT: return "K_JOY_STICK1_RIGHT";
    case K_JOY_STICK2_UP: return "K_JOY_STICK2_UP";
    case K_JOY_STICK2_DOWN: return "K_JOY_STICK2_DOWN";
    case K_JOY_STICK2_LEFT: return "K_JOY_STICK2_LEFT";
    case K_JOY_STICK2_RIGHT: return "K_JOY_STICK2_RIGHT";
    case K_JOY_TRIGGER1: return "K_JOY_TRIGGER1";
    case K_JOY_TRIGGER2: return "K_JOY_TRIGGER2";
    case K_JOY_DPAD_UP: return "K_JOY_DPAD_UP";
    case K_JOY_DPAD_DOWN: return "K_JOY_DPAD_DOWN";
    case K_JOY_DPAD_LEFT: return "K_JOY_DPAD_LEFT";
    case K_JOY_DPAD_RIGHT: return "K_JOY_DPAD_RIGHT";
    case K_MOUSE1: return "K_MOUSE1";
    case K_MOUSE2: return "K_MOUSE2";
    case K_MOUSE3: return "K_MOUSE3";
    case K_MOUSE4: return "K_MOUSE4";
    case K_MOUSE5: return "K_MOUSE5";
    case K_MOUSE6: return "K_MOUSE6";
    case K_MOUSE7: return "K_MOUSE7";
    case K_MOUSE8: return "K_MOUSE8";
    case K_MWHEELDOWN: return "K_MWHEELDOWN";
    case K_MWHEELUP: return "K_MWHEELUP";
    case K_LAST_KEY: return "K_LAST_KEY";
    default:  return "UNKNOWN ?!";
    }
}

__int64 idUsercmdGenLocalManager::getBtnInfoFor(keyNum_t keyNum) {
	typedef __int64(__fastcall* getBtnRefSmth_AA46F0)(__int16 deviceNum_a1, char bindsetIndexMBa2, keyNum_t keyNuma3, char a4);
    //! result: matches @ 0xAA46F0, sig direct: 40 53 48 83 EC 20 41 0F B6 D9 E8
	auto funcAddr = MemHelper::getFuncAddr(0xAA46F0);
	auto getBtnRefFunc = reinterpret_cast<getBtnRefSmth_AA46F0>(funcAddr);
	//! from bp i got a1 = 0, a2 = 0, a3 =1, a4 = 0
	__int64 result = getBtnRefFunc(0, 0, keyNum, 0);
	if (MemHelper::isBadReadPtr((void*)result)) {
		//logWarn("getBtnInfoFor could not find any BtnInfo for input ... returning 0 ");
		return 0;
	}
	return result;
}

cmdGenButton_t idUsercmdGenLocalManager::getCmdGenButtonBoundTo(keyNum_t keyNum) {
	auto btnInfoAddr = getBtnInfoFor(keyNum);
	if (btnInfoAddr) {
		ButtonInfo_K* btnInfo = (ButtonInfo_K*)btnInfoAddr;
		return btnInfo->cmdGenButtonVal;
	}
	return UB_NONE;
}



//! will return K_JOY_X if nothing is bound to Use key as joy x works but might make player reload when he doesn't want to.
keyNum_t idUsercmdGenLocalManager::getUseActionKeyNum() {
	for (int keynum = (int)K_ESCAPE; keynum < (int)K_LWIN; keynum++)	{
        
		auto cmdGenBtn = getCmdGenButtonBoundTo((keyNum_t)keynum);
		if (cmdGenBtn == UB_USE) {
            std::string keyNumStr = getkeyNum_tAsStr((keyNum_t)keynum);
			logInfo("getUseKeyGenButton: Use Btn is bound to keyNum: %s returning %d", keyNumStr.c_str(), keynum);
			return (keyNum_t)keynum;
		}
	}

	for (int keynum = (int)K_MOUSE1; keynum < (int)K_LAST_KEY; keynum++)
	{
        auto cmdGenBtn = getCmdGenButtonBoundTo((keyNum_t)keynum);
        if (cmdGenBtn == UB_USE) {
            std::string keyNumStr = getkeyNum_tAsStr((keyNum_t)keynum);
            logInfo("getUseKeyGenButton: Use Btn is bound to keyNum: %s returning %d", keyNumStr.c_str(), keynum);
            return (keyNum_t)keynum;
        }
	}

	logWarn("getUseKeyGenButton: seems no key is bound to Use action. Using K_JOY_X instead but the result will not be optimal. Please bind a key to Use in the game menu.");

	return K_JOY_X;
}

//! this should be called when user gets out of game menu => game or when he closes the console as these are the only times where he could change use key bind.
void idUsercmdGenLocalManager::updateCurrentUseBtnKeyNum() {
    auto newUseKeyNum = getUseActionKeyNum();
    if (newUseKeyNum != m_current_use_keyNum) {
        auto newUseKeyNumStr = getkeyNum_tAsStr(newUseKeyNum);
        auto current_use_keyNumStr = getkeyNum_tAsStr(m_current_use_keyNum);
        logWarn("updateCurrentUseBtnKeyNum: useKeyNum has changed from %s to %s", current_use_keyNumStr.c_str(), newUseKeyNumStr.c_str());
        m_current_use_keyNum = newUseKeyNum;
    }
}



void idUsercmdGenLocalManager::sendFakeUseKeyPressAndRelase(__int64 idUsercmdGenLocal_a1, unsigned int a2, bool isKeyDown)
{
    if (!m_sendKeyFuncAddr) {
        //! result: matches @ 0xAE6FE0, sig direct: 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B 81 ? ? ? ? 8B F2 49 63 E8
        m_sendKeyFuncAddr = MemHelper::getFuncAddr(0xAE6FE0);
        if (MemHelper::isBadReadPtr((void*)m_sendKeyFuncAddr)) {
            logErr("sendFakeUseKeyPressAndRelase: failed to find sendKeyFuncAddr, mod can not work.");
            m_sendKeyFuncAddr = 0;
            return;
        }
    }	

    if (m_current_use_keyNum == K_NONE) {
        updateCurrentUseBtnKeyNum();
    }

	auto idUsercmdGenFunc = reinterpret_cast<idUsercmdGenLocalSmth_t>(m_sendKeyFuncAddr);
	idUsercmdGenFunc(idUsercmdGenLocal_a1, a2, m_current_use_keyNum, (char)isKeyDown); 
	//idUsercmdGenFunc(idUsercmdGenLocal_a1, a2, K_JOY_X, (char)isKeyDown); //?  this will work even if there is not controller connected 
	//idUsercmdGenFunc(idUsercmdGenLocal_a1, a2, 0x21, (char)isKeyDown); //? 0x21 for F key 
}


//void idUsercmdGenLocalManager::sendFakeKeyPress(__int64 idUsercmdGenLocal_a1, keyNum_t keyNum, unsigned int a2, bool isKeyDown)
//{
//    if (!m_sendKeyFuncAddr) {
//        //! result: matches @ 0xAE6FE0, sig direct: 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B 81 ? ? ? ? 8B F2 49 63 E8
//        m_sendKeyFuncAddr = MemHelper::getFuncAddr(0xAE6FE0);
//        if (MemHelper::isBadReadPtr((void*)m_sendKeyFuncAddr)) {
//            logErr("sendFakeKeyPress: failed to find sendKeyFuncAddr, mod can not work.");
//            m_sendKeyFuncAddr = 0;
//            return;
//        }
//    }   
//
//    auto idUsercmdGenFunc = reinterpret_cast<idUsercmdGenLocalSmth_t>(m_sendKeyFuncAddr);
//    idUsercmdGenFunc(idUsercmdGenLocal_a1, a2, keyNum, (char)isKeyDown);
//    //idUsercmdGenFunc(idUsercmdGenLocal_a1, a2, K_JOY_X, (char)isKeyDown); //?  this will work even if there is not controller connected 
//    //idUsercmdGenFunc(idUsercmdGenLocal_a1, a2, 0x21, (char)isKeyDown); //? 0x21 for F key 
//}

//void idUsercmdGenLocalManager::sendFakeZoomKeyPress(bool isKeyDown)
//{
//    if (!m_sendKeyFuncAddr) {
//        //! result: matches @ 0xAE6FE0, sig direct: 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B 81 ? ? ? ? 8B F2 49 63 E8
//        m_sendKeyFuncAddr = MemHelper::getFuncAddr(0xAE6FE0);
//        if (MemHelper::isBadReadPtr((void*)m_sendKeyFuncAddr)) {
//            logErr("sendFakeKeyPress: failed to find sendKeyFuncAddr, mod can not work.");
//            m_sendKeyFuncAddr = 0;
//            return;
//        }
//    }
//
//    if (MemHelper::isBadReadPtr((void*)m_idUsercmdGenLocal)) {
//        return;
//    }
//
//    auto idUsercmdGenFunc = reinterpret_cast<idUsercmdGenLocalSmth_t>(m_sendKeyFuncAddr);
//    idUsercmdGenFunc(m_idUsercmdGenLocal, 0, K_MOUSE2, (char)isKeyDown);
//    //idUsercmdGenFunc(idUsercmdGenLocal_a1, a2, K_JOY_X, (char)isKeyDown); //?  this will work even if there is not controller connected 
//    //idUsercmdGenFunc(idUsercmdGenLocal_a1, a2, 0x21, (char)isKeyDown); //? 0x21 for F key 
//}



//bool idUsercmdGenLocalManager::IsKeyPressed(usercmdButton_t button) {
//
//
//    if (!usercmd_t_Static) return false;
//    return (usercmd_t_Static->buttons & button) != 0;
// 
//}


//void idUsercmdGenLocalManager::SetButtonState(usercmdButton_t button, bool state) {
//    if (!usercmd_t_Static) return;
//
//    if (state) {
//        usercmd_t_Static->buttons |= button;  // Set the button state to pressed
//    }
//    else {
//        usercmd_t_Static->buttons &= ~button; // Clear the button state (release)
//    }
//}



//void idUsercmdGenLocalManager::SetButtonState(usercmd_t* cmd_tPtr, usercmdButton_t button, bool state) {
//    if (!cmd_tPtr) return;
//
//    if (state) {
//        cmd_tPtr->buttons |= button;  // Set the button state to pressed
//    }
//    else {
//        cmd_tPtr->buttons &= ~button; // Clear the button state (release)
//    }
//}
