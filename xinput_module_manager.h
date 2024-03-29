#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include <windows.h>

#include "xinput.h"
#include "Common.h"
#include "Config/Config.h"

class XInputModuleManager : NonCopyable
{
public:
	DWORD XInputGetState( DWORD dwUserIndex, XINPUT_STATE* pState ) {
		if( !m_XInputGetState ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return m_XInputGetState( dwUserIndex, pState );
	}

	DWORD XInputSetState( DWORD dwUserIndex, XINPUT_VIBRATION* pVibration ) {
		if( !m_XInputSetState ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return m_XInputSetState( dwUserIndex, pVibration );
	}

	DWORD XInputGetCapabilities( DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities ) {
		if( !m_XInputGetCapabilities ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return m_XInputGetCapabilities( dwUserIndex, dwFlags, pCapabilities );
	}

	VOID XInputEnable( BOOL enable ) {
		if( !m_XInputEnable ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return;
		}

		m_XInputEnable( enable );
	}

	DWORD XInputGetDSoundAudioDeviceGuids( DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid ) {
		if( !m_XInputGetDSoundAudioDeviceGuids ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputGetDSoundAudioDeviceGuids( dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid );
	}

	DWORD XInputGetBatteryInformation( DWORD  dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION* pBatteryInformation ) {
		if( !m_XInputGetBatteryInformation ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputGetBatteryInformation( dwUserIndex, devType, pBatteryInformation );
	}

	DWORD XInputGetKeystroke( DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke ) {
		if( !m_XInputGetKeystroke ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputGetKeystroke( dwUserIndex, dwReserved, pKeystroke );
	}

	DWORD XInputGetStateEx( DWORD dwUserIndex, XINPUT_STATE *pState ) {
		if( !m_XInputGetStateEx )
			return XInputGetState( dwUserIndex, pState );

		return XInputGetStateEx( dwUserIndex, pState );
	}

	DWORD XInputWaitForGuideButton( DWORD dwUserIndex, DWORD dwFlag, LPVOID pVoid ) {
		if( !m_XInputWaitForGuideButton ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputWaitForGuideButton( dwUserIndex, dwFlag, pVoid );
	}

	DWORD XInputCancelGuideButtonWait( DWORD dwUserIndex ) {
		if( !m_XInputCancelGuideButtonWait ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputCancelGuideButtonWait( dwUserIndex );
	}

	DWORD XInputPowerOffController( DWORD dwUserIndex ) {
		if( !m_XInputPowerOffController ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputPowerOffController( dwUserIndex );
	}

	DWORD XInputGetAudioDeviceIds( DWORD dwUserIndex, LPWSTR pRenderDeviceId, UINT* pRenderCount, LPWSTR pCaptureDeviceId, UINT* pCaptureCount ) {
		if( !m_XInputGetAudioDeviceIds ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputGetAudioDeviceIds( dwUserIndex, pRenderDeviceId, pRenderCount, pCaptureDeviceId, pCaptureCount );
	}

	DWORD XInputGetBaseBusInformation( DWORD dwUserIndex, struct XINPUT_BUSINFO* pBusinfo ) {
		if( !m_XInputGetBaseBusInformation ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputGetBaseBusInformation( dwUserIndex, pBusinfo );
	}

	DWORD XInputGetCapabilitiesEx( DWORD unk1, DWORD dwUserIndex, DWORD dwFlags, struct XINPUT_CAPABILITIESEX* pCapabilitiesEx ) {
		if( !m_XInputGetCapabilitiesEx ) {
			//PrintWarning( "Call to unimplemented function "__FUNCTION__ );

			return ERROR_SUCCESS;
		}

		return XInputGetCapabilitiesEx( unk1, dwUserIndex, dwFlags, pCapabilitiesEx );
	}

    XInputModuleManager( )
	: m_XInputGetState( nullptr )
	, m_XInputSetState( nullptr )
	, m_XInputGetCapabilities( nullptr )
	, m_XInputEnable( nullptr )
	, m_XInputGetDSoundAudioDeviceGuids( nullptr )
	, m_XInputGetBatteryInformation( nullptr )
	, m_XInputGetKeystroke( nullptr )
	, m_XInputGetStateEx( nullptr )
	, m_XInputWaitForGuideButton( nullptr )
	, m_XInputCancelGuideButtonWait( nullptr )
	, m_XInputPowerOffController( nullptr ) {
		//PrintDebug( __FUNCTION__ );

        std::string current_module;
        ModuleFileName(&current_module, CurrentModule());

		std::transform( current_module.begin( ), current_module.end( ), current_module.begin( ), ::tolower );

        std::string loaded_module_path;

		if( current_module.find( "xinput1_3.dll" ) == std::string::npos )
			m_module = LoadLibraryCurrent( "xinput1_3.dll", &loaded_module_path );

		if( !m_module )
			m_module = LoadLibrarySystem( current_module, &loaded_module_path );

		if (!m_module)
        {
            HRESULT hr = GetLastError();
            std::unique_ptr<char[]> error_msg(new char[MAX_PATH]);
            sprintf_s(error_msg.get(), MAX_PATH, "Cannot load \"%s\" error: 0x%x", loaded_module_path.c_str(), hr);
			logErr(error_msg.get());
			//PrintError(error_msg.get());
            MessageBoxA(NULL, error_msg.get(), "Error", MB_ICONERROR);
            exit(hr);
        }
        else
        {
			logInfo("Loaded \"%s\"", loaded_module_path.c_str());
            //PrintInfo("Loaded \"%s\"", loaded_module_path.c_str());
        }

        // XInput 1.3 and older functions
		GetProcAddress( "XInputGetState", &m_XInputGetState );
		GetProcAddress( "XInputSetState", &m_XInputSetState );
		GetProcAddress( "XInputGetCapabilities", &m_XInputGetCapabilities );
		GetProcAddress( "XInputEnable", &m_XInputEnable );
		GetProcAddress( "XInputGetDSoundAudioDeviceGuids", &m_XInputGetDSoundAudioDeviceGuids );
		GetProcAddress( "XInputGetBatteryInformation", &m_XInputGetBatteryInformation );
		GetProcAddress( "XInputGetKeystroke", &m_XInputGetKeystroke );

        // XInput 1.3 undocumented functions
		GetProcAddress( ( const char* ) 100, &m_XInputGetStateEx );
		GetProcAddress( ( const char* ) 101, &m_XInputWaitForGuideButton );
		GetProcAddress( ( const char* ) 102, &m_XInputCancelGuideButtonWait );
		GetProcAddress( ( const char* ) 103, &m_XInputPowerOffController );

		// XInput 1.4 functions
		GetProcAddress( "XInputGetAudioDeviceIds", &m_XInputGetAudioDeviceIds );

		// XInput 1.4 undocumented functionss
		GetProcAddress( ( const char* ) 104, &m_XInputGetBaseBusInformation );
		GetProcAddress( ( const char* ) 108, &m_XInputGetCapabilitiesEx );
    }

    ~XInputModuleManager()
    {
		if (m_module)
        {
            std::string xinput_path;
			ModulePath(&xinput_path, m_module);
			logInfo("Unloading %s", xinput_path.c_str());
            //PrintInfo("Unloading %s", xinput_path.c_str());
			FreeLibrary(m_module);
        }
    }

    static XInputModuleManager& Get()
    {
        static XInputModuleManager instance;
        return instance;
    }

private:
	// XInput 1.3 and older functions
	DWORD( WINAPI* m_XInputGetState )( DWORD dwUserIndex, XINPUT_STATE* pState );
	DWORD( WINAPI* m_XInputSetState )( DWORD dwUserIndex, XINPUT_VIBRATION* pVibration );
	DWORD( WINAPI* m_XInputGetCapabilities )( DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities );
	VOID( WINAPI* m_XInputEnable )( BOOL enable );
	DWORD( WINAPI* m_XInputGetDSoundAudioDeviceGuids )( DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid );
	DWORD( WINAPI* m_XInputGetBatteryInformation )( DWORD  dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION* pBatteryInformation );
	DWORD( WINAPI* m_XInputGetKeystroke )( DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke );

	// XInput 1.3 undocumented functions
	DWORD( WINAPI* m_XInputGetStateEx )( DWORD dwUserIndex, XINPUT_STATE *pState ); // 100
	DWORD( WINAPI* m_XInputWaitForGuideButton )( DWORD dwUserIndex, DWORD dwFlag, LPVOID pVoid ); // 101
	DWORD( WINAPI* m_XInputCancelGuideButtonWait )( DWORD dwUserIndex ); // 102
	DWORD( WINAPI* m_XInputPowerOffController )( DWORD dwUserIndex ); // 103

	// XInput 1.4 functions
	DWORD( WINAPI* m_XInputGetAudioDeviceIds )( DWORD dwUserIndex, LPWSTR pRenderDeviceId, UINT* pRenderCount, LPWSTR pCaptureDeviceId, UINT* pCaptureCount );

	// XInput 1.4 undocumented functionss
	DWORD( WINAPI* m_XInputGetBaseBusInformation )( DWORD dwUserIndex, struct XINPUT_BUSINFO* pBusinfo ); // 104
	DWORD( WINAPI* m_XInputGetCapabilitiesEx )( DWORD unk1, DWORD dwUserIndex, DWORD dwFlags, struct XINPUT_CAPABILITIESEX* pCapabilitiesEx ); // 108

    template<typename T>
	inline void GetProcAddress(const char* funcname, T* ppfunc)
    {
        *ppfunc = reinterpret_cast<T>(::GetProcAddress(m_module, funcname));
    }

    HMODULE m_module;
};