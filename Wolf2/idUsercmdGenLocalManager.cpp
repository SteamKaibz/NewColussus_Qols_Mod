#include "idUsercmdGenLocalManager.h"








std::string idUsercmdGenLocalManager::getCmdGenButtonAsStr(cmdGenButton_t value) {

    std::string resultStr = TypeInfoManager::getEnumMemberName("cmdGenButton_t", value);
    if (resultStr.empty()) {
        return "failed to find cmdGenButton_t val str";
    }

    return resultStr;
}


std::string idUsercmdGenLocalManager::getkeyNum_tAsStr(keyNum_t keyNum) {

    std::string resultStr = TypeInfoManager::getEnumMemberName("keyNum_t", keyNum);
    if (resultStr.empty()) {
        return "failed to find keyNum_t val str";
    }   

    return resultStr;
}

__int64 idUsercmdGenLocalManager::getBtnInfoFor(keyNum_t keyNum) {
	typedef __int64(__fastcall* getBtnRefSmth_AA46F0)(__int16 deviceNum_a1, char bindsetIndexMBa2, keyNum_t keyNuma3, char a4);
    //! result: matches @ 0xAA46F0, sig direct: 40 53 48 83 EC 20 41 0F B6 D9 E8
	auto funcAddr = MemHelper::getFuncAddr(0xAA46F0);
	auto getBtnRefFunc = reinterpret_cast<getBtnRefSmth_AA46F0>(funcAddr);
	//! from bp i got a1 = 0, devicneNumMb_a2 = 0, a3 =1, a4 = 0
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

//todo this will return the keyNum_t for any bound action, however still need to test what happens if user is using only a controller as this will return a keyboard key as they are evaluated first(?)
keyNum_t idUsercmdGenLocalManager::getKeyNumForCmd(cmdGenButton_t inputCmdGenBtn) {

    for (int keynum = (int)K_ESCAPE; keynum < (int)K_LAST_KEY; keynum++) {

        auto cmdGenBtn = getCmdGenButtonBoundTo((keyNum_t)keynum);
        if (cmdGenBtn == inputCmdGenBtn) {
            std::string keyNumStr = getkeyNum_tAsStr((keyNum_t)keynum);
            std::string inputCmdGenBtnStr = getCmdGenButtonAsStr(inputCmdGenBtn);
            logInfo("getKeyNumForCmd: inputCmdGenBtnStr: %s is bound to keyNum: %s ", inputCmdGenBtnStr.c_str(), keyNumStr.c_str());
            return (keyNum_t)keynum;
        }
    }

    std::string inputCmdGenBtnStr = getCmdGenButtonAsStr(inputCmdGenBtn);
    logErr("getKeyNumForCmd: failed to find keyNum for cmd: %s returning K_NONE", inputCmdGenBtnStr.c_str());
    return K_NONE;
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
    logInfo("updateCurrentUseBtnKeyNum() called");
    auto newUseKeyNum = getUseActionKeyNum();
    if (newUseKeyNum != m_current_use_keyNum) {
        auto newUseKeyNumStr = getkeyNum_tAsStr(newUseKeyNum);
        auto current_use_keyNumStr = getkeyNum_tAsStr(m_current_use_keyNum);
        logWarn("updateCurrentUseBtnKeyNum: useKeyNum has changed from %s to %s", current_use_keyNumStr.c_str(), newUseKeyNumStr.c_str());
        m_current_use_keyNum = newUseKeyNum;
    }
}


void idUsercmdGenLocalManager::sendFakeUseKeyPressAndRelase(__int64 idUsercmdGenLocal_a1, unsigned int devicneNumMb_a2, bool isKeyDown)
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
    idUsercmdGenFunc(idUsercmdGenLocal_a1, devicneNumMb_a2, m_current_use_keyNum, (char)isKeyDown);
    //idUsercmdGenFunc(idUsercmdGenLocal_a1, devicneNumMb_a2, K_JOY_X, (char)isKeyDown); //?  this will work even if there is not controller connected 
    //idUsercmdGenFunc(idUsercmdGenLocal_a1, devicneNumMb_a2, 0x21, (char)isKeyDown); //? 0x21 for F key 
}







//? this will not return any joy stick button bound to this action ! (meaning it will return keys or mouse btns)
Bind_K idUsercmdGenLocalManager::getKeyboardBind_K_ForAction(cmdGenButton_t cmd) {

    Bind_K bindk = Bind_K(cmd);

    for (int keynum = (int)K_ESCAPE; keynum < (int)K_LAST_KEY; keynum++) {

        if ((keyNum_t)keynum > K_SLEEP && (keyNum_t)keynum < K_MOUSE1) continue; //! skiping joy btns.

        auto cmdGenBtn = getCmdGenButtonBoundTo((keyNum_t)keynum);
        if (cmdGenBtn == cmd) {
            bindk.keyNumsVec.push_back((keyNum_t)keynum);
        }
    }

    if (bindk.keyNumsVec.empty()) {
        logWarn("getBind_K_ForAction: could not find any key bound to: %s Mod might not work as intended", getCmdGenButtonAsStr(cmd).c_str());
    }

    logInfo("getBind_K_ForAction: dbg: for cmdGenButton_t: %s found those matches: ", getCmdGenButtonAsStr(cmd).c_str());
    for (keyNum_t keyMatch : bindk.keyNumsVec) {
        logInfo("%s", getkeyNum_tAsStr(keyMatch).c_str());
    }

    return bindk;
}


