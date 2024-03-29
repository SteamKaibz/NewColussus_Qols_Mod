#include "idResourceManager.h"
#include "../MemHelper/MemHelper.h"


//! result: matches @ 0x2FE02B0, sig direct: 80 48 F4 5C 7F 01
const __int64 idResourceManager::m_labelsListStartOffset = 0x2FE02B0;

bool idResourceManager::isDevStringOverwriteAttempt = false;

const char* idResourceManager::m_MenuBtnModText = "Kaibz Mod";
const char* idResourceManager::m_MenuBtnModHelpText = "Open Mod Menu";

const char* idResourceManager::m_MenuBtnDevRefStr = "#str_menu_root_dev_label";
const char* idResourceManager::m_MenuBtnDevHelpStr = "#str_menu_root_dev_help";

idResourceList__ForClassName_ABBE60 idResourceManager::m_getResListForClsNameFp = nullptr;

//? damn templates ! it's a nightmate to build with them.
//template <typename T>
//std::string idResourceManager::getDeclName(T* idDeclDerivedPtr) {
//	idResource* idResourceObj = (idResource*)idDeclDerivedPtr;
//	if (MemHelper::isBadReadPtr(idResourceObj)) {
//		logErr("getDeclName: bad ptr for idResourceObj: %p returning empty str", idResourceObj);
//	}
//	else {
//		return std::string(idResourceObj->name.str);
//	}
//	return std::string();
//}


std::string idResourceManager::getDeclName(idResource* idResourceObj) {
	//idResource* idResourceObj = (idResource*)resPtr;
	if (MemHelper::isBadReadPtr(idResourceObj)) {
		logErr("getDeclName: bad ptr for idResourceObj: %p returning empty str", idResourceObj);
	}
	else {
		return std::string(idResourceObj->name.str);
	}
	return std::string();
}



bool idResourceManager::acquireGetResListForClsNameFp(__int64 faddr)
{	
	//auto funcAddr = MemHelper::getFuncAddr(0xABBE60);
	if (MemHelper::isBadReadPtr((void*)faddr)) {
		logErr("acquireGetResListForClsNameFp: faddr is bad ptr: %p", (void*)faddr);
		m_getResListForClsNameFp = nullptr;
		return false;
	}
	m_getResListForClsNameFp = reinterpret_cast<idResourceList__ForClassName_ABBE60>(faddr);
	return true;
}


idResourceList* idResourceManager::getResourceListPtrForClsName(std::string clsName)
{
	auto result = m_getResListForClsNameFp(clsName.c_str());
	if (MemHelper::isBadReadPtr(result)) {
		logErr("getResourceListPtrForClsName: failed to find idResourceList ptr for clsName: %s returning nullptr", clsName.c_str());
		return nullptr;
	}
	return result;
}


idResource* idResourceManager::getDeclByName(std::string clsName, std::string declName) {
	auto resourcePtrs = getResPtrsVecForClsName(clsName);
	for (size_t i = 0; i < resourcePtrs.size(); i++)
	{
		if (std::string(resourcePtrs[i]->name.str) == declName) {
			return resourcePtrs[i];
		}
	}
	logWarn("getDeclByName: failed to find %s returning null", declName.c_str());
	return nullptr;
}

__int64 idResourceManager::getDevLoadOutResource()
{
	//! result: matches @ 0xA42B80, sig direct: 44 89 4C 24 ? 44 89 44 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24
	auto findWithInheritanceFp = reinterpret_cast<DeclInfo_FindWithInheritanceFp>(MemHelper::getFuncAddr(0xA42B80));
	if (!findWithInheritanceFp) {
		logErr("faildd to find findWithInheritanceFp");
		return 0;
	}

	//! result: matches @ 0x3DC6400, sig direct: 88 CA DB 3B F7 7F 00
	auto devInvLoadoutResAddr = MemHelper::getAddr(0x3DC6400);

	__int64 result = findWithInheritanceFp(devInvLoadoutResAddr, (__int64)"devInvLoadout/code_referenced/default_buildgame_devloadout", 0, 0);

	logInfo("testFindDevLoadOutResource: found: %p", (void*)result);

	return result;


}


