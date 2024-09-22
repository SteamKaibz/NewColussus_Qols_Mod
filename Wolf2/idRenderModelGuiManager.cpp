#include "idRenderModelGuiManager.h"




//! we have this cause we can not acquire material during game load as it may not be initialized yet.
void idRenderModelGuiManager::acquireWhiteMaterial() {
	//! result: matches @ 0x2F120D0, sig direct : 00 F2 DD BC 7E 01 00 00 F0 67 C7 03 00 00 00 00 80 2B 68
	auto _whiteMatrPtr = MemHelper::getAddr(0x2F120D0);
	if (MemHelper::isBadReadPtr((void*)_whiteMatrPtr)) {
		logErr("acquireWhiteMaterial: failed to handleChange _whiteMatr.");
		m_whiteMaterial = 0;
		return;
	}
	m_whiteMaterial = *(__int64*)_whiteMatrPtr;
	if (MemHelper::isBadReadPtr((void*)m_whiteMaterial)) {
		logErr("acquireWhiteMaterial: m_whiteMaterial is bad ptr: %p setting it to 0.", (void*)m_whiteMaterial);
		m_whiteMaterial = 0;
		return;
	}
	logInfo("acquireWhiteMaterial: m_whiteMaterial set to: %p", (void*)m_whiteMaterial);
}


bool idRenderModelGuiManager::acquireWhiteMaterialAddr(__int64 _whiteMtr)
{
	if (MemHelper::isBadReadPtr((void*)_whiteMtr)) {
		logErr("acquireWhiteMaterialAddr: failed to handleChange _whiteMtr.");
		m_whiteMaterial = 0;
		return false;
	}

	m_whiteMaterial = *(__int64*)_whiteMtr;
	if (MemHelper::isBadReadPtr((void*)m_whiteMaterial)) {
		logErr("acquireWhiteMaterialAddr: m_whiteMaterial is bad ptr: %p setting it to 0.", (void*)m_whiteMaterial);
		m_whiteMaterial = 0;
		return false;
	}
	else {
		logInfo("acquireWhiteMaterialAddr: m_whiteMaterial set to: %p", (void*)m_whiteMaterial);
	}
	return true;
}



bool idRenderModelGuiManager::acquireDrawStretchPicFuncAddr(__int64 funcAddr) {
	if (MemHelper::isBadReadPtr((void*)funcAddr)) {
		logErr("acquireDrawStretchPicFuncAddr: funcAddr: %p is bad ptr", (void*)m_idRenderModelGui_DrawStretchPicFAddr);
		m_idRenderModelGui_DrawStretchPicFAddr = 0;
		return false;
	}
	//m_idRenderModelGui_DrawStretchPicFAddr = reinterpret_cast<idRenderModelGui_DrawStretchPic>(funcAddr);
	m_idRenderModelGui_DrawStretchPicFAddr = funcAddr;
	logInfo("acquireDrawStretchPicFuncAddr: m_idRenderModelGui_DrawStretchPicFAddr set to %p", (void*)funcAddr);
	return true;
}


//bool idRenderModelGuiManager::acquireDrawStretchPicFuncAddr(__int64 funcAddr) {
//
//	if (MemHelper::isBadReadPtr((void*)funcAddr)) {
//
//	}
//}






void idRenderModelGuiManager::drawColoredRect(__int64 idRenderModelGuiAdrr, float x, float y, float width, float height, idColor color) {

	static int counter = 0;

	if (!m_whiteMaterial) {
		logErr("drawColoredRect: can not draw m_whiteMaterial is null");
		return;
	}
	if (!m_idRenderModelGui_DrawStretchPicFAddr) {
		logErr("drawColoredRect: can not draw m_idRenderModelGui_DrawStretchPicFAddr is null");
		return;
	}
	setColor(idRenderModelGuiAdrr, color);

	idRenderModelGui_DrawStretchPic drawStretchPicFp = reinterpret_cast<idRenderModelGui_DrawStretchPic>(m_idRenderModelGui_DrawStretchPicFAddr);
	drawStretchPicFp(idRenderModelGuiAdrr, x, y, 0.0, width, height, s1_default, t1_default, s2_default, t2_default, m_whiteMaterial);
}

void idRenderModelGuiManager::updateLastFrameNumber(__int64 idRenderModelGuiAdrr)
{
	auto currentFrameNumber = *(unsigned int*)(idRenderModelGuiAdrr + m_frameNumOffset);
	m_lastFramNumber = currentFrameNumber;
}

unsigned int idRenderModelGuiManager::getCurrentFrameNumber(__int64 idRenderModelGuiAdrr) {
	return  *(unsigned int*)(idRenderModelGuiAdrr + m_frameNumOffset);
}

bool idRenderModelGuiManager::isWhiteMaterialacquired() {
	if (MemHelper::isBadReadPtr((void*)m_whiteMaterial)) {
		return false;
	}
	return true;
}



std::string idRenderModelGuiManager::getDisplayDbgInfoStr()
{
	std::string resultStr;
	resultStr += "Resulution Info: Display mode: ";
	//? reminder: enum name is different here...
	resultStr += TypeInfoManager::getEnumMemberName("idPlayerProfileShell::displayMode_t", cachedCvarsManager::getDisplayMode());
	resultStr += " r_mode: ";
	resultStr += std::to_string(cachedCvarsManager::get_r_mode());
	resultStr += " Width: ";
	resultStr += std::to_string(cachedCvarsManager::get_WindowWidthInt());
	resultStr += " Height: ";
	resultStr += std::to_string(cachedCvarsManager::get_WindowHeightInt());
	return resultStr;
}





void idRenderModelGuiManager::setColor(__int64 idRenderModelGuiAdrr, const idColor& idColor) {
	if (MemHelper::isBadReadPtr((void*)idRenderModelGuiAdrr)) {
		logErr("setColor: can not set color cause idRenderModelGuiAdrr is bad ptr");
		return;
	}
	*(unsigned int*)(idRenderModelGuiAdrr + m_packedColorOffset) = idColor.PackColor();
}
