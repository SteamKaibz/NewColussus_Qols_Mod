#pragma once

#include "idCvarManager.h"
#include "cachedCvarsManager.h"



class timescaleManager
{
private:

	static const float m_normalSpeedScaleF;
	static const float m_fastForwardSpeedScaleF;

public:
	static void setMaxSpeed();
	static void setDefaultSpeed();
	static bool isFastForwardTimeScale();
	//todo: implement this:
	//static void checkSpeed(); //! make sure we're not max speed during gameplay sequences

};

