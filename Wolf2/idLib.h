#pragma once
#include "../Config/Config.h"


//? side note: class who have member functions defined directly within the class definition are implicitly inline functions, which is why you can add this file to many other file and not break the one definition rule.

//struct idStr {
//	char pad_K_000;
//	//Offset 8,	 size 8
//	char* data;
//	//Offset 16,	 size 4
//	int len;
//	//Offset 20,	 size 4
//	//top bit is used to store a flag that indicates if the string data is static or not
//	int allocedAndFlag;
//	//Offset 24,	 size 20
//	char baseBuffer[20] ;
//};

struct idHashIndex {
	//Offset 0x0,	 size 8
	int* hash;
	//Offset 0x8,	 size 8
	int* indexChain;
	//Offset 0x10,	 size 4
	int hashSize;
	//Offset 0x14,	 size 4
	int indexSize;
	//Offset 0x18,	 size 4
	int granularity;
	//Offset 0x1C,	 size 4
	int hashMask;
	//Offset 0x20,	 size 4
	int lookupMask;
	//Offset 0x24,	 size 4
	int memTag;
};



struct idStr {
	char pad_K_000;
	//Offset 0x8,	 size 8
	char* data;
	//Offset 0x10,	 size 4
	int len;
	//Offset 0x14,	 size 4
	int allocedAndFlag; //? it seems this is a flag to indicate if data is static or not. 
	//Offset 0x18,	 size 24
	char baseBuffer[24];
};



struct idManagedClassPtrBase {
	//Offset 0x0 	Size 0x8 (8)
	void* ptr; // idManagedClass* ptr;
	//Offset 0x8 	Size 0x8 (8)
	idManagedClassPtrBase* next;
	//Offset 0x10 	Size 0x8 (8)
	idManagedClassPtrBase* prev;
	//Offset 0x18 	Size 0x4 (4)
	int spawnId; // idSpawnId spawnId;
}; // Size: 0x20 (Size Dec: 32)

//struct idListVoid
//{
//	unsigned __int64* list;
//	int num;
//	int size;
//	__int16 granularity;
//	unsigned __int8 memTag;
//	unsigned __int8 listStatic;
//};


struct swfRect_t;

struct idStrId {
	//Offset 0,	 size 4	
	unsigned int id;
};

//struct idList
//{
//	unsigned __int64* list; // deref of this should be the first elem of the list
//	int num;
//	int size;
//	__int16 granularity;
//	unsigned __int8 memTag;
//	unsigned __int8 listStatic;
//};


//? 16/9/24 after the big crash, i thought this was the reason we got crashes but it seems fine.
//! 15/9/24 updated this as we were using the old IdList from DE which is shorter, this one has a pad at the end
//struct idListBase {
struct idList {
	//Offset 0x0 	Size 0x8 (8)
	unsigned __int64* list;
	//Offset 0x8 	Size 0x4 (4)
	int num;
	//Offset 0xC 	Size 0x4 (4)
	int size;
	//Offset 0x10 	Size 0x4 (4)
	int granularity;
	//Offset 0x14 	Size 0x2 (2)
	short memTag;
	//Offset 0x16 	Size 0x2 (2)
	short listStatic;
	//Offset 0x18 	Size 0x8 (8)
	unsigned long long padd; // yes this is fomr the lib itself i didn't add that
}; // Size: 0x20 (Size Dec: 32)



struct commandDef_s {
	//Offset 0x0 	Size 0x8 (8)
	char* name;
	//Offset 0x8 	Size 0x8 (8)
	void* function;//void(const idCmdArgs& args)* function;
	//Offset 0x10 	Size 0x8 (8)
	void* argCompletion; // void(idAutoComplete& autoComplete)* argCompletion;
	//Offset 0x18 	Size 0x8 (8)
	char* description;
	//Offset 0x20 	Size 0x4 (4)
	int flags;
}; // Size: 0x28 (Size Dec: 40)


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






struct constantInfo_t {
	//Offset 0x0,	 size 8
	char* type;
	//Offset 0x8,	 size 8
	char* name;
	//Offset 0x10,	 size 8
	char* value;
};

struct functionPointerInfo_t {
	//Offset 0x0,	 size 8
	char* name;
	//Offset 0x8,	 size 8
	void* ptr;
};