//! for example get for K_ESCAPE (1) this will return Escape, so we can use it in bind/unbind cmd.
std::string idUsercmdGenLocalManager::getKeyNameStrForKeyNum(keyNum_t keyNum) {

    if (!m_keynumsToKeyNameListAddr) {
        m_keynumsToKeyNameListAddr = MemHelper::getFuncAddr(0x2EEFDA0);
        if (MemHelper::isBadReadPtr((void*)m_keynumsToKeyNameListAddr)) {
            m_keynumsToKeyNameListAddr = 0;
            logErr("getKeyNameStrForKeyNum: m_keynumsToKeyNameListAddr is bad ptr mod should not be running");
            return std::string(); 
        }
        else {
            logInfo("getKeyNameStrForKeyNum: m_keynumsToKeyNameListAddr set to %p", (void*)m_keynumsToKeyNameListAddr);
        }
    }

    KeyNumToStr_K* keyNumToStr = (KeyNumToStr_K*)m_keynumsToKeyNameListAddr;
    logInfo("getKeyNameStrForKeyNum: dbg: keyNumToStr: %p", keyNumToStr);
   

    while (keyNumToStr->keyNum < (K_LAST_KEY))
    {
        if (keyNumToStr->keyNum == keyNum) {
            return keyNumToStr->keyNumToStr;
        }
        keyNumToStr++;
    }   

    return std::string();
}




//! this should be triggered first time we are in game menus. and then each time leaving the game controls menu page.
void idUsercmdGenLocalManager::tryCacheGameFireKeysBinds() {

    m_attack1_UserBindK = getKeyboardBind_K_ForAction(UB_ATTACK1);
    m_zoom_UserBindK = getKeyboardBind_K_ForAction(UB_ZOOM);


    if (!(m_zoom_UserBindK.isBound()) || !(m_attack1_UserBindK.isBound())) {
        logErr("tryCacheGameFireKeysBinds: For mouse and keyboard users: iron sight key and/or fire right weapon key is not bound, the feature to swap buttons when dual wielding will not work, please bind a key to 'fire right weapon' and 'iron sight/Fire left weapon' in the game menu (but do not bind them in the console please!)");

        m_isFireKeysBindsSet = false;
        return;
    }
    else {
        m_isFireKeysBindsSet = true;
    }
   

    logInfo("tryCacheGameFireKeysBinds: just acquired/updated Bind_K for attack1 and zoom from game settings");
}



bool idUsercmdGenLocalManager::isAttack1Key(keyNum_t keynum) {
    return m_attack1_UserBindK.isBoundToKey(keynum);
}

bool idUsercmdGenLocalManager::isZoomKey(keyNum_t keynum) {
    return m_zoom_UserBindK.isBoundToKey(keynum);
}


bool idUsercmdGenLocalManager::isFireKeysBindsSet()
{
    return m_isFireKeysBindsSet;
}




//! to be used in SendKeySmth_t_Hook
void idUsercmdGenLocalManager::dbgLogHookArgsChanges(__int64 idUsercmdGenLocal_a1, unsigned int deviceNumMB_a2, keyNum_t keyNum_a3, char isDown_a4) {

    static __int64 prev_idUsercmdGenLocal_a1 = -1;
    static unsigned int prev_deviceNumMB_a2 = UINT_MAX;
    static keyNum_t prev_keyNum_a3 = K_LAST_KEY;  // Assuming K_NONE is a valid keyNum_t default
    static char prev_isDown_a4 = -1;

    if (idUsercmdGenLocal_a1 != prev_idUsercmdGenLocal_a1) {
        logInfo("idUsercmdGenLocal_a1 has changed to: %p ", (void*)idUsercmdGenLocal_a1);
        prev_idUsercmdGenLocal_a1 = idUsercmdGenLocal_a1;
        prev_keyNum_a3 = K_LAST_KEY;
        prev_deviceNumMB_a2 = UINT_MAX;;
        prev_isDown_a4 = -1;
    }
    
    if (deviceNumMB_a2 != prev_deviceNumMB_a2) {
        logInfo("devicneNumMB_a2 has changed from %d to %d", prev_deviceNumMB_a2, deviceNumMB_a2);
        prev_deviceNumMB_a2 = deviceNumMB_a2;
    }

    if (keyNum_a3 != prev_keyNum_a3) {
        std::string prevkeyNumAsStr = getkeyNum_tAsStr(prev_keyNum_a3);
        std::string keyNumAsStr = getkeyNum_tAsStr(keyNum_a3);

        logInfo("keyNum_a3 has changed from %s to %s", prevkeyNumAsStr.c_str(), keyNumAsStr.c_str());
        prev_keyNum_a3 = keyNum_a3;
    }

    if (isDown_a4 != prev_isDown_a4) {
        logInfo("isDown_a4 has changed from %d to %d", prev_isDown_a4, isDown_a4);
        prev_isDown_a4 = isDown_a4;
    }
}



