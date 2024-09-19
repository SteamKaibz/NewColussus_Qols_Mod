#include "TypeInfoManager.h"

__int64 TypeInfoManager::m_debugFindClsInfoCount = 0;
__int64 TypeInfoManager::m_typeInfoToolsPtrAddr = 0;
__int64 TypeInfoManager::m_findClassInfoFuncPtr = 0;
__int64 TypeInfoManager::m_findEnumInfoFuncPtr = 0;
__int64 TypeInfoManager::m_engine_tAddr = 0;
int TypeInfoManager::m_cached_IdGameSystemLocalStateOffset = 0;
int TypeInfoManager::m_cached_IdGameSystemLocalMapInstanceOffset = 0;

classTypeInfo_t* TypeInfoManager::getTypeInfoTest(__int64 idEnginePtr, const char* className)
{
	logInfo("getTypeInfoTest: idEnginePtr: %p className: %s", (void*)idEnginePtr, className);
	if (MemHelper::isBadReadPtr((void*)idEnginePtr)) {
		logErr("getTypeInfoTest: idEnginePtr is bad ptr: %p returning", (void*)idEnginePtr);
		return nullptr;
	}
	auto typeInfoToolsPtrAddr = idEnginePtr + 0x80;
	if (MemHelper::isBadReadPtr((void*)typeInfoToolsPtrAddr)) {
		logErr("getTypeInfoTest: typeInfoToolsPtrAddr is bad ptr: %p returning", (void*)typeInfoToolsPtrAddr);
		return nullptr;
	}
	logInfo("getTypeInfoTest: typeInfoToolsPtrAddr: %p ", (void*)typeInfoToolsPtrAddr);

	//! result: matches @ 0x1285C80, sig direct: 4C 89 44 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 C7 44 24
	auto findClsInfoFuncAdd = MemHelper::getFuncAddr(0x1285C80);
	if (MemHelper::isBadReadPtr((void*)findClsInfoFuncAdd)) {
		logErr("getTypeInfoTest: findClsInfoFuncAdd is bad ptr: %p returning", (void*)findClsInfoFuncAdd);
		return nullptr;
	}
	logInfo("getTypeInfoTest: findClsInfoFuncAdd: %p ", (void*)findClsInfoFuncAdd);
	auto findClassInfoFunc = reinterpret_cast<pIdTypeInfoTools_FindClassInfo>(findClsInfoFuncAdd);
	auto result = (classTypeInfo_t*)findClassInfoFunc(typeInfoToolsPtrAddr, className);

	logInfo("getTypeInfoTest: result: %p", result);
	return result;
}

void TypeInfoManager::dumpTypeTest(classTypeInfo_t* typeInfoPtr)
{
	if (MemHelper::isBadReadPtr(typeInfoPtr)) {
		logErr("dumpTypeTest: typeInfoPtr is bad ptr: %p ", typeInfoPtr);
		return;

	}
	std::string filetext = "";

	filetext += "\nstruct ";
	filetext += typeInfoPtr->name;
	if (typeInfoPtr->superType && typeInfoPtr->superType[0]) {
		filetext += " : public ";
		filetext += typeInfoPtr->superType;

	}
	filetext += " {\n";

	logInfo("dumpTypeTest: &typeInfoPtr->variables: %p ", &typeInfoPtr->variables);
	logInfo("dumpTypeTest: size of classVariableInfo_t: %zu (dec)", sizeof(classVariableInfo_t));
	//return;

	for (auto bleh2 = typeInfoPtr->variables; bleh2 && bleh2->name; ++bleh2) {
		//bleh2->
		filetext += "\t//";

		char buff[64];
		sprintf_s(buff, "Offset %d,\t size %d\n", bleh2->offset, bleh2->size);

		filetext += buff;
		/*if (bleh2->comment && bleh2->comment[0]) {
			filetext += "\t//";
			filetext += bleh2->comment;
			filetext += "\n";
		}*/
		filetext += "\t";
		filetext += bleh2->type;


		if (bleh2->ops) {
			filetext += bleh2->ops;
		}
		filetext += " ";
		filetext += bleh2->name;
		filetext += ";\n";
	}
	filetext += "};\n";
	logInfo("%s", filetext.c_str());
}

bool TypeInfoManager::acquireTypeInfoTools(__int64 typeInfoToolsPtr)
{
	logDebug("acquireTypeInfoTools");
	if (MemHelper::isBadReadPtr((void*)typeInfoToolsPtr)) {
		logErr("acquireTypeInfoTools: failed to handleChange TypeInfoTools (bad ptr): %p", (void*)typeInfoToolsPtr);
		m_typeInfoToolsPtrAddr = 0;

	}
	else {

		/*m_typeInfoToolsAsAnInt64_Test = (__int64)typeInfoToolsPtr;
		logInfo("acquireTypeInfoTools: DEBUGGING  m_typeInfoToolsAsAnInt64_Test: %p", (void*)m_typeInfoToolsAsAnInt64_Test);*/
		//m_typeInfoToolsCharPtr = (char*)typeInfoToolsPtr;

		m_typeInfoToolsPtrAddr = typeInfoToolsPtr;
		logInfo("acquireTypeInfoTools: Succes acquirring m_typeInfoToolsPtrAddr: %p", (void*)m_typeInfoToolsPtrAddr);
		return true;
	}
	return false;
}