struct typeInfo_t {
	//Offset 0x0,	 size 8
	constantInfo_t* constants;
	//Offset 0x8,	 size 4
	int numConstants;
	//Offset 0x10,	 size 8
	enumTypeInfo_t* enums;
	//Offset 0x18,	 size 4
	int numEnums;
	//Offset 0x20,	 size 8
	classTypeInfo_t* classes;
	//Offset 0x28,	 size 4
	int numClasses;
	//Offset 0x30,	 size 8
	typedefInfo_t* typedefs;
	//Offset 0x38,	 size 4
	int numTypedefs;
	//Offset 0x40,	 size 8
	functionPointerInfo_t* functionPointers;
	//Offset 0x48,	 size 4
	int numfunctionPointers;
};



struct idTypeInfoTools {
	//Offset 0x0,	 size 8
	typeInfo_t* typeInfo;
	//Offset 0x8,	 size 40
	idHashIndex enumHash;
	//Offset 0x30,	 size 40
	idHashIndex classHash;
	//Offset 0x58,	 size 32
	idList /*< idTypeInfoTools::readWrite_t, TAG_IDLIB, false >*/ enumObject;
	//Offset 0x78,	 size 32
	idList /*< idTypeInfoTools::readWrite_t, TAG_IDLIB, false >*/ enumPointer;
	//Offset 0x98,	 size 32
	idList /*< idTypeInfoTools::readWrite_t, TAG_IDLIB, false >*/ classObject;
	//Offset 0xB8,	 size 32
	idList /*< idTypeInfoTools::readWrite_t, TAG_IDLIB, false >*/ classPointer;
	//Offset 0xD8,	 size 32
	char jsonSerializers[32];//idHashTableT < idStr, idTypeInfoTools::jsonReadWrite_t, 4 > jsonSerializers;
	//Offset 0xF8,	 size 32
	char jsonIgnoredVariables[32];  //idHashTableT < idStr, idList < idStr, TAG_IDLIB >, 4 > jsonIgnoredVariables;
	//Offset 0x118,	 size 4
	int editDepth;
	//Offset 0x11C,	 size 4
	int designDepth;
	//Offset 0x120,	 size 4
	int defDepth;
	//Offset 0x128,	 size 32
	idList  warnings;/*< idStr, TAG_IDLIST, false >*/
};





struct idVec3 {
	float x = 0;
	float y = 0;
	float z = 0;

	float Distance(idVec3& other) {

		float xx = x - other.x;
		float yy = y - other.y;
		float zz = z - other.z;
		xx *= xx;
		yy *= yy;
		zz *= zz;

		return sqrtf(xx + yy + zz);

	}

	void Set(float val) {
		x = val;
		y = val;
		z = val;
	}
};
struct idVec2 {
	float x = 0;
	float y = 0;

	void set(float _x, float _y) {
		x = _x;
		y = _y;
	}

};

struct idVec2i {
	//Offset 0x0,	 size 4
	int x;
	//Offset 0x4,	 size 4
	int y;
};

struct swfRect_t {
	//Offset 0,	 size 8
	idVec2 tl;
	//Offset 8,	 size 8
	idVec2 br;

	swfRect_t() {}

	swfRect_t(float x, float y, float w, float h)
	{
		tl.x = x;
		tl.y = y;
		br.x = x + w;
		br.y = y + h;
	}
	float getWidth() {
		return br.x - tl.x;
	}
	float getHeight() {
		return br.y - tl.y;
	}	

};


struct idVec4 {
	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;


	idVec4(){}

