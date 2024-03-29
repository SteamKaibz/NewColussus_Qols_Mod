#include "idMaterialManager.h"
#include "cachedCvarsManager.h"

__int64 const idMaterialManager::m_idMaterialResourceListOffset = 0x3C767F0;
std::string idMaterialManager::m_idMaterialResourceListTypeName("material");
//int idMaterialManager::m_testIndex = -1;
//? don't forget m_testIndex might not be -1
int idMaterialManager::m_testIndex = 250;

 //std::vector<std::string> m_spotligtShadowCastingFallOffMaterialsStrsVec {""}



std::vector<std::string> idMaterialManager::getCurrentMapSpotLightMaterialNames() {

	std::vector<std::string> resultVec;
	std::string spotLightStrStart = "lights/analytical/spot/p50";

	__int64 idMaterialResourceListObj = MemHelper::getAddr(m_idMaterialResourceListOffset);
	if (MemHelper::isBadReadPtr((void*)idMaterialResourceListObj)) {
		logErr("getCurrentMapSpotLightMaterialNames: failed returning 0");
		return resultVec;
	}
	__int64 idMaterialResourceList_IdListPtr = idMaterialResourceListObj + 0x20;
	auto matrsIdList = (idList*)idMaterialResourceList_IdListPtr;

	for (size_t i = 0; i < matrsIdList->num; i++)
	{
		if (!MemHelper::isBadReadPtr(&matrsIdList->list[i])) {
			auto matrAddr = matrsIdList->list[i];
			std::string matrNameStr = *(const char**)(matrAddr + 8);
			MaterialBitFieldStruct* bf = (MaterialBitFieldStruct*)(matrAddr + 0x80);
			if (bf->materialIsLightMaterial && matrNameStr._Starts_with(spotLightStrStart)) {
				resultVec.push_back(matrNameStr);				
			}
		}		
	}
	return resultVec;
}


__int64 idMaterialManager::getCurrentMapSpotLightMaterialPtr() {
	
	//? we can change this at some point if one does not contain any p100 spotlight matr
	std::string spotLightStrStart = "lights/analytical/spot/p50";
	//std::string spotLightStrStart = "lights/analytical/spot/p100"; //! this works but lots of specular in scope

	__int64 idMaterialResourceListObj = MemHelper::getAddr(m_idMaterialResourceListOffset);
	if (MemHelper::isBadReadPtr((void*)idMaterialResourceListObj)) {
		logErr("getCurrentMapSpotLightMaterialPtr: failed returning 0");
		return 0;
	}
	__int64 idMaterialResourceList_IdListPtr = idMaterialResourceListObj + 0x20;
	auto matrsIdList = (idList*)idMaterialResourceList_IdListPtr;

	for (size_t i = 0; i < matrsIdList->num; i++)
	{
		if (!MemHelper::isBadReadPtr(&matrsIdList->list[i])) {
			auto matrAddr = matrsIdList->list[i];
			std::string matrNameStr = *(const char**)(matrAddr + 8);
			MaterialBitFieldStruct* bf = (MaterialBitFieldStruct*)(matrAddr + 0x80);
			if (bf->materialIsLightMaterial && matrNameStr._Starts_with(spotLightStrStart)) {
				logInfo("getCurrentMapSpotLightMaterialPtr: found spotLight matr: ptr: %p name:  %s", (void*)matrAddr, matrNameStr.c_str());
				return matrAddr;				
			}				
		}
		else {
			logErr("getCurrentMapSpotLightMaterialPtr: debugGetLightMaterialVec: bad ptr ");
		}
	}
	logWarn("getCurrentMapSpotLightMaterialPtr: could not find any spot light material, will use default and ugly square light");
	return 0;
}


//! previous version bak
//__int64 idMaterialManager::getCurrentMapHeadLightMaterialPtr(std::string ligthMtrName) {
//	__int64 idMaterialResourceListObj = MemHelper::getAddr(m_idMaterialResourceListOffset);
//	if (MemHelper::isBadReadPtr((void*)idMaterialResourceListObj)) {
//		logErr("getCurrentMapHeadLightMaterialPtr: failed returning 0");
//		return 0;
//	}
//	__int64 idMaterialResourceList_IdListPtr = idMaterialResourceListObj + 0x20;
//	auto matrsIdList = (idList*)idMaterialResourceList_IdListPtr;
//
//	for (size_t i = 0; i < matrsIdList->num; i++)
//	{
//		if (!MemHelper::isBadReadPtr(&matrsIdList->list[i])) {
//			auto matrAddr = matrsIdList->list[i];
//			auto matrName = *(const char**)(matrAddr + 8);
//			MaterialBitFieldStruct* bf = (MaterialBitFieldStruct*)(matrAddr + 0x80);
//			if (bf->materialIsLightMaterial && (std::string(matrName) == ligthMtrName)){
//				logInfo("found IsLightMaterial ptr with name %s ligthMtrName returning %p", matrName, (void*)matrAddr);	
//				return matrAddr;
//			}				
//		}		
//	}
//	logErr("getCurrentMapHeadLightMaterialPtr failed to find %s returning 0", ligthMtrName.c_str());
//}


