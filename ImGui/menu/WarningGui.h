#pragma once


#include <Windows.h>
#include "../dependencies/imgui/imgui.h"
#include "menu.hpp"
#include "../../Wolf2/MenuStateManager.h"


class WarningGui
{
private:

public:

	static void showWarningWindow(bool* p_open = NULL);
};