	idVec4(float _x, float _y, float _w, float _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	idVec4(swfRect_t swfRect) {
		x = swfRect.tl.x;
		y = swfRect.tl.y;
		w = swfRect.br.x - swfRect.tl.x;
		h = swfRect.br.y - swfRect.tl.y;
	}

	void update(float _x, float _y, float _w, float _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	void print() {
		logInfo("print:  x: %.2f, y: %.2f, w: %.2f, h: %.2f,", x, y, w, h);
	}

	std::string getStrData() {
		return "x: " + std::to_string(x) + " y: " + std::to_string(y) + " w: " + std::to_string(w) + " h: " + std::to_string(h);
	}

	void printMsg(std::string str) {
		logInfo("printMsg: %s:  x: %.2f, y: %.2f, w: %.2f, h: %.2f,", str.c_str(), x, y, w, h);
	}
};

struct idVec4_Bounds {
	float tl_x = 0;
	float tl_y = 0;
	float br_x = 0;
	float br_y = 0;
};



struct idMat2 {
	//Offset 0x0,	 size 16
	idVec2 mat[2];
};


struct idMat3 {
	//Offset 0x0,	 size 36
	idVec3 mat[3];
};


struct idMat3x4 {
	//Offset 0x0,	 size 48
	float mat[12];
};


struct idMat4 {
	//Offset 0x0,	 size 64
	idVec4 mat[4];
};




struct idMatX {
	//Offset 0x0,	 size 4
	int numRows;
	//Offset 0x4,	 size 4
	int numColumns;
	//Offset 0x8,	 size 4
	int alloced;
	//Offset 0x10,	 size 8
	float* mat;
};




struct  idQuat {
	//Offset 0,	 size 4
	//METASTATE|ALLOCATOR|SAVESKIP
	//x-component
	float x;
	//Offset 4,	 size 4
	//METASTATE|ALLOCATOR|SAVESKIP
	//y-component
	float y;
	//Offset 8,	 size 4
	//METASTATE|ALLOCATOR|SAVESKIP
	//z-component
	float z;
	//Offset 12,	 size 4
	//METASTATE|ALLOCATOR|SAVESKIP
	//w-component
	float w;
};



//! this is from the swfFillStyle_t.h file

struct  swfMatrix_t {
	//Offset 0,	 size 4
	float xx;
	//Offset 4,	 size 4
	float yy;
	//Offset 8,	 size 4
	float xy;
	//Offset 12,	 size 4
	float yx;
	//Offset 16,	 size 4
	float tx;
	//Offset 20,	 size 4
	float ty;
};


struct  swfColorRGB_t {
	//Offset 0,	 size 1
	unsigned char r;
	//Offset 1,	 size 1
	unsigned char g;
	//Offset 2,	 size 1
	unsigned char b;
};

struct  swfColorRGBA_t : public swfColorRGB_t {
	//Offset 3,	 size 1
	unsigned char a;

	void setColor(const swfColorRGBA_t& color2) {
		r = color2.r;
		g = color2.g;
		b = color2.b;
		a = color2.a;
	}

	bool isEqual(const swfColorRGBA_t& color2) {
		return r == color2.r &&
			g == color2.g &&
			b == color2.b &&
			a == color2.a;
	}
	
};


struct  swfGradientRecord_t {
	//Offset 0,	 size 1
	unsigned char startRatio;
	//Offset 1,	 size 1
	unsigned char endRatio;
	//Offset 2,	 size 4
	swfColorRGBA_t startColor;
	//Offset 6,	 size 4
	swfColorRGBA_t endColor;
};


struct swfGradient_t {
	//Offset 0,	 size 1
	unsigned char numGradients;
	//Offset 1,	 size 160
	swfGradientRecord_t gradientRecords[16];
};






struct  swfFillStyle_t {
	//Offset 0,	 size 1
	//0 = solid, 1 = gradient, 4 = bitmap
	unsigned char type;
	//Offset 1,	 size 1
	//0 = linear, 2 = radial, 3 = focal; 0 = repeat, 1 = clamp, 2 = near repeat, 3 = near clamp
	unsigned char subType;
	//Offset 2,	 size 4
	//if type = 0   <<<<<<<<<<<<<<<<<<<<------------
	swfColorRGBA_t startColor;
	//Offset 6,	 size 4
	//if type = 0 <<<<<<<<<<<<<<<<<<<<------------
	swfColorRGBA_t endColor;
	//Offset 12,	 size 24
	//if type > 0
	swfMatrix_t startMatrix;
	//Offset 36,	 size 24
	//if type > 0
	swfMatrix_t endMatrix;
	//Offset 60,	 size 161
	//if type = 1
	swfGradient_t gradient;
	//Offset 224,	 size 4
	//if type = 1 and subType = 3
	float focalPoint;
	//Offset 228, 0xE4	 size 2
	//if type = 4
	unsigned short bitmapID;


	void print() {
		logInfo("swfFillStyle_t print: type: %u subType: %u  bitmapID: %hu startColor: r:%u g:%u b:%u a:%u endColor: r:%u g:%u b:%u a:%u", type, subType, bitmapID, startColor.r, startColor.g, startColor.b, startColor.a, endColor.r, endColor.g, endColor.b, endColor.a);
	}
};



struct idAtomicString {
	//Offset 0,	 size 8
	char* str;
};

struct idDeduplicatedString {
	//Offset 0x0,	 size 8
	char* str;
};






