#pragma once


#include "../MemHelper/MemHelper.h"
#include "../K_Utils/K_Utils.h"
#include "GeneratedClasses.h"
#include "GeneratedEnums.h"



//! this actually is a 2 bytes val in lib it seems but it makes more sens as an int.
enum cmdGenButton_t : __int32 {
	UB_ATTACK1 = 0,
	UB_ZOOM = 1,
	UB_MELEE = 2,
	UB_USE = 3,
	UB_RELOAD = 4,
	UB_USE_AND_RELOAD = 5,
	UB_SPRINT = 6,
	UB_QGRENADE = 7,
	UB_WEAPONSELECT = 8,
	UB_QGRENADE_AND_WEAPONSELECT = 9,
	UB_WEAP_PREV_EQUIP = 10,
	UB_WEAP_NEXT = 11,
	UB_WEAP_PREV = 12,
	UB_WEAP_FUNC_LEFT = 13,
	UB_WEAP_0 = 14,
	UB_WEAP_1 = 15,
	UB_WEAP_2 = 16,
	UB_WEAP_3 = 17,
	UB_WEAP_4 = 18,
	UB_WEAP_5 = 19,
	UB_WEAP_TOGGLE_UPGRADE_LEFT = 20,
	UB_WEAP_TOGGLE_UPGRADE_RIGHT = 21,
	UB_COVERMODE = 22,
	UB_WALK = 23,
	UB_TOGGLEDW = 24,
	UB_INVENTORY = 25,
	UB_MOVEUP = 26,
	UB_MOVEDOWN = 27,
	UB_HINT = 28,
	UB_MOVELEFT = 48,
	UB_MOVERIGHT = 49,
	UB_MOVEFORWARD = 50,
	UB_MOVEBACK = 51,
	UB_LOOKUP = 52,
	UB_LOOKDOWN = 53,
	UB_LOOKLEFT = 54,
	UB_LOOKRIGHT = 55,
	UB_NONE = 56,
	UB_MAX = 57,
};