std::vector<idResource*> idResourceManager::getResPtrsVecForClsName(std::string clsName)
{
	std::vector<idResource*> results;

	auto resourceListPtr = getResourceListPtrForClsName(clsName);
	if (!resourceListPtr) {
		logWarn("getDeclPtrsVecForClsName: no result for %s", clsName.c_str());
		return results;
	}
	
	for (size_t i = 0; i < resourceListPtr->resourceList.num; i++)
	{
		if (!MemHelper::isBadReadPtr(&resourceListPtr->resourceList.list[i])) {
			idResource* res = (idResource*)resourceListPtr->resourceList.list[i];
			if (!MemHelper::isBadReadPtr(res)) {
				results.push_back(res);
			}
		}
		
		else {
			logErr("getResPtrsVecForClsName: bad ptr for&resourceListPtr->resourceList.list[i]: %p", &resourceListPtr->resourceList.list[i]);
		}
	}

	//logInfo("getResPtrsVecForClsName: found %d results for %s ", )
	return results;
}



void idResourceManager::overwriteDevLabelsWithModRefs() {
	//static int s_overwriteAttemptsTotal = 0;


	logInfo("overwriteDevLabelsWithModRefs: attempting to overwrite dev labels...");

	__int64 refStringsListStartPtr = MemHelper::getAddr(m_labelsListStartOffset);
	if (!MemHelper::isBadReadPtr((void*)refStringsListStartPtr)) {
		int listSize = *(int*)(refStringsListStartPtr + 0x8);
		refString_k* refStringsListPtr = *(refString_k**)refStringsListStartPtr;	


		bool isOverwrittenDevLabel = false;
		bool isOverwrittenDevHelp = false;		

		size_t lastCounter = 0;
		size_t counter = 0;

		while (counter < listSize)
		{
			if (isOverwrittenDevLabel && isOverwrittenDevHelp) {
				logInfo("overwriteDevLabelsWithModRefs: succes!");
				break;				
			}


			if (MemHelper::isBadReadPtr(refStringsListPtr) || MemHelper::isBadReadPtr(&refStringsListPtr->refString) || MemHelper::isBadReadPtr(&refStringsListPtr->localString) || refStringsListPtr->refString == nullptr || refStringsListPtr->localString == nullptr) {
				logErr("overwriteDevLabelsWithModRefs: bad ptr found");
				break;
			}
			else {

				std::string refStr = refStringsListPtr->refString;

				
				if (refStr == m_MenuBtnDevRefStr) {
					//? this crashes during level load or main menu
					//strcpy_s(refStringsListPtr->localString, strlen(m_MenuBtnModText) + 1, m_MenuBtnModText);
					//? this crashes too for mod name Kaibz Mod
					//strcpy_s(refStringsListPtr->localString, _TRUNCATE, m_MenuBtnModText);
					//? this crashes
					//strcpy(refStringsListPtr->localString, m_MenuBtnModText);
					
					
					//s_overwriteAttemptsTotal++;
					size_t refStringSize = sizeof(refStringsListPtr->localString);
					logInfo("overwriteDevLabelsWithModRefs: refStringsListPtr->localString: %s is being overwritten by %s refStringSize: %zu (refStringsListPtr: %p)", refStringsListPtr->localString, m_MenuBtnModText, refStringSize, refStringsListPtr);
					//strcpy_s(refStringsListPtr->localString, _TRUNCATE, m_MenuBtnModText);
					/*strncpy_s(refStringsListPtr->localString, sizeof(m_MenuBtnModText), m_MenuBtnModText, sizeof(m_MenuBtnModText));*/
					
					
					
					//! this works but mod name will have to be changed:
					/*size_t refStringSize = sizeof(refStringsListPtr->localString);
					logInfo("overwriteDevLabelsWithModRefs: refStringsListPtr->localString: %s is being overwritten by %s refStringSize: %zu (refStringsListPtr: %p)", refStringsListPtr->localString, m_MenuBtnModText, refStringSize, refStringsListPtr);
					strncpy_s(refStringsListPtr->localString, _TRUNCATE, m_MenuBtnModText, refStringSize);		*/			
					
					
					isOverwrittenDevLabel = true;
				}

				else if (refStr == m_MenuBtnDevHelpStr) {
					//? this crashes during level load or main menu
					//strcpy_s(refStringsListPtr->localString, strlen(m_MenuBtnModHelpText) + 1, m_MenuBtnModHelpText);
					//? crashes too
					//strcpy_s(refStringsListPtr->localString, _TRUNCATE, m_MenuBtnModHelpText);
					//? crashes as well:
					//strcpy(refStringsListPtr->localString, m_MenuBtnModHelpText);
					 
					
					size_t refStringSize = sizeof(refStringsListPtr->localString);
					logInfo("overwriteDevLabelsWithModRefs: refStringsListPtr->localString: %s is being overwritten by %s refStringSize: %zu (refStringsListPtr: %p)", refStringsListPtr->localString, m_MenuBtnModHelpText, refStringSize, refStringsListPtr);
					//strcpy_s(refStringsListPtr->localString, _TRUNCATE, m_MenuBtnModHelpText);
					//? crashes too
					/*strncpy_s(refStringsListPtr->localString, sizeof(m_MenuBtnModHelpText), m_MenuBtnModHelpText, sizeof(m_MenuBtnModHelpText));*/
					


				
					//! this works but mod description will have to be changed:
					/*size_t refStringSize = sizeof(refStringsListPtr->localString);
					logInfo("overwriteDevLabelsWithModRefs: refStringsListPtr->localString: %s is being overwritten by %s refStringSize: %zu (refStringsListPtr: %p)", refStringsListPtr->localString, m_MenuBtnModHelpText, refStringSize, refStringsListPtr);
					strncpy_s(refStringsListPtr->localString, _TRUNCATE, m_MenuBtnModHelpText, sizeof(refStringsListPtr->localString));*/
					
					
					isOverwrittenDevHelp = true;
				}
			}
			refStringsListPtr++;
			counter++;
		}

		if (!isOverwrittenDevLabel || !isOverwrittenDevHelp) {
			logErr("overwriteDevLabelsWithModRefs: failed to find devs labels...Mod name link will not appear in game menu. Please report to mod author on Nexus.");
		}		
	}



	idResourceManager::isDevStringOverwriteAttempt = true;


}



