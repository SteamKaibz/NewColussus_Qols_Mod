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

struct idList
{
	unsigned __int64* list; // deref of this should be the first elem of the list
	int num;
	int size;
	__int16 granularity;
	unsigned __int8 memTag;
	unsigned __int8 listStatic;
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






