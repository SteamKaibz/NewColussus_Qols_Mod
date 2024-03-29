#pragma once
#include <string>
#include "idLib.h"
#include "../K_Utils/K_Utils.h"
#include "GeneratedClasses.h"

//class idResourceManager;

//! a custom made struct check 'Menu Structure' section of Reminder file for more info
struct refString_k {
	int refInt;
	char* refString; //! like #str_menu_video_texture_filtering_4
	char* localString; //! like Anisotropic 16x
	char pad_end[8];
};

typedef idResourceList* (__fastcall* idResourceList__ForClassName_ABBE60)(const char* className_a1);

//! this is used a lot in the game's code, and could be useful to find decl which are not in the level potentially.
typedef __int64(__fastcall* DeclInfo_FindWithInheritanceFp)(
	__int64 a1,
	__int64 a2,
	int a3,
	int a4);


class idResourceManager
{
private:

	static idResourceList__ForClassName_ABBE60 m_getResListForClsNameFp;

	static idResourceList* getResourceListPtrForClsName(std::string clsName);

	static const __int64 m_labelsListStartOffset;

	static const char* m_MenuBtnModText;
	static const char* m_MenuBtnModHelpText;

	static const char* m_MenuBtnDevRefStr;
	static const char* m_MenuBtnDevHelpStr;


public:

	//? damn templates.
	/*template <typename T>
	static std::string getDeclName(T* idDeclDerivedPtr);*/

	static bool isDevStringOverwriteAttempt;




	static std::string getDeclName(idResource* resPtr);
	
	static bool acquireGetResListForClsNameFp(__int64 faddr);

	static std::vector<idResource*> getResPtrsVecForClsName(std::string clsName);

	static idResource* getDeclByName(std::string clsName, std::string declName);


	static __int64 getDevLoadOutResource();


	static void debugLogResourceListForClsName(std::string clsName);

	static void Log_idDeclRenderParmList();		

	static void debugListRenderParmsNamesAndValues(bool onlyShowEditables );


	static void debugListReferenceStringInfo(const char* searchStr);

	static void overwriteDevLabelsWithModRefs();

	static const char* getLocalizedStrPtrForRef(const char* refStr);

	//static std::vector<std::string> getResourceListDataStrForClsName(std::string clsName);

};

