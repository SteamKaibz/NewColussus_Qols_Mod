#pragma once


#include "idColor.h"
#include "../Config/Config.h"
#include "../MemHelper/MemHelper.h"
#include "cachedCvarsManager.h"


class idRenderModelGuiManager
{

private:

	static inline __int64 m_idRenderModelGui_DrawStretchPicFAddr = 0;
	static inline _int64  m_idRenderModelGui_DrawSringFAddr = 0;

	static inline __int64 m_whiteMaterial = 0;

	static inline const unsigned int m_packedColorOffset = 0x418;

	static inline const float s1_default = 0.0;
	static inline const float t1_default = 0.0;
	static inline const float s2_default = 1.0;
	static inline const float t2_default = 1.0;

	static inline  unsigned int m_lastFramNumber = 0;
	static inline const unsigned int m_frameNumOffset = 0x446C;


	//! DrawStretchPic(guiPtr, x, y, z, w, h, s1, t1, s2, t2, mapPtr)
	typedef void(__fastcall* idRenderModelGui_DrawStretchPic)(__int64 guiPtr_a1, float x_a2, float y_a3, float z_a4, float w_a5, float h_a6, float s1_a7, float t1_a8, float s2_a9, float t2_a10, __int64 mtr_a11);
	
	typedef __int64(__fastcall* idRenderModelGui_DrawString_t)(
	void* idRenderModelGui_a1,
	float a2,
	float a3,
	unsigned __int8* charPtr_a4,
	__int64 a5,
	char a6,
	float a7);


public:

	static bool acquireWhiteMaterialAddr(__int64 _whiteMtr);

	static bool acquireDrawStretchPicFuncAddr(__int64 funcAddr);

	static void setColor(__int64 idRenderModelGuiAdrr, const idColor& idColor);

	static void drawColoredRect(__int64 idRenderModelGuiAdrr, float x, float y, float width, float height, idColor color);

	static void updateLastFrameNumber(__int64 idRenderModelGuiAdrr);

	static unsigned int getCurrentFrameNumber(__int64 idRenderModelGuiAdrr);

	static bool isWhiteMaterialacquired();

	static void acquireWhiteMaterial();

	static std::string getDisplayDbgInfoStr();

	//static void drawStretchPic(__int64 guiPtr_a1, float x_a2, float y_a3, float z_a4, float w_a5, float h_a6, float s1_a7, float t1_a8, float s2_a9, float t2_a10, __int64 mtr_a11);
};

