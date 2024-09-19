#pragma once


#include <Windows.h>
#include <string>
#include "../Config/Config.h"
#include "../MemHelper/MemHelper.h"

enum eventType_t {
	EVENT_GAME = 0,
	EVENT_ACTION = 1,
	EVENT_ANIMEVENT = 2,
	EVENT_FSMEVENT = 3,
	EVENT_NOTICE = 4,
};

struct idEventDef {
	//Offset 0x0,	 size 8
	char* name;
	//Offset 0x8,	 size 8
	char* formatspec;
	//Offset 0x10,	 size 8
	char* argTypes;
	//Offset 0x18,	 size 8
	char* argNames;
	//Offset 0x20,	 size 8
	char* argDefaultValues;
	//Offset 0x28,	 size 4
	int returnType;
	//Offset 0x2C,	 size 4
	int numargs;
	//Offset 0x30,	 size 4
	int numstrings;
	//Offset 0x34,	 size 4
	int eventnum;
	//Offset 0x38,	 size 4
	int flags;
	//Offset 0x3C,	 size 4
	eventType_t type;
	//Offset 0x40,	 size 8
	char* timelineEventGroup;
	//Offset 0x48,	 size 8
	char* comment;
	//Offset 0x50,	 size 8
	idEventDef* noticeEvent;
};



class idEventManager
{
private:
	static std::string m_idEventDefFileName;
	static std::vector<std::string> m_idEventDefStrVec;
	

public:
	static std::string eventTypeToString(eventType_t eventType);
	static std::string getidEventDefToStr(idEventDef* idEventDefPtr);
	static void listAllEventsToFile();

	static std::vector<idEventDef*> getEventsVec();

	static void generateEventNumsEnumFile();

	static void generateEventNumsEnumFileFor_0xcb58c0();

	static std::string getEventNumAsEnumMember(size_t index, idEventDef* eventDefPtr, bool is_0xcb58c0_SpecialCase = false);

	//static std::string getEventNumAsEnumMember(size_t index, idEventDef* eventDefPtr);

};