void idMaterialManager::debugGetLightMaterialVec() {
	int counter = 0;


	__int64 idMaterialResourceListObj = MemHelper::getAddr(m_idMaterialResourceListOffset);
	if (MemHelper::isBadReadPtr((void*)idMaterialResourceListObj)) {
		logErr("debugGetLightMaterialVec: failed");
		return;
	}
	//! we could also do a check if it's a idMaterial Resource list.
	__int64 idMaterialResourceList_IdListPtr = idMaterialResourceListObj + 0x20;
	auto matrsIdList =  (idList*)idMaterialResourceList_IdListPtr;

	for (size_t i = 0; i < matrsIdList->num; i++)
	{
		if (!MemHelper::isBadReadPtr(&matrsIdList->list[i])) {
			auto matrAddr = matrsIdList->list[i];
			auto matrName = *(const char**)(matrAddr + 8);
			MaterialBitFieldStruct* bf = (MaterialBitFieldStruct*)(matrAddr + 0x80);
			if (bf->materialIsLightMaterial) {
				if (bf->materialCastsShadows && bf->materialHas2dLightFalloff) {
					logInfo("found IsLightMaterial ptr: %p name:  %s can cast shadows and has 2d light fall off", (void*)matrAddr, matrName);
				}
				else if (bf->materialCastsShadows) {
					logInfo("found IsLightMaterial ptr: %p name:  %s and can cast shadows ", (void*)matrAddr, matrName);
				}
				else if(bf->materialHas2dLightFalloff){
					logInfo("found IsLightMaterial ptr: %p name:  %s and has 2d light fall off ", (void*)matrAddr, matrName);
				}
				else {
					logInfo("found IsLightMaterial ptr: %p name:  %s", (void*)matrAddr, matrName);
				}
				counter++;
			}
			//logInfo("found matr name: %s", matrName);			
		}
		else {
			logErr("debugGetLightMaterialVec: bad ptr ");
		}
	}

	logInfo("done found %d light mtrs", counter);
	
}



idList* idMaterialManager::getMaterialsIdList() {
	__int64 idMaterialResourceListObj = MemHelper::getAddr(m_idMaterialResourceListOffset);
	if (MemHelper::isBadReadPtr((void*)idMaterialResourceListObj)) {
		return nullptr;
	}
	//! we could also do a check if it's a idMaterial Resource list.
	__int64 idMaterialResourceList_IdListPtr = idMaterialResourceListObj + 0x20;
	return  (idList*)idMaterialResourceList_IdListPtr;
}

void idMaterialManager::showMaterial(int index, idList* idListPtr) {
	auto firstMaterialPtr = idListPtr->list; //! addr of first materialPtr in the list
	logInfo("showMaterial: firstMaterialPtr %p", firstMaterialPtr);
	auto materialPtr = m_testIndex * 8 + (char*)firstMaterialPtr;
	logInfo("showMaterial: materialPtr %p", materialPtr);
	if (MemHelper::isBadReadPtr(materialPtr)) {
		logErr("showMaterial: materialPtr bad ptr: %p", materialPtr);
		return;
	}
	__int64 material = *(__int64*)materialPtr;
	logInfo("showMaterial: material %p", (void*)material);

	const char* materialName = *(const char**)(material + 8);
	//std::string matrName = materialName;
	//std::string g_testMaterialStr = "g_testMaterial " + matrName;
	logInfo("showMaterial: material: %p materialName addr: %p matrName: %s index is: %d", (void*)material, materialName, materialName, m_testIndex);
	if (materialName) {
		//cachedCvarsManager::testMaterial(materialName);
		idCvarManager::setCvar("g_testMaterial", materialName);
	}
}


void idMaterialManager::testMaterialNext()
{

	auto materialIdList = getMaterialsIdList();
	if (MemHelper::isBadReadPtr(materialIdList)) {
		logErr("testMaterialNext: materialIdList bad ptr: %p", materialIdList);
		return;
	}

	 m_testIndex++;
	 if (m_testIndex < 0) {
		 logWarn("testMaterialNext: m_testIndex is negative, setting index to 0");
		 m_testIndex = 0;
	 }
	 if (m_testIndex >= materialIdList->num) {
		 logWarn("testMaterialNext: max materials index reached (num = %d and index = %d) setting index to 0", materialIdList->num, m_testIndex);
		 m_testIndex = 0;
	 }
	 showMaterial(m_testIndex, materialIdList);

  }

  void idMaterialManager::testMaterialPrev()
  {
	  auto materialIdList = getMaterialsIdList();
	  if (MemHelper::isBadReadPtr(materialIdList)) {
		  logErr("testMaterialPrev: materialIdList bad ptr: %p", materialIdList);
		  return;
	  }

	  m_testIndex--;
	  if (m_testIndex < 0) {
		  if (materialIdList->num == 0) {
			  m_testIndex = 0;
		  }
		  else {
			  m_testIndex = materialIdList->num - 1;
		  }	 		  
		  logWarn("testMaterialPrev: m_testIndex is negative, setting index to %d", m_testIndex);
	  }
	  if (m_testIndex >= materialIdList->num) {		 
		  logWarn("testMaterialPrev: max materials index reached (num = %d and index = %d) setting index to 0", materialIdList->num, m_testIndex);
		  m_testIndex = 0;
		  
	  }
	  showMaterial(m_testIndex, materialIdList);
  }
