#include "idAutomapManager.h"


const std::vector<unsigned char> idAutomapManager::m_setDefaultZoomToMinVec = { 0x00, 0x00, 0x00, 0x41 };
const std::vector<unsigned char> idAutomapManager::m_setDefaultZoomToOrigValueVec = { 0x00, 0x00, 0x80, 0x41 };


void idAutomapManager::setAutoMapDefaultZoomToMinZoom(bool isSetToMaxZoom)
{
	if (isSetToMaxZoom) {
		if (!Patcher::patchIfNeeded("autoMapMinZoom", MemHelper::getFuncAddr(0x4DA599) + 6, m_setDefaultZoomToMinVec)) {
			logErr("setAutoMapDefaultZoomToMaxZoom: failed to set autoMapMinZoom");			
		}
	}
	else {
		if (!Patcher::patchIfNeeded("autoMapDefaultZoom", MemHelper::getFuncAddr(0x4DA599) + 6, m_setDefaultZoomToOrigValueVec)) {
			logErr("setAutoMapDefaultZoomToMaxZoom: failed to set autoMapDefaultZoom");
		}
	}


}
