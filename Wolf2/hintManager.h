#pragma once


#include "../Config/Config.h"


class hintManager
{

private:
	//! this is state but it's ok this time there is not deref of any kind happening.
	static bool m_wasHintBtnPressed;
public:


	static void setHintBtnPressState(bool wasPressed);
	static bool wasHintBtnPressed();
};

