#pragma once

#include "idCvarManager.h"
#include "cachedCvarsManager.h"
#include "idCmdManager.h"



class timescaleManager
{
private:

	//static const float m_normalSpeedScaleF;
	//static const float m_fastForwardSpeedScaleF;

	//static inline const float m_timeScaleDefaultValF =  1.0f;
	static inline const std::vector<float> m_timeScaleValues = {1.0f, 10.0f, 20.0f, 50.0f };
	static inline const size_t m_defaultSpeedIndex = 0;
	static inline size_t m_currentSpeedIndex = 0;
	

public:
	static void increaseSpeed();
	static void resetSpeed();

	static size_t getCurrentSpeedIndex();

	static float getCurrentTimeScaleValF();

	static void updateSpeed();

	static bool isFastForwardTimeScale();
	//static void setMaxSpeed();
	//static void setDefaultSpeed();
	
	//todo: implement this:
	//static void checkSpeed(); //! make sure we're not max speed during gameplay sequences

};

