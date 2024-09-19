#pragma once


#include <cstdint>
#include "../Config/Config.h"
#include "../MemHelper/MemHelper.h"
#include "idLib.h"









class TypeInfoManager {

private:
	static __int64 m_debugFindClsInfoCount;
	static __int64 m_typeInfoToolsPtrAddr;
	static __int64 m_findClassInfoFuncPtr;
	static __int64 m_findEnumInfoFuncPtr;
	static __int64 m_engine_tAddr;

	static int m_cached_IdGameSystemLocalStateOffset;
	static int m_cached_IdGameSystemLocalMapInstanceOffset;

	//! Global Cached:

	//! idList defined in idLib not sure if  good idea or not but very low chance it changes.
	//static classVariableInfo_t* m_idList_VarInfo;



	// __int64 __fastcall idTypeInfoTools::FindClassInfo_4104A0(__int64 a1, unsigned __int8 *a2)
	typedef __int64(__fastcall* pIdTypeInfoTools_FindClassInfo)(__int64 typeInfoTools, const char* className);
	static pIdTypeInfoTools_FindClassInfo m_pIdTypeInfoTools_FindClassInfo;

	typedef __int64(__fastcall* pIdTypeInfoTools_FindEnumInfo)(__int64 typeInfoTools, const char* className);
	static pIdTypeInfoTools_FindEnumInfo m_pIdTypeInfoTools_FindEnumInfo;



public:


	static classTypeInfo_t* getTypeInfoTest(__int64 idEnginePtr, const char* className);

	static void dumpTypeTest(classTypeInfo_t* typeInfoPtr);

	static bool acquireTypeInfoTools(__int64 typeInfoToolsPtr);

	static bool acquirreFindClassInfoFuncPtr(__int64 funcAddr);
	
	static bool acquirreFindEnumInfoFuncPtr(__int64 funcAddr);

	static typeInfo_t* getTypeInfo_t();
	
	static classTypeInfo_t* findClassInfo(const char* className);

	static classVariableInfo_t* findClassField(const char* cname, const char* fieldname);	

	static bool AreStringsEqual(const char* str1, const char* str2);

	static classVariableInfo_t* findClassFirstField(const char* cname);
	
	static enumTypeInfo_t* FindEnumInfo(const char* enumName);
	
	static  std::string getEnumMemberName(const char* enumName, long long enumMemberVal);

};