enum keyNum_t {
	K_NONE = 0,
	K_ESCAPE = 1,
	K_1 = 2,
	K_2 = 3,
	K_3 = 4,
	K_4 = 5,
	K_5 = 6,
	K_6 = 7,
	K_7 = 8,
	K_8 = 9,
	K_9 = 10,
	K_0 = 11,
	K_MINUS = 12,
	K_EQUALS = 13,
	K_BACKSPACE = 14,
	K_TAB = 15,
	K_Q = 16,
	K_W = 17,
	K_E = 18,
	K_R = 19,
	K_T = 20,
	K_Y = 21,
	K_U = 22,
	K_I = 23,
	K_O = 24,
	K_P = 25,
	K_LBRACKET = 26,
	K_RBRACKET = 27,
	K_ENTER = 28,
	K_LCTRL = 29,
	K_A = 30,
	K_S = 31,
	K_D = 32,
	K_F = 33,
	K_G = 34,
	K_H = 35,
	K_J = 36,
	K_K = 37,
	K_L = 38,
	K_SEMICOLON = 39,
	K_APOSTROPHE = 40,
	K_GRAVE = 41,
	K_LSHIFT = 42,
	K_BACKSLASH = 43,
	K_Z = 44,
	K_X = 45,
	K_C = 46,
	K_V = 47,
	K_B = 48,
	K_N = 49,
	K_M = 50,
	K_COMMA = 51,
	K_PERIOD = 52,
	K_SLASH = 53,
	K_RSHIFT = 54,
	K_KP_STAR = 55,
	K_LALT = 56,
	K_SPACE = 57,
	K_CAPSLOCK = 58,
	K_F1 = 59,
	K_F2 = 60,
	K_F3 = 61,
	K_F4 = 62,
	K_F5 = 63,
	K_F6 = 64,
	K_F7 = 65,
	K_F8 = 66,
	K_F9 = 67,
	K_F10 = 68,
	K_NUMLOCK = 69,
	K_SCROLL = 70,
	K_KP_7 = 71,
	K_KP_8 = 72,
	K_KP_9 = 73,
	K_KP_MINUS = 74,
	K_KP_4 = 75,
	K_KP_5 = 76,
	K_KP_6 = 77,
	K_KP_PLUS = 78,
	K_KP_1 = 79,
	K_KP_2 = 80,
	K_KP_3 = 81,
	K_KP_0 = 82,
	K_KP_DOT = 83,
	K_F11 = 87,
	K_F12 = 88,
	K_F13 = 100,
	K_F14 = 101,
	K_F15 = 102,
	K_KANA = 112,
	K_CONVERT = 121,
	K_NOCONVERT = 123,
	K_YEN = 125,
	K_KP_EQUALS = 141,
	K_CIRCUMFLEX = 144,
	K_AT = 145,
	K_COLON = 146,
	K_UNDERLINE = 147,
	K_KANJI = 148,
	K_STOP = 149,
	K_AX = 150,
	K_UNLABELED = 151,
	K_KP_ENTER = 156,
	K_RCTRL = 157,
	K_KP_COMMA = 179,
	K_KP_SLASH = 181,
	K_PRINTSCREEN = 183,
	K_RALT = 184,
	K_PAUSE = 197,
	K_HOME = 199,
	K_UPARROW = 200,
	K_PGUP = 201,
	K_LEFTARROW = 203,
	K_RIGHTARROW = 205,
	K_END = 207,
	K_DOWNARROW = 208,
	K_PGDN = 209,
	K_INS = 210,
	K_DEL = 211,
	K_LWIN = 219,
	K_RWIN = 220,
	K_APPS = 221,
	K_POWER = 222,
	K_SLEEP = 223,
	K_JOY1 = 256,
	K_JOY_A = 256,
	K_JOY2 = 257,
	K_JOY_B = 257,
	K_JOY3 = 258,
	K_JOY_X = 258,
	K_JOY4 = 259,
	K_JOY_Y = 259,
	K_JOY5 = 260,
	K_JOY_LB = 260,
	K_JOY6 = 261,
	K_JOY_RB = 261,
	K_JOY7 = 262,
	K_JOY_LS = 262,
	K_JOY8 = 263,
	K_JOY_RS = 263,
	K_JOY9 = 264,
	K_JOY_START = 264,
	K_JOY10 = 265,
	K_JOY_BACK = 265,
	K_JOY11 = 266,
	K_JOY12 = 267,
	K_JOY13 = 268,
	K_JOY14 = 269,
	K_JOY15 = 270,
	K_JOY16 = 271,
	K_JOY_STICK1_UP = 272,
	K_JOY_STICK1_DOWN = 273,
	K_JOY_STICK1_LEFT = 274,
	K_JOY_STICK1_RIGHT = 275,
	K_JOY_STICK2_UP = 276,
	K_JOY_STICK2_DOWN = 277,
	K_JOY_STICK2_LEFT = 278,
	K_JOY_STICK2_RIGHT = 279,
	K_JOY_TRIGGER1 = 280,
	K_JOY_TRIGGER2 = 281,
	K_JOY_DPAD_UP = 282,
	K_JOY_DPAD_DOWN = 283,
	K_JOY_DPAD_LEFT = 284,
	K_JOY_DPAD_RIGHT = 285,
	K_MOUSE1 = 286,
	K_MOUSE2 = 287,
	K_MOUSE3 = 288,
	K_MOUSE4 = 289,
	K_MOUSE5 = 290,
	K_MOUSE6 = 291,
	K_MOUSE7 = 292,
	K_MOUSE8 = 293,
	K_MWHEELDOWN = 294,
	K_MWHEELUP = 295,
	K_LAST_KEY = 296
};


//! created in reclass with 
//#pragma pack(push, 1) // making sure no padding is added by compiler
class ButtonInfo_K
{
public:
	int64_t gap_0; //0x0000
	int64_t idStrPtr; //0x0008
	const char* ActionNameStr; //0x0010
	int32_t Unknown; //0x0018
	char pad_001C[20]; //0x001C
	int32_t N0000091D; //0x0030
	char pad_0034[4]; //0x0034
	cmdGenButton_t cmdGenButtonVal; //0x0038
	cmdGenButton_t UB_NONE_ButtonVal; //0x003C	
}; 
//#pragma pack(pop) // Restore default packing alignment