const char* idResourceManager::getLocalizedStrPtrForRef(const char* refStrInput) {

	logInfo("getLocalizedStrPtrForRef: attempting to find localized string from ref: %s...", refStrInput);

	__int64 refStringsListStartPtr = MemHelper::getAddr(m_labelsListStartOffset);
	if (!MemHelper::isBadReadPtr((void*)refStringsListStartPtr)) {
		int listSize = *(int*)(refStringsListStartPtr + 0x8);
		refString_k* refStringsListPtr = *(refString_k**)refStringsListStartPtr;

		size_t lastCounter = 0;
		size_t counter = 0;

		while (counter < listSize)
		{
			if (MemHelper::isBadReadPtr(refStringsListPtr) || MemHelper::isBadReadPtr(&refStringsListPtr->refString) || MemHelper::isBadReadPtr(&refStringsListPtr->localString) || refStringsListPtr->refString == nullptr || refStringsListPtr->localString == nullptr) {
				logErr("getLocalizedStrPtrForRef: bad ptr found");
				break;
			}
			else {

				std::string refStr = refStringsListPtr->refString;
				if (refStr == refStrInput) {
					logInfo("getLocalizedStrPtrForRef: found localized string ptr: %p for ref: %s", refStringsListPtr->localString, refStrInput);
					return refStringsListPtr->localString;
				}
			}
			refStringsListPtr++;
			counter++;
		}
		
	}

	logErr("getLocalizedStrPtrForRef: failed to find localized string, the mod link won't be displayed in game menus. User will have to click on 'Dev' buttons in the game menu to acces the mod settings");
	return nullptr;
}






