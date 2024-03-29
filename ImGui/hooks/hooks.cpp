#include <cstdio>
#include <mutex>
#include <thread>

#include "hooks.hpp"

#include "backend/dx10/hook_directx10.hpp"
#include "backend/dx11/hook_directx11.hpp"
#include "backend/dx12/hook_directx12.hpp"
#include "backend/dx9/hook_directx9.hpp"

#include "backend/opengl/hook_opengl.hpp"
#include "backend/vulkan/hook_vulkan.hpp"

#include "../console/console.hpp"
#include "../menu/menu.hpp"
#include "../utils/utils.hpp"

#include "../dependencies/minhook/MinHook.h"
#include <MinHook.h>
#include "../../Config/Config.h"
#include "../dependencies/imgui/imgui.h"
#include "../ImGuiDebug.h"
#include "../../Wolf2/ImGuiManager.h"
#include "../../ModSettings/ModSettings.h"
#include "../../Wolf2/MenuStateManager.h"
static HWND g_hWindow = NULL;
static std::mutex g_mReinitHooksGuard;

static DWORD WINAPI ReinitializeGraphicalHooks(LPVOID lpParam) {
    std::lock_guard<std::mutex> guard{g_mReinitHooksGuard};

    logInfo("[!] Hooks will reinitialize!\n");

    HWND hNewWindow = U::GetProcessWindow( );
    while (hNewWindow == reinterpret_cast<HWND>(lpParam)) {
        hNewWindow = U::GetProcessWindow( );
    }

    H::bShuttingDown = true;

    H::Free( );
    H::Init( );

    H::bShuttingDown = false;
    Menu::bShowMenu = false;

    return 0;
}





static WNDPROC oWndProc;


static LRESULT WINAPI WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

   
    if ((uMsg == WM_KEYDOWN) && (wParam == VK_ESCAPE)){
       Menu::bShowMenu = false;
       return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
    }
    else if ((MenuStateManager::get() == inDevMenu) && cachedCvarsManager::isWindowFocused()) {
        if (uMsg == WM_KEYDOWN) {
            int debug_wParam = (int)wParam;
            logInfo("debug_wParam: %d", debug_wParam);
            Menu::lastKeyPressed = static_cast<int>(wParam);
        }    
        
    }
    else {
        Menu::lastKeyPressed = -1;
    }
        
 

    if (uMsg == WM_DESTROY) {
        logInfo("WM_DESTROY triggered");
        HANDLE hHandle = CreateThread(NULL, 0, ReinitializeGraphicalHooks, hWnd, 0, NULL);
        if (hHandle != NULL)
            CloseHandle(hHandle);
    }


    LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

  
    ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
    ImGuiIO& io = ImGui::GetIO();


    if (Menu::bShowMenu)
    {
        io.MouseDrawCursor = true;  
        if (io.WantCaptureMouse ) {
            return true;
        }  
    }
    else {
        io.MouseDrawCursor = false;
    }
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


namespace Hooks {
    void Init( ) {
        g_hWindow = U::GetProcessWindow( );

#ifdef DISABLE_LOGGING_CONSOLE
        bool bNoConsole = GetConsoleWindow( ) == NULL;
        if (bNoConsole) {
            AllocConsole( );
        }
#endif

        RenderingBackend_t eRenderingBackend = U::GetRenderingBackend( );
        switch (eRenderingBackend) {
            case DIRECTX9:
                DX9::Hook(g_hWindow);
                break;
            case DIRECTX10:
                DX10::Hook(g_hWindow);
                break;
            case DIRECTX11:
                DX11::Hook(g_hWindow);
                break;
            case DIRECTX12:
                DX12::Hook(g_hWindow);
                break;
            case OPENGL:
                GL::Hook(g_hWindow);
                break;
            case VULKAN:
                VK::Hook(g_hWindow);
                break;
        }

#ifdef DISABLE_LOGGING_CONSOLE
        if (bNoConsole) {
            FreeConsole( );
        }
#endif

        oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
    }

    void Free( ) {
        if (oWndProc) {
            SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
        }

        MH_DisableHook(MH_ALL_HOOKS);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        RenderingBackend_t eRenderingBackend = U::GetRenderingBackend( );
        switch (eRenderingBackend) {
            case DIRECTX9:
                DX9::Unhook( );
                break;
            case DIRECTX10:
                DX10::Unhook( );
                break;
            case DIRECTX11:
                DX11::Unhook( );
                break;
            case DIRECTX12:
                DX12::Unhook( );
                break;
            case OPENGL:
                GL::Unhook( );
                break;
            case VULKAN:
                VK::Unhook( );
                break;
        }
    }
}   
