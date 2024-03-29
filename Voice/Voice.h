#pragma once
#include <windows.h>
#include <sapi.h>
#include <string>
#include <queue>
#include "../Config/Config.h"






class TTS
{
private:
    static std::queue<std::wstring> m_wstrsQueue;
public:
    static void addToQueue(std::wstring wstr);
    static void sayAllInQueue();


};