//! let's look for #str_menu_dev_title
//! i suppose 0x2FE02B0 is an idlist but that will do for now...
void idResourceManager::debugListReferenceStringInfo(const char* searchStr) {
	__int64 refStringsListStartPtr = MemHelper::getAddr(m_labelsListStartOffset);
	if (!MemHelper::isBadReadPtr((void*)refStringsListStartPtr)) {
		int listSize = *(int*)(refStringsListStartPtr + 0x8);
		refString_k* refStringsListPtr = *(refString_k**) refStringsListStartPtr;
		//logInfo("debugListReferenceStringInfo: searching for: %s refStringsListPtr: %p (refStringsListStartPtr: %p) list size should be %d", searchStr, refStringsListPtr, (void*)refStringsListStartPtr, listSize);
		logInfo("debugListReferenceStringInfo: searching for: %s ", searchStr);


		size_t lastCounter = 0;
		size_t counter = 0;

		while (counter < listSize)
		{
			if (MemHelper::isBadReadPtr(refStringsListPtr) || MemHelper::isBadReadPtr(&refStringsListPtr->refString) || MemHelper::isBadReadPtr(&refStringsListPtr->localString) || refStringsListPtr->refString == nullptr || refStringsListPtr->localString == nullptr) {
				logWarn("debugListReferenceStrings: bad ptr found returning (counter: %zu) returning", counter);
				return;
			}
			else {

				try
				{
					std::string refStr = refStringsListPtr->refString;
					std::string localStr = refStringsListPtr->localString;


					if (refStr == searchStr) {
						logInfo("succes finding input %s Localized str: %s refInt: %d (refStringsListPtr for this result: %p)", searchStr, localStr.c_str(), refStringsListPtr->refInt, refStringsListPtr);
						return;
					}
				}
				catch (const std::exception&)
				{
					logWarn("exception error...");
				}				
			}
			refStringsListPtr++;
			counter++;			
		}
		logWarn("debugListReferenceStringInfo: search the whole list, could not find: %s", searchStr);
	}
	

	

}





void idResourceManager::debugLogResourceListForClsName(std::string clsName) {

	logInfo("debugLogResourceListForClsName: logging for clasName: %s", clsName.c_str());
	auto declPtrsVec = getResPtrsVecForClsName(clsName);
	if (declPtrsVec.empty()) {
		logWarn("debugLogResourceListForClsName: no results for %s", clsName.c_str());
		return;
	}
	for (size_t i = 0; i < declPtrsVec.size(); i++)
	{
		if (!MemHelper::isBadReadPtr(declPtrsVec[i])) {
			logInfo("decl addr: %p name: %s", declPtrsVec[i], declPtrsVec[i]->name.str);
		}
	}
}

void idResourceManager::Log_idDeclRenderParmList() {

	logInfo("Log_idDeclRenderParmList: loggingidDeclRenderParm");
	auto declPtrsVec = getResPtrsVecForClsName("idDeclRenderParm");
	if (declPtrsVec.empty()) {
		logWarn("Log_idDeclRenderParmList: no results ");
		return;
	}
	for (size_t i = 0; i < declPtrsVec.size(); i++)
	{
		if (!MemHelper::isBadReadPtr(declPtrsVec[i])) {
			idDeclRenderParm* decl = (idDeclRenderParm*)declPtrsVec[i];

			int parmIndex = *(int*)((char*)declPtrsVec[i] + 0x80);
			logInfo("decl addr: %p name: %s parmIndex: %d parmType: %d edit: %d", decl, decl->name, decl->parmIndex, decl->parmType, decl->edit);
		}
	}
}