bool TypeInfoManager::acquirreFindClassInfoFuncPtr(__int64 funcAddr)
{
	logDebug("acquirreFindClassInfoFuncPtr");
	if (!funcAddr) {
		logErr("acquirreFindClassInfoFuncPtr: failed to handleChange funcAddr");
		m_findClassInfoFuncPtr = 0;
		return false;
	}
	else {
		m_findClassInfoFuncPtr = funcAddr;
		logInfo("acquirreFindClassInfoFuncPtr: Succes acquirring funcAddr: %p", (void*)funcAddr);
	}
	return true;
}

bool TypeInfoManager::acquirreFindEnumInfoFuncPtr(__int64 funcAddr)
{
	logDebug("acquirreFindEnumInfoFuncPtr");
	if (!funcAddr) {
		logErr("acquirreFindEnumInfoFuncPtr: failed to handleChange funcAddr");
		m_findEnumInfoFuncPtr = 0;
		return false;
	}
	else {
		m_findEnumInfoFuncPtr = funcAddr;
		logInfo("acquirreFindEnumInfoFuncPtr: Succes acquirring funcAddr: %p", (void*)funcAddr);
	}
	return true;
}


typeInfo_t* TypeInfoManager::getTypeInfo_t() {

	if (MemHelper::isBadReadPtr((void*)m_typeInfoToolsPtrAddr)) {
		logErr("getTypeInfo_t: m_typeInfoToolsPtrAddr is bad ptr returning");
		return nullptr;
	}

	idTypeInfoTools* typeInfoTools = (idTypeInfoTools*)m_typeInfoToolsPtrAddr;

	if (!typeInfoTools->typeInfo) {
		logErr("getTypeInfo_t: typeInfoTools->typeInfo is nullptr !");
		return nullptr;
	}

	return typeInfoTools->typeInfo;

}



classTypeInfo_t* TypeInfoManager::findClassInfo(const char* className)
{
	m_debugFindClsInfoCount++;
	if (MemHelper::isBadReadPtr((void*)className)) {		
		logErr("findClassInfo: className is bad ptr: %p returning 0 (findClassInfo called %lld times)", className, m_debugFindClsInfoCount);
		return 0;
	}	

	if (MemHelper::isBadReadPtr((void*)m_typeInfoToolsPtrAddr) || MemHelper::isBadReadPtr((void*)m_findClassInfoFuncPtr)) {
		logErr("findClassInfo: can not execute, m_typeInfoToolsPtr or m_findClassInfoFuncPtr is badptr: m_typeInfoToolsPtr: %p , m_findClassInfoFuncPtr: %p", (void*)m_typeInfoToolsPtrAddr, (void*)m_findClassInfoFuncPtr);
		return nullptr;
	}
	auto findClassInfoFunc = reinterpret_cast<pIdTypeInfoTools_FindClassInfo>(m_findClassInfoFuncPtr);
	return (classTypeInfo_t*)findClassInfoFunc(m_typeInfoToolsPtrAddr, className);
}

classVariableInfo_t* TypeInfoManager::findClassField(const char* cname, const char* fieldname)
{
	logDebug("findClassField");
	auto playerclass = findClassInfo(cname);
	if (!playerclass)
		return nullptr;
	auto headattr = playerclass->variables;
	classVariableInfo_t* notarget_field = nullptr;
	while (headattr && headattr->name) {
		if (AreStringsEqual(headattr->name, fieldname)) {
			return headattr;
		}
		++headattr;
	}
	return nullptr;
}

bool TypeInfoManager::AreStringsEqual(const char* str1, const char* str2)
{
	return strcmp(str1, str2) == 0;
}

classVariableInfo_t* TypeInfoManager::findClassFirstField(const char* cname)
{
	logDebug("findClassFirstField");
	auto playerclass = findClassInfo(cname);
	if (!playerclass)
		return nullptr;
	auto headattr = playerclass->variables;
	if (headattr) {
		return headattr;
	}
	return nullptr;
}

enumTypeInfo_t* TypeInfoManager::FindEnumInfo(const char* enumName)
{
	logDebug("FindEnumInfo");
	if (MemHelper::isBadReadPtr((void*)m_typeInfoToolsPtrAddr) || MemHelper::isBadReadPtr((void*)m_findEnumInfoFuncPtr)) {
		logErr("FindEnumInfo: can not execute, m_typeInfoToolsPtr or m_findEnumInfoFuncPtr is badptr: m_typeInfoToolsPtr: %p , m_findEnumInfoFuncPtr: %p", (void*)m_typeInfoToolsPtrAddr, (void*)m_findEnumInfoFuncPtr);
		return nullptr;
	}
	auto findEnumInfoFunc = reinterpret_cast<pIdTypeInfoTools_FindEnumInfo>(m_findEnumInfoFuncPtr);
	return (enumTypeInfo_t*)findEnumInfoFunc(m_typeInfoToolsPtrAddr, enumName);
}

std::string TypeInfoManager::getEnumMemberName(const char* enumName, long long enumMemberVal)
{
	auto enumTypeInfo = FindEnumInfo(enumName);
	if (!enumTypeInfo) {
		logWarn("getEnumMemberName: failed to find EnumInfo for enumName: %s ", enumName);
		return std::string();
	}
	for (auto eval = enumTypeInfo->values; eval && eval->name && eval->name[0]; eval++) {

		if (eval->value == enumMemberVal) {
			return std::string(eval->name);
		}
	}
	return std::string();
}


