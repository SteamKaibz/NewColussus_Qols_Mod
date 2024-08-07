#pragma once

#include <vector>
#include <string>

class ImGuiDebugWin
{
    static std::vector<std::string> messages;

public:
    
    static std::vector<std::string> getMessages();
    static void AddMessage(const std::string message);
    static void ClearMessages();   

};

