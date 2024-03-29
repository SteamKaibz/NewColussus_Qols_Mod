#pragma once


#include <cstdint>
#include "../Config/Config.h"
#include "../MemHelper/MemHelper.h"


//types def from meathook: 
#pragma pack(push, 1)
struct enumValueInfo_t {
	//offset 0 , size 8
	char* name;
	//offset 8 , size 4
	long long value;

};
//struct enumTypeInfo_t {
//	//offset 0 , size 8
//	char* name;
//	//offset 8 , size 4
//	unsigned long long flags;
//	int type;
//	int valueIndexLength;
//
//	//offset 16 , size 8
//	enumValueInfo_t* values;
//	int* valueIndex;
//};

struct enumTypeInfo_t {	
	char* name;	
	int unknown_1;
	int unknown_2;
	int unknown_3;
	int unknown_4;
	enumValueInfo_t* values;
};



struct typedefInfo_t {
	char* name;
	char* type;
	char* ops;
	int size;
	int padding;
};
struct classMetaDataInfo_t
{
	char* metaData;
};
#pragma pack(pop)

#pragma pack(push, 1)


//struct classVariableInfo_t_BAK
//{
//	char* type;
//	char* ops;
//	char* name;
//	int offset;
//	int size;
//	int flags;
//	//char pad36[4];
//	int m_mh_added_delta2type; //delta to FindClassInfo(type)
//	char* comment;//i dont think anything in the engine actually uses comment, so i might be able to pack it into a delta and put more data here if i ever need it
//	int (*get)(void* ptr);
//	//offset 56 , size 8
//	void (*set)(void* ptr, int value);
//	//offset 64 , size 8
//	void* (*reallocate)(void* ptr, const int oldNum, const int newNum, const int tag, const bool zeroBuffer);
//
//};

//! done this manually
//struct classVariableInfo_t
//{
//	char* type;
//	char* ops;
//	char* name;
//	int offset;
//	int size;
//	void* typeInfoInstPtr;
//	int unknown_1;
//	int unknown_2;
//	void* unknownPtr;
//	int inknown_3;
//	int inknown_4;
//	int inknown_5;
//	int inknown_6;
//	int inknown_7;
//	int inknown_8;
//};

//! from our idLib, with some tweaks
struct classVariableInfo_t {
	//Offset 0x0,	 size 8
	char* type;
	//Offset 0x8,	 size 8
	char* ops;
	//Offset 0x10,	 size 8
	char* name;
	//Offset 0x18,	 size 4
	int offset;
	//Offset 0x1C,	 size 4
	int size;
	//Offset 0x20,	 size 8
	std::type_info* type_id;
	//Offset 0x28,	 size 8
	long long flags;
	//Offset 0x30,	 size 8
	char* comment;
	//Offset 0x38,	 size 8
	int (*get)(void* ptr);
	//Offset 0x40,	 size 8
	void (*set)(void* ptr, int value);
	//Offset 0x48,	 size 8
	void* (*reallocate)(void* ptr, const int oldNum, const int newNum, const int tag, const bool zeroBuffer);	
};


#pragma pack(pop)
struct idClass;
struct idRenderModel;
struct idDeclModelAsset;

#pragma pack(push, 1)

/*
	we replace all classes metaData pointers with pointers to the one in here.
	then we just recast to be able to search for a fields index. when you have the index you can just look it up in variables
*/
struct mh_classtypeextra_t {

	classMetaDataInfo_t m_metadata;

	//
	unsigned m_num_fields;

	unsigned m_offset2fields; //add to this to get base of field props
};


//! from out lib with little tweaks:
struct classTypeInfo_t {
	//Offset 0x0,	 size 8
	char* name;
	//Offset 0x8,	 size 8
	char* superType;
	//Offset 0x10,	 size 4
	int size;
	//Offset 0x14,	 size 4
	int pad_allignment; // this is just something we added to make sure it's alligned.
	//Offset 0x18,	 size 8
	std::type_info* type_id;
	//Offset 0x20,	 size 8
	classVariableInfo_t* templateParms;
	//Offset 0x28,	 size 8
	classVariableInfo_t* variables;
	//Offset 0x30,	 size 8
	idClass* (*createInstance)();
	//Offset 0x38,	 size 8
	idRenderModel* (*createModel)(const idDeclModelAsset* modelAsset, const unsigned int createFlags);
	//Offset 0x40,	 size 8
	classMetaDataInfo_t* metaData;
};

//§ this is size 0x50...
//struct classTypeInfo_t
//{
//	char* name;
//	char* superType;
//	int size;
//
//	//char pad20[4];
//	//this is padding in the engine originally, but we co-opt it to store the byte delta from the start of this class to
//	//the start of its super class, allowing us to traverse the inheritance chain without having to go through findclassinfo's hashing and searching
//	//this could be made to be fewer bits if i need other stuff in here in the future
//	//also, it could be shifted to the right by 3 to make room for more bits since it should always be 8 byte aligned
//	int m_mh_added_delta2super;
//	classVariableInfo_t* templateParms;
//	char pad_0[8]; //! added pad to make variables to offset variables location in the struct
//	classVariableInfo_t* variables; //! this is now at offset 0x28 but in Eternal it's at offset 0x20
//	unsigned long long* variableNameHashes;
//
//	idClass* (*createInstance)();
//	idRenderModel* (*createModel)(const idDeclModelAsset* modelAsset, const unsigned int createFlags);
//	classMetaDataInfo_t* metaData;
//};
#pragma pack(pop)

struct idClass;
template<typename T>
struct  idHierarchy
{
	idHierarchy<T>* parent;
	idHierarchy<T>* sibling;
	idHierarchy<T>* child;
	T* owner;
};









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
	
	static classTypeInfo_t* findClassInfo(const char* className);

	static classVariableInfo_t* findClassField(const char* cname, const char* fieldname);	

	static bool AreStringsEqual(const char* str1, const char* str2);

	static classVariableInfo_t* findClassFirstField(const char* cname);
	
	static enumTypeInfo_t* FindEnumInfo(const char* enumName);
	
	static  std::string getEnumMemberName(const char* enumName, long long enumMemberVal);

};




