#pragma once

#include <Windows.h>
#include "../dependencies/imgui/imgui.h"
#include "menu.hpp"



class fastForwardGui
{
private:

public:
	//static void showFastForwardIcon(bool* p_open = NULL);
	static std::string getCurrentSpeedStr();
	static ImVec4& getSpeedTextColorVec4();
	static void show(bool* p_open = NULL);
};

