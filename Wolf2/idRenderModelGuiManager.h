#pragma once



#include "idColor.h"
#include "../Config/Config.h"
#include "../MemHelper/MemHelper.h"


class idRenderModelGuiManager
{

private:

	static __int64 m_whiteMaterial;

	static const unsigned int m_packedColorOffset;
	static const unsigned int m_frameNumOffset;

	static const float s1_default;
	static const float t1_default;
	static const float s2_default;
	static const float t2_default;

	static unsigned int m_lastFramNumber;

	//! DrawStretchPic(guiPtr, x, y, z, w, h, s1, t1, s2, t2, mapPtr)
	typedef void(__fastcall* idRenderModelGui_DrawStretchPic)(__int64 guiPtr_a1, float x_a2, float y_a3, float z_a4, float w_a5, float h_a6, float s1_a7, float t1_a8, float s2_a9, float t2_a10, __int64 mtr_a11);
	//static idRenderModelGui_DrawStretchPic m_pidRenderModelGui_DrawStretchPic;

	static __int64 m_idRenderModelGui_DrawStretchPicFAddr;

public:

	static bool acquireWhiteMaterialAddr(__int64 _whiteMtr);

	static bool acquireDrawStretchPicFuncAddr(__int64 funcAddr);

	static void setColor(__int64 idRenderModelGuiAdrr, const idColor& idColor);

	static void drawColoredRect(__int64 idRenderModelGuiAdrr, float x, float y, float width, float height, idColor color);

	static void updateLastFrameNumber(__int64 idRenderModelGuiAdrr);

	static unsigned int getCurrentFrameNumber(__int64 idRenderModelGuiAdrr);

	static bool isWhiteMaterialacquired();

	static void acquireWhiteMaterial();

	//static void drawStretchPic(__int64 guiPtr_a1, float x_a2, float y_a3, float z_a4, float w_a5, float h_a6, float s1_a7, float t1_a8, float s2_a9, float t2_a10, __int64 mtr_a11);
};