std::string idUsercmdGenLocalManager::debug_getFireKeysInfoStr() {

    std::string resultStr;

    for (int keynum = (int)K_ESCAPE; keynum < (int)K_LWIN; keynum++) {

        auto cmdGenBtn = getCmdGenButtonBoundTo((keyNum_t)keynum);
        if (cmdGenBtn == UB_ATTACK1) {
            std::string keyNumStr = getkeyNum_tAsStr((keyNum_t)keynum);
            resultStr += " UB_ATTACK1 bound to " + keyNumStr;           
        }
        else  if (cmdGenBtn == UB_ZOOM) {
            std::string keyNumStr = getkeyNum_tAsStr((keyNum_t)keynum);
            resultStr += " UB_ZOOM bound to " + keyNumStr;
        }
    }

    for (int keynum = (int)K_MOUSE1; keynum < (int)K_LAST_KEY; keynum++)
    {
        auto cmdGenBtn = getCmdGenButtonBoundTo((keyNum_t)keynum);
        if (cmdGenBtn == UB_ATTACK1) {
            std::string keyNumStr = getkeyNum_tAsStr((keyNum_t)keynum);
            resultStr += " UB_ATTACK1 bound to " + keyNumStr;
        }
        else  if (cmdGenBtn == UB_ZOOM) {
            std::string keyNumStr = getkeyNum_tAsStr((keyNum_t)keynum);
            resultStr += " UB_ZOOM bound to " + keyNumStr;
        }
    }

    return resultStr;
}




bool idUsercmdGenLocalManager::isButtonPressed(int usercmdButtonFlags, usercmdButton_t button) {
    return (usercmdButtonFlags & button) != 0;
}


void idUsercmdGenLocalManager::setButtonFlag(int& usercmdButtonFlags, usercmdButton_t button, bool isPressed) {
    if (isPressed) {
        // Set the flag (turn the button on)
        usercmdButtonFlags |= button;
    }
    else {
        // Clear the flag (turn the button off)
        usercmdButtonFlags &= ~button;
    }
}


void idUsercmdGenLocalManager::invertZoomAndAttack(int& usercmdButtonFlags) {
    bool isZoomPressed = (usercmdButtonFlags & BUTTON_ZOOM) != 0;
    bool isAttackPressed = (usercmdButtonFlags & BUTTON_ATTACK1) != 0;

    // Swap the flags: if zoom was pressed, now attack is pressed and vice versa
    if (isZoomPressed) {
        usercmdButtonFlags &= ~BUTTON_ZOOM;      // Clear BUTTON_ZOOM
        usercmdButtonFlags |= BUTTON_ATTACK1;    // Set BUTTON_ATTACK1
    }
    else {
        usercmdButtonFlags &= ~BUTTON_ATTACK1;   // Clear BUTTON_ATTACK1
    }

    if (isAttackPressed) {
        usercmdButtonFlags &= ~BUTTON_ATTACK1;   // Clear BUTTON_ATTACK1
        usercmdButtonFlags |= BUTTON_ZOOM;       // Set BUTTON_ZOOM
    }
    else {
        usercmdButtonFlags &= ~BUTTON_ZOOM;      // Clear BUTTON_ZOOM
    }
}





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


//void idUsercmdGenLocalManager::sendFakeKeyPress(__int64 idUsercmdGenLocal_a1, keyNum_t keyNum, unsigned int devicneNumMb_a2, bool isKeyDown)
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
//    idUsercmdGenFunc(idUsercmdGenLocal_a1, devicneNumMb_a2, keyNum, (char)isKeyDown);
//    //idUsercmdGenFunc(idUsercmdGenLocal_a1, devicneNumMb_a2, K_JOY_X, (char)isKeyDown); //?  this will work even if there is not controller connected 
//    //idUsercmdGenFunc(idUsercmdGenLocal_a1, devicneNumMb_a2, 0x21, (char)isKeyDown); //? 0x21 for F key 
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
//    //idUsercmdGenFunc(idUsercmdGenLocal_a1, devicneNumMb_a2, K_JOY_X, (char)isKeyDown); //?  this will work even if there is not controller connected 
//    //idUsercmdGenFunc(idUsercmdGenLocal_a1, devicneNumMb_a2, 0x21, (char)isKeyDown); //? 0x21 for F key 
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
//	//! from bp i got a1 = 0, devicneNumMb_a2 = 0, a3 =1, a4 = 0
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