//class usercmd_t
//{
//public:
//	uint64_t gameTime; //0x0000
//	bool fromBot; //0x0008
//	bool inhibited; //0x0009
//	char pad_000A[2]; //0x000A
//	int32_t buttons; //0x000C
//	int8_t forwardmove; //0x0010
//	int8_t forwardmoveSec; //0x0011
//	int8_t rightmove; //0x0012
//	int8_t rightmoveSec; //0x0013
//	int8_t upmove; //0x0014
//	char pad_0015[110]; //0x0015
//}; //? not complete btw



//enum usercmdButton_t {
//	BUTTON_ATTACK1 = 1,
//	BUTTON_ZOOM = 2,
//	BUTTON_MELEE = 4,
//	BUTTON_USE = 8,
//	BUTTON_RELOAD = 16,
//	BUTTON_USE_AND_RELOAD = 32,
//	BUTTON_QGRENADE = 128,
//	BUTTON_WPNSEL = 256,
//	BUTTON_QGRENADE_AND_WPNSEL = 512,
//	BUTTON_SPRINT = 64,
//	BUTTON_WEAP_PREV_EQUIP = 1024,
//	BUTTON_WEAP_NEXT = 2048,
//	BUTTON_WEAP_PREV = 4096,
//	BUTTON_WEAP_FUNC_LEFT = 8192,
//	BUTTON_WEAP_0 = 16384,
//	BUTTON_WEAP_1 = 32768,
//	BUTTON_WEAP_2 = 65536,
//	BUTTON_WEAP_3 = 131072,
//	BUTTON_WEAP_4 = 262144,
//	BUTTON_WEAP_5 = 524288,
//	BUTTON_WEAP_TOGGLE_UPGRADE_LEFT = 1048576,
//	BUTTON_WEAP_TOGGLE_UPGRADE_RIGHT = 2097152,
//	BUTTON_COVERMODE = 4194304,
//	BUTTON_WALK = 8388608,
//	BUTTON_TOGGLEDW = 16777216,
//	BUTTON_INVENTORY = 33554432,
//	BUTTON_MOVEUP = 67108864,
//	BUTTON_MOVEDOWN = 134217728,
//	BUTTON_HINT = 268435456,
//	BUTTON_ANY = -1
//};







class idUsercmdGenLocalManager
{
private:

	//static __int64 m_idUsercmdGenLocal;

	//static usercmd_t* usercmd_t_Static;

	static unsigned int m_lastA2In_idKeyboardSmth_AE72A0;

	static __int64 m_sendKeyFuncAddr;

	static keyNum_t m_current_use_keyNum;

	typedef __int64(__fastcall* idUsercmdGenLocalSmth_t)(__int64 idUsercmdGenLocal_a1, unsigned int a2, int keyNum_a3, char isDown_a4);

public:

	//static void acquireIdUsercmdGenLocal(__int64 IdUsercmdGenLocal);

	//static bool acquireUsercmdStatic(__int64 usercmd_t_StaticPtr);

	static void sendFakeUseKeyPressAndRelase(__int64 idUsercmdGenLocal_a1, unsigned int a2, bool isKeyDown);

	static void sendFakeKeyPress(__int64 idUsercmdGenLocal_a1, keyNum_t keyNum, unsigned int a2, bool isKeyDown);


	static void sendFakeZoomKeyPress(bool isKeyDown);
	//static void updateLastFakeKeyPressAndRelease();

	static std::string debugGetLastA2InidKeyboardSmth_AE72A0Str();

	static void debugUpdate(unsigned int lastA2In_idKeyboardSmth_AE72A0);

	static std::string getCmdGenButtonAsStr(cmdGenButton_t input);

	static std::string getkeyNum_tAsStr(keyNum_t keyNum);

	static __int64 getBtnInfoFor(keyNum_t keyNum);

	static cmdGenButton_t getCmdGenButtonBoundTo(keyNum_t keyNum);

	static keyNum_t getUseActionKeyNum();

	static cmdGenButton_t getUseKeyGenButton();

	static void updateCurrentUseBtnKeyNum();

	static bool IsKeyPressed(usercmdButton_t button);

	static void SetButtonState(usercmdButton_t button, bool state);

	static void SetButtonState(usercmd_t* cmd_tPtr, usercmdButton_t button, bool state);

};

