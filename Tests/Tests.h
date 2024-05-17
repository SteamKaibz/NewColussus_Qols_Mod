#pragma once


#include "../Wolf2/idGameLocalManager.h"
#include "../Wolf2/GeneratedClasses.h"


class Tests
{
private:
	static movementMode_t m_lastPendingMovementMode;   
	static movementMode_t m_lastCurrentMovementMode;

	idPlayer* m_lastIdPlayer = nullptr;
	char* m_lastCinematicMtrPtr = nullptr;
	__int64 m_lastCinematicMtrAddr = 0;

	static std::vector<__int64> addArgFrom_371DB0_Vec;

public:
	//void printUsercmdAddrs();

	static std::string getmovementModeDgbStrForImgui();

	void printUseKeyState();
	void PrintIdPlayerInfo();
	void printChangedIdPlayerData();
	static std::string MovementModeToString(movementMode_t mode);
	static void print_ChangedMovementMode_t();
	static void set_all_idDeclProp_HealthComponent_pickupEffect_to_zero();
	static void addArgFrom_371DB0_ToVec(__int64 arg);
	static bool isPickUpModel(__int64 idRenderModel);
	static bool isRenderModelNameStartsWith(__int64 idRenderModel_Addr, std::string renderModelNameStr);
	static void printArgsNamesFrom_371DB0();
};

