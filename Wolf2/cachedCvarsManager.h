#pragma once

#include "idCvarManager.h"
#include "GeneratedEnums.h"
#include "cameraManager.h"



//! caching to optimize performance in takss like crosshair rendering
//? aftet some thinking, i realized this is a bit unecessary for most of these cvars...as most are not time constrained as they are set once we get out of mod menu.
class cachedCvarsManager
{
private:
	static idCVar* m_windowWidthCached;
	static idCVar* m_windowHeightCached;
	//! this is used to prevent keypress from triggering key press actions when user alt tabs
	static idCVar* m_win_hasFocusCached;
	static idCVar* m_swf_safeFrameCached;
	static idCVar* m_swf_timescaleCached;
	static idCVar* m_swf_skipRenderText;
	static idCVar* m_pm_animCamAmount;
	static idCVar* m_sensitivity; // 

	static const float m_swf_safeFrameDefaultVal; //! because use in imgui

	//! finding good enough value through trial and error
	static const inline float m_headbobResetIncrements = 0.02f;


	//static idCVar* m_showDevMenuCached;
	//static idCVar* m_unlockMouseInMenusCached;
	//static idCVar* m_win_pauseOnAltTabCached;
	//static idCVar* m_testMaterialCached;
	//static idCVar* m_setTimeScaleCached;
	//static idCVar* m_showWorldMarkersCached;


public :


	static const float m_safeFrameValueMax;

	static bool cacheCriticalCvars();

	static int get_WindowWidthInt();

	static int get_WindowHeightInt();

	static bool isWindowFocused();
	
	static void debugLogWin_hasFocusCvar();

	static float getMouseSens();

	static void setMouseSens(float sens);

	static void setSafeFrame(float safeFrameFloat);

	static void setSafeFrameToDefault();

	static void setTimescale(float timeScaleF);

	static float getTimescaleF();

	static void skipRenderText(bool isSkipRenderText);

	static void setAnimCamAmount(float animCamAmountF, AnimCamAmountChangeReson reason);

	//! this is to prevent the jarring effect when user stops firing and AnimCamAmount goes from 1 to 0.1 and snaps the camera into place which is very visible . Not a great way to do it but let's see at least if it works
	static bool setUserAnimCamAmountProgressive();

	

	/*static float get_Fov();

	static void setShowOptionForDevMenu(bool isOn);

	static void setUnlockMouseInMenu(bool isTrue);

	static void setPauseGameOnAltTab(bool isTrue);

	static void testMaterial(const char* matrName);

	static void setTimeScale(const char* scaleStr);*/

};