void idResourceManager::debugListRenderParmsNamesAndValues(bool onlyShowEditables) {

	std::vector<std::string> result;

	auto resourceListPtr = getResourceListPtrForClsName("idDeclRenderParm");
	if (!resourceListPtr) {
		logErr("debugListRenderParmsNamesAndValues: failed.");
		return;
	}

	logInfo("debugListRenderParmsNamesAndValues: debug: attempting to list %d ptrs in list", resourceListPtr->resourceList.num);
	for (size_t i = 0; i < resourceListPtr->resourceList.num; i++)
	{
		if (!MemHelper::isBadReadPtr(&resourceListPtr->resourceList.list[i])) {
			idResource* res = (idResource*)resourceListPtr->resourceList.list[i];
			if (!MemHelper::isBadReadPtr(&res->name.str)) {
				int ParmIndex = *(int*)((char*)res + 0x80);
				int edit = *(int*)((char*)res + 0x90);
				int parmType = *(int*)((char*)res + 0x84);
				if (onlyShowEditables) {
					if (!edit) continue;
				}
				//logInfo("decl addr: %p name: %s", res, res->name.str);
				std::string dataStr = "decl addr: " + K_Utils::intToHexString((__int64)res) + " name: " + res->name.str + " parmIndex: " + std::to_string(ParmIndex) + " parmType: " + std::to_string(parmType);
				result.push_back(dataStr);
			}
			else {
				logErr("debugListRenderParmsNamesAndValues: bad ptr for &res->name.str: %p", &res->name.str);
			}
			//logInfo("&resourceListPtr->resourceList.list[i]: %p res: %p", &resourceListPtr->resourceList.list[i], (void*)res);
		}
		else {
			logErr("debugListRenderParmsNamesAndValues: bad ptr for&resourceListPtr->resourceList.list[i]: %p", &resourceListPtr->resourceList.list[i]);
		}
	}


	logInfo("debugListRenderParmsNamesAndValues : found: %zu results : ", result.size());
	for (size_t i = 0; i < result.size(); i++)
	{
		logInfo("%s", result[i].c_str());

	}
	logInfo("debugListRenderParmsNamesAndValues: done.");


}

//std::vector<std::string> idResourceManager::getResourceListDataStrForClsName(std::string clsName)
//{
//	std::vector<std::string> result;
//
//	auto resourceListPtr = getResourceListPtrForClsName(clsName);
//	if (!resourceListPtr) {	
//		return result;
//	}
//
//	logInfo("getResourceListNamesForClsName: debug: attempting to list %d ptrs in list for input: %s", resourceListPtr->resourceList.num, clsName.c_str());
//	for (size_t i = 0; i < resourceListPtr->resourceList.num; i++)
//	{
//		if (!MemHelper::isBadReadPtr(&resourceListPtr->resourceList.list[i])) {
//			idResource* res = (idResource*) resourceListPtr->resourceList.list[i];
//			if (!MemHelper::isBadReadPtr(&res->name.str)) {
//				//logInfo("decl addr: %p name: %s", res, res->name.str);
//				std::string dataStr = "decl addr: " + K_Utils::intToHexString((__int64)res) + " name: " + res->name.str;
//				result.push_back(dataStr);
//				//result.push_back(res->name.str);
//			}
//			else {
//				logErr("getResourceListNamesForClsName: bad ptr for &res->name.str: %p", &res->name.str);
//			}			
//			//logInfo("&resourceListPtr->resourceList.list[i]: %p res: %p", &resourceListPtr->resourceList.list[i], (void*)res);
//		}	
//		else {
//			logErr("getResourceListNamesForClsName: bad ptr for&resourceListPtr->resourceList.list[i]: %p", &resourceListPtr->resourceList.list[i]);
//		}
//	}
//
//
//	logInfo("getResourceListNamesForClsName : found: %zu results : ", result.size());
//	for (size_t i = 0; i < result.size(); i++)
//	{
//		logInfo("%s", result[i].c_str());
//
//	}
//
//	logInfo("getResourceListDataStrForClsName: done.");
//
//}


