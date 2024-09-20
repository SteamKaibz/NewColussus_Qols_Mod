#pragma once
#include "idLib.h"
#include "idColor.h"
#include "GeneratedEnums.h"



//? read Types Generation section to understand how all this work


//! not using this atm but keeping it just in case
//! from https://www.youtube.com/watch?v=vQb21RM9-5M&list=PLt9cUwGw6CYHYGsDbI9QnHIJ9q67jzlzL&index=8
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}


//#pragma pack(push, 1) // making sure no padding is added by compiler



//? manually created, offsets are correct.
struct idResourceList {
	char gap_0[8];
	//Offset 0x8,	 size 8
	char* resourceTypeName;
	//Offset 0x10,	 size 8
	char* resourceClassName;
	//Offset 0x18,	 size 8
	idResourceList* nextResourceList;
	//Offset 0x20,	 size 32
	idList resourceList;
	//Offset 0x40,	 size 40
	idHashIndex resourceIDHash;
	//Offset 0x68,	 size 4
	int reloadCount;
};



class idResource {
public:
	char pad_0[8]; // offset: 0h (0d) size: 8
	idAtomicString name; // offset: 8h (8d)  size: 8
	idResourceList* resourceListPtr; // offset: 10h (16d)  size: 8
	char pad_24[32]; // offset: 18h (24d) size: 32
	unsigned long long resourceID; // offset: 38h (56d)  size: 8
	char pad_End[16]; // offset: 40h (64d) size: 16
}; // size: 80




// idMaterial : idDecl : idResource
class idMaterial {
public:
	char pad_0[8]; // offset: 0h (0d) size: 8
	idAtomicString name; // offset: 8h (8d)  size: 8
	char pad_16[1608]; //! making the size correct manually.
	//char pad_0[1620]; // offset: 0h (0d) size: 1620
	//bool ownsMaterialIndex; // offset: 654h (1620d)  size: 1
	//char pad_End[3]; // offset: 655h (1621d) size: 3

	/*const char* getName() {
		return (const char*)((char*)this + 0x8);
	}*/


}; // size: 1624



//struct idMaterial_K {
//	char gap_0[8];
//	//Offset 0x8,	 size 8
//	idAtomicString name;
//	//Offset 0x10,	 size 8
//	idResourceList* resourceListPtr;
//	//Offset 0x18,	 size 8
//	char* resourceError;
//	//Offset 0x20,	 size 8
//	void* idResourceStorage_container;
//	//Offset 0x28,	 size 8
//	unsigned long long generateHash;
//	//Offset 0x30,	 size 4
//	int idResourceVariation_variation;
//	char padding_34[4]; // manual allign
//	//Offset 0x38,	 size 8
//	unsigned long long resourceID;
//};


class idSWFSpriteInstance {
public:
	char pad_0[8]; // offset: 0h (0d) size: 8
	int references; // offset: 8h (8d)  size: 4
	char pad_12[4]; // offset: Ch (12d) size: 4
	idDeduplicatedString name; // offset: 10h (16d)  size: 8
	int fullPathHash; // offset: 18h (24d)  size: 4
	char pad_28[44]; // offset: 1Ch (28d) size: 44
	spriteAlignmentType_t alignmentType; // offset: 48h (72d)  size: 4
	char pad_76[48]; // offset: 4Ch (76d) size: 48
	float xOffset; // offset: 7Ch (124d)  size: 4
	float yOffset; // offset: 80h (128d)  size: 4
	float xOriginal; // offset: 84h (132d)  size: 4
	float yOriginal; // offset: 88h (136d)  size: 4
	char pad_140[156]; // offset: 8Ch (140d) size: 156
	swfRect_t bounds; // offset: 128h (296d)  size: 16
	char pad_End[40]; // offset: 138h (312d) size: 40
}; // size: 352



class idSWFTextInstance {
public:
	char pad_0[8]; // offset: 0h (0d) size: 8
	int fullPathHash; // offset: 8h (8d)  size: 4
	char pad_12[28]; // offset: Ch (12d) size: 28
	idSWFSpriteInstance* parent; // offset: 28h (40d)  size: 8
	char pad_48[8]; // offset: 30h (48d) size: 8
	idStr text; // offset: 38h (56d)  size: 48
	char pad_104[96]; // offset: 68h (104d) size: 96
	swfColorRGBA_t color; // offset: C8h (200d)  size: 4
	char pad_End[644]; // offset: CCh (204d) size: 644
}; // size: 848



struct idSWFDictionaryEntry {
	//Offset 0x0,	 size 4
	swfDictType_t type;
	int gap_4;
	//Offset 0x8,	 size 8
	void* idMaterial_material;
	//Offset 0x10,	 size 8
	void* idSWFShape_shape;
	//Offset 0x18,	 size 8
	void*  idSWFSprite_sprite;
	//Offset 0x20,	 size 8
	void* idSWFFont_font;
	//Offset 0x28,	 size 8
	void* idSWFText_text;
	//Offset 0x30,	 size 8
	void* idSWFEditText_edittext;
	//Offset 0x38,	 size 8
	idVec2i imageSize;
	//Offset 0x40,	 size 8
	idVec2i imageAtlasOffset;
	//Offset 0x48,	 size 16
	idVec4 channelScale;
};// size is 88 i think...




class idSWF {
public:
	char pad_0[368]; // offset: 0h (0d) size: 368
	idAtomicString filename; // offset: 170h (368d)  size: 8
	char pad_376[328]; // offset: 178h (376d) size: 328
	float frameWidth; // offset: 2C0h (704d)  size: 4
	float frameHeight; // offset: 2C4h (708d)  size: 4
	char pad_712[8]; // offset: 2C8h (712d) size: 8
	float swfScale; // offset: 2D0h (720d)  size: 4
	char pad_724[6796]; // offset: 2D4h (724d) size: 6796
	// idList < idSWFDictionaryEntry , TAG_SWF , false >
	idList dictionary; // offset: 1D60h (7520d)  size: 32
	char pad_End[4328]; // offset: 1D80h (7552d) size: 4328
}; // size: 11880






//class idLight
//{//! from reclass but with some tweaks, we'll hopefull have our class generator working by the time the mod release...
//public:
//	char pad_0000[8]; //0x0000
//	int32_t objectNumber; //0x0008
//	int32_t fetchCount; //0x000C
//	char pad_0010[24]; //0x0010
//	char* name; //0x0028
//	char pad_0030[2136]; //0x0030
//	float Intensity; //0x0888
//	char pad_088C[4]; //0x088C
//	void* lightMaterial; //0x0890
//	lightType_t lightType; //0x0898
//	float lightRadiusX; //0x089C
//	float lightRadiusY; //0x08A0
//	float lightRadiusZ; //0x08A4
//	float lightCenterX; //0x08A8
//	float lightCenterY; //0x08AC
//	float lightCenterZ; //0x08B0
//	int32_t idSpotLightRef; //0x08B4
//	char pad_08B8[168]; //0x08B8
//	int32_t N0000017F; //0x0960
//	int8_t N00000B0F; //0x0964
//	bool N00000B11; //0x0965
//	bool N00000B45; //0x0966
//	bool allowEnvOverride; //0x0967
//	float lightProbeInnerFalloff_1; //0x0968
//	float lightProbeInnerFalloff_2; //0x096C
//	float lightProbeInnerFalloff_3; //0x0970
//	float lightProbeInnerFalloff_4; //0x0974
//	float lightShadowSmoothness; //0x0978
//	float lightShadowLeakClamp; //0x097C
//	char pad_0980[40]; //0x0980
//	float shadowMipBias; //0x09A8
//	int32_t shadowResolutionQuality; //0x09AC
//	int32_t shadowFlags; //0x09B0
//	int32_t shadowRate; //0x09B4
//	bool castShadows; //0x09B8
//	bool radiosityShadows; //0x09B9
//	bool backFaceShadows; //0x09BA
//	char pad_09BB[1]; //0x09BB
//	int32_t advancedLightDataStruct; //0x09BC
//	int32_t clippingType; //0x09C0
//	char pad_09C4[68]; //0x09C4
//	int32_t lightGroupID; //0x0A08
//	int32_t particleLightEffect; //0x0A0C
//	float particleLightScale; //0x0A10
//	float staticLightMapScale; //0x0A14
//	float lightGenAreaScale; //0x0A18
//	bool staticLight; //0x0A1C
//	bool staticLightBakeSpecular; //0x0A1D
//	char pad_0A1E[2]; //0x0A1E
//	float dynamicLightSpecularScale; //0x0A20
//	bool contributesToLightProbeGen; //0x0A24
//	bool dynamicOnly; //0x0A25
//	bool startOff; //0x0A26
//	bool flipFadeVisibility; //0x0A27
//	bool stationary; //0x0A28
//	bool N00000B2D; //0x0A29
//	char pad_0A2A[2]; //0x0A2A
//	float maxVisibleRange; //0x0A2C
//	float fadeVisibilityOver; //0x0A30
//	float maxShadowVisibleRange; //0x0A34
//	char pad_0A38[32]; //0x0A38
//	float fadeFromR; //0x0A58
//	float fadeFromG; //0x0A5C
//	float fadeFromB; //0x0A60
//	float fadeFromA; //0x0A64
//	float fadeToR; //0x0A68
//	float fadeToG; //0x0A6C
//	float fadeToB; //0x0A70
//	float fadeToA; //0x0A74
//	class N00000BD1* fadeTablePtr; //0x0A78
//	float originalColorR; //0x0A80
//	float originalColorG; //0x0A84
//	float originalColorB; //0x0A88
//	float originalColorA; //0x0A8C
//	char pad_0A90[16]; //0x0A90
//	uint64_t fadeStart; //0x0AA0
//	uint64_t fadeEnd; //0x0AA8
//	int32_t N000001A8; //0x0AB0
//	bool hasColorCurves; //0x0AB4
//	char pad_0AB5[1491]; //0x0AB5
//}; //Size: 0x1088
//





class idSpotLight
{
public:
	int32_t N00000AA6; //0x0000
	idVec3 lightTarget; //0x0004
	idVec3 lightRight; //0x0010
	idVec3 lightUp; //0x001C
	idVec3 lightStart; //0x0028
	idVec3 lightEnd; //0x0034
	float lightConeLength; //0x0040
	float lightConeSize; //0x0044
	float lightWidthRatio; //0x0048
	float lightHeightRatio; //0x004C
	//? keep this mistake that made us loose 3 hours as a reminder as to why we need a better system:
	//char pad_0050[1096]; //0x0050
}; //Size: 0x0498



//? this used to have a wrong total size, but i went back in reclass, selected all the bytes after AA and ctrl+click selected them and pressed del to delete them and then, i had the correct size.
class idDeclRenderParm
{
public:
	char pad_0000[8]; //0x0000
	char* name; //0x0008
	char pad_0010[8]; //0x0010
	char* resourceError; //0x0018
	class N0000027D* container; //0x0020
	char pad_0028[72]; //0x0028
	float declaredValue; //0x0070
	float declaredValue2; //0x0074
	float declaredValue3; //0x0078
	float declaredValue4; //0x007C
	int32_t parmIndex; //0x0080
	int32_t parmType; //0x0084
	int32_t parmDataType; //0x0088
	int32_t creator; //0x008C
	int32_t edit; //0x0090
	int32_t setFrequency; //0x0094
	int32_t parmScope; //0x0098
	float editRange1; //0x009C
	float editRange2; //0x00A0
	uint32_t srgbaMask; //0x00A4
	bool cubeFilterTexture; //0x00A8
	bool dynamicOffset; //0x00A9
}; //Size: 0x00AA





//! reclass:
//class idRenderLightParms
//{
//public:
//	char pad_0000[48]; //0x0000
//	int32_t lightGroupID; //0x0030
//	char pad_0034[20]; //0x0034
//	int32_t lightType; //0x0048
//	int32_t particleLightEffect; //0x004C
//	float particleLightScale; //0x0050
//	float staticLightMapScale; //0x0054
//	float dynamicLightSpecularScale; //0x0058
//	uint32_t N00000497; //0x005C
//	char pad_0060[48]; //0x0060
//	float lightRadiusX; //0x0090
//	float lightRadiusY; //0x0094
//	float lightRadiusZ; //0x0098
//	float lightCenterX; //0x009C
//	float lightCenterY; //0x00A0
//	float lightCenterZ; //0x00A4
//	float targetX; //0x00A8
//	float targetY; //0x00AC
//	float targetZ; //0x00B0
//	float rightX; //0x00B4
//	float rightY; //0x00B8
//	float rightZ; //0x00BC
//	float upX; //0x00C0
//	float upY; //0x00C4
//	float upZ; //0x00C8
//	float startX; //0x00CC
//	float startY; //0x00D0
//	float startZ; //0x00D4
//	float endX; //0x00D8
//	float endY; //0x00DC
//	float endZ; //0x00E0
//	int32_t lightArea_t; //0x00E4
//	float maxVisibleRange; //0x00E8
//	float fadeVisibilityOver; //0x00EC
//	float N00000397; //0x00F0
//	float N000004BB; //0x00F4
//	float N00000398; //0x00F8
//	float N000004BE; //0x00FC
//	float N00000399; //0x0100
//	float N000004C1; //0x0104
//	float N0000039A; //0x0108
//	float N000004C4; //0x010C
//	float N0000039B; //0x0110
//	float N000004C7; //0x0114
//	float N0000039C; //0x0118
//	float N000004CA; //0x011C
//	float N0000039D; //0x0120
//	float N000004CD; //0x0124
//	float N0000039E; //0x0128
//	float N000004D0; //0x012C
//	int32_t analyticalFlags; //0x0130
//	float N000004D3; //0x0134
//	float N000003A0; //0x0138
//	float N000004D6; //0x013C
//	float N000003A1; //0x0140
//	char pad_0144[1852]; //0x0144
//}; //Size: 0x0880

//? dangerious to directly modify those vals, i got crash, you can check crash log in reminder file.
class idRenderLightParms {
public:
	char pad_0[72]; // offset: 0h (0d) size: 72
	lightType_t lightType; // offset: 48h (72d)  size: 4
	char pad_76[12]; // offset: 4Ch (76d) size: 12
	float dynamicLightSpecularScale; // offset: 58h (88d)  size: 4
	char pad_92[76]; // offset: 5Ch (92d) size: 76
	idVec3 target; // offset: A8h (168d)  size: 12
	char pad_180[24]; // offset: B4h (180d) size: 24
	idVec3 start; // offset: CCh (204d)  size: 12
	idVec3 end; // offset: D8h (216d)  size: 12
	char pad_End[116]; // offset: E4h (228d) size: 116
}; // size: 344




class idRenderLight {
public:
	char pad_0[24]; // offset: 0h (0d) size: 24
	idRenderLightParms g; // offset: 18h (24d)  size: 344
	char pad_End[632]; // offset: 170h (368d) size: 632
}; // size: 1000



//class advancedLightData
//{
//public:
//	bool clipPlanesEnabled; //0x0000
//	bool N00000DFF; //0x0001
//	char pad_0002[2]; //0x0002
//	int32_t clippingType; //0x0004
//	float clipPlanePositionX; //0x0008
//	float clipPlanePositionY; //0x000C
//	float clipPlanePositionZ; //0x0010
//	float clipPlaneNormal; //0x0014
//	float N00000D69; //0x0018
//	float N00000E0C; //0x001C
//	float clipBoxPosition; //0x0020
//	float N00000E0F; //0x0024
//	float N00000D6B; //0x0028
//	float clipBoxSize; //0x002C
//	float N00000D6C; //0x0030
//	float N00000E15; //0x0034
//	bool clipPlaneLocked; //0x0038
//	int8_t N00000E18; //0x0039
//	char pad_003A[2]; //0x003A
//	float scatteringMultiplier; //0x003C
//	float falloffMultiplier; //0x0040
//	float toggleFadeTime; //0x0044
//	int32_t lightClass; //0x0048
//	char pad_004C[1092]; //0x004C
//}; //Size: 0x0490




 //idLight : idEntity : idEventReceiver : idManagedClass : idClass
class idLight {
public:
	char pad_0[2168]; // offset: 0h (0d) size: 2168
	idColor lightColor; // offset: 878h (2168d)  size: 16
	float lightIntensity; // offset: 888h (2184d)  size: 4
	char pad_2188[4]; // offset: 88Ch (2188d) size: 4
	void* lightMaterial; // offset: 890h (2192d)  size: 8
	lightType_t lightType; // offset: 898h (2200d)  size: 4
	char pad_2204[24]; // offset: 89Ch (2204d) size: 24
	idSpotLight spotLight; // offset: 8B4h (2228d)  size: 80
	char pad_2308[290]; // offset: 904h (2308d) size: 290
	bool startOff; // offset: A26h (2598d)  size: 1
	char pad_2599[41]; // offset: A27h (2599d) size: 41
	idRenderLight* renderLight; // offset: A50h (2640d)  size: 8
	char pad_2648[40]; // offset: A58h (2648d) size: 40
	idColor originalColor; // offset: A80h (2688d)  size: 16
	char pad_End[40]; // offset: A90h (2704d) size: 40
}; // size: 2744






// idDeclWeaponReticle : idGameDeclTypeInfo : idDeclTypeInfo : idDecl : idResource
class idDeclWeaponReticle {
public:
	char pad_0[156]; // offset: 0h (0d) size: 156
	float reticleModelScale; // offset: 9Ch (156d)  size: 4
	char pad_End[120]; // offset: A0h (160d) size: 120
}; // size: 280


class idDeclWeapon_zoomInfo_t {
public:
    float zoomedFOV; // offset: 0h (0d)  size: 4
    float sensitivity_scale_controller; // offset: 4h (4d)  size: 4
    float sensitivity_scale_mouse; // offset: 8h (8d)  size: 4
    char pad_End[124]; // offset: Ch (12d) size: 124
}; // size: 136


// idDeclWeapon : idDeclInventory : idGameDeclTypeInfo : idDeclTypeInfo : idDecl : idResource
class idDeclWeapon {
public:
    char pad_0[2304]; // offset: 0h (0d) size: 2304
    idDeclWeapon_zoomInfo_t ironSightZoom; // offset: 900h (2304d)  size: 136
    char pad_2440[96]; // offset: 988h (2440d) size: 96
    float sensitivityWhileFiring; // offset: 9E8h (2536d)  size: 4
    char pad_End[452]; // offset: 9ECh (2540d) size: 452
}; // size: 2992



//class idHudReticleInfo {
//public:
//	char pad_0[8]; // offset: 0h (0d) size: 8
//	idDeclWeaponReticle* decl; // offset: 8h (8d)  size: 8
//	char pad_16[8]; // offset: 10h (16d) size: 8
//	idDeclWeapon* weaponDecl; // offset: 18h (24d)  size: 8
//	char pad_32[68]; // offset: 20h (32d) size: 68
//	float targetIndication; // offset: 64h (100d)  size: 4
//	char pad_End[8]; // offset: 68h (104d) size: 8
//}; // size: 112



struct idHudReticleInfo {
	//Offset 0x0,	 size 8
	idMaterial* iconMaterial;
	//Offset 0x8,	 size 8
	idDeclWeaponReticle* decl;
	//Offset 0x10,	 size 8
	idDeclWeaponReticle* upgradeReticle;
	//Offset 0x18,	 size 8
	idDeclWeapon* weaponDecl;
	//Offset 0x20,	 size 8
	idAtomicString npcName;
	//Offset 0x28,	 size 4
	int flags;
	//Offset 0x2C,	 size 4
	int iconIndex;
	//Offset 0x30,	 size 4
	int entityNum;
	//Offset 0x34,	 size 12
	idVec3 tracePoint;
	//Offset 0x40,	 size 8
	char* text;
	//Offset 0x48,	 size 16
	idColor color;
	//Offset 0x58,	 size 4
	float spread;
	//Offset 0x5C,	 size 4
	float zoomFraction;
	//Offset 0x60,	 size 4
	float chargingFraction;
	//Offset 0x64,	 size 4
	float targetIndication;
	//Offset 0x68,	 size 4
	//? this will be -1 all the time from my tests.
	leanMode_t leanDirIndication; //idEnvironmentAnalyzer::leanMode_t leanDirIndication;
};









struct idHudHealthIndicatorInfo {
	//Offset 0x0,	 size 4
	float health;
	//Offset 0x4,	 size 4
	float armor;
	//Offset 0x8,	 size 4
	int armorMax;
	//Offset 0xC,	 size 4
	int healthMax;
	//Offset 0x10,	 size 4
	float barAmount;
	//Offset 0x14,	 size 4
	float barMax;
	//Offset 0x18,	 size 1
	byte playerHealth;
	//Offset 0x19,	 size 1
	byte show;
	//Offset 0x1A,	 size 1
	byte instant;
	//Offset 0x1B,	 size 1
	byte healthOvercharge; // afaik this is one whatever your health is.
	//Offset 0x1C,	 size 1
	byte armorOvercharge;
	//Offset 0x1D,	 size 1
	byte envDamageTrigger;
	//Offset 0x20,	 size 4
	int healthMode;
	//Offset 0x24,	 size 4
	int iconDmgSet;
	//Offset 0x28,	 size 4
	int stackType;
};


//struct weaponAmmoInfo_ammoInfo_t {
//	//Offset 0x0,	 size 4
//	int flags;
//	//Offset 0x4,	 size 4
//	int clipCount;
//	//Offset 0x8,	 size 4
//	int pocketCount;
//	//Offset 0xC,	 size 4
//	int maxAmmoCount;
//	//Offset 0x10,	 size 4
//	float maxChargeCount;
//	//Offset 0x14,	 size 4
//	float chargeCount;
//	//Offset 0x18,	 size 4
//	float chargeDurationMs;
//	//Offset 0x1C,	 size 4
//	float activeCharge;
//	//Offset 0x20,	 size 48
//	idStr ammoType;
//	//Offset 0x50,	 size 8
//	void* idMaterial_ammoIcon;
//	//Offset 0x58,	 size 8
//	void* idMaterial_upgradeIcon;
//};


//? keep this cause it made my life shit, this is a struct we defined in reclass, problem is if you look at the size it's wrong so as a result it messed all the other offset in an class it was used in. so 
//class idHudWeaponAmmoStatusInfo
//{
//public:
//	weaponAmmoFlags_t flags; //0x0000
//	int32_t clipCount; //0x0004
//	int32_t pocketCount; //0x0008
//	int32_t maxAmmoCount; //0x000C
//	float maxChargeCount; //0x0010
//	float chargeCount; //0x0014
//	float chargeDurationMs; //0x0018
//	float activeCharge; //0x001C
//	char pad_0020[368]; //0x0020
//	bool show; //0x0190
//	bool subdued; //0x0191
//	bool isReloading; //0x0192
//	char pad_0193[3821]; //0x0193
//}; //Size: 0x1080


class idHudWeaponAmmoStatusInfo {
public:
	char weaponAmmoInfo_t_info[400]; // offset: 0h (0d)  size: 400
	char pad_End[8]; // offset: 190h (400d) size: 8

	weaponAmmoFlags_t getFlags() {
		return *(weaponAmmoFlags_t*)weaponAmmoInfo_t_info;
	}

}; // size: 408






struct idHudInfo_Cinematic {
	//Offset 0x0,	 size 1
	bool show;
	//Offset 0x1,	 size 1
	bool fadeIn;
	//Offset 0x8,	 size 8
	idMaterial* cinematic;
	//Offset 0x10,	 size 32
	char cinematicTarget[32];  //idManagedClassPtr < idTarget_Cinematic > cinematicTarget;
};


struct idHudInteractionInfo {
	//Offset 0x0,	 size 32
	char icons[32]; // < idHudInteractionInfo::icon_t, TAG_IDLIST, false > icons;
	//Offset 0x20,	 size 4
	interactIconSet_t state;
};


//struct alignas(8) weaponAmmoInfo_t {
//	//Offset 0x0,	 size 192
//	char sldkf[192];// weaponAmmoInfo_t::ammoInfo_t[2] ammoInfo;
//	//Offset 0xC0,	 size 4
//	int flags;
//}; //k: size 0xC4


struct idHudInfo {
	//Offset 0x0,	 size 1448
	char pad_0[1448];	//idHudInfo::playerInfoIndicator_t playerInfoIndicator;
		//Offset 0x5A8,	 size 1
	bool inCombat;
	//Offset 0x5A9,	 size 1
	bool inScope;
	//Offset 0x5AA,	 size 1
	bool isZooming;
	//Offset 0x5AB,	 size 1
	bool fireModePrimary;
	//Offset 0x5AC,	 size 1
	bool isSaving;
	//Offset 0x5AD,	 size 1
	bool blockIcons;
	//Offset 0x5AE,	 size 1
	bool gameIntroActive;
	//Offset 0x5B0,	 size 4
	float playerYaw;
	//Offset 0x5B4,	 size 4
	float playerPitch;
	//Offset 0x5B8,	 size 12
	idVec3 playerPos;
	//Offset 0x5C4,	 size 36
	idMat3 playerAxis;
	//Offset 0x5E8,	 size 408
	idHudWeaponAmmoStatusInfo weaponAmmoStatus;
	//Offset 0x780,	 size 64
	char activeNotification[64]; //idHud_NotificationEvent* [8] activeNotification;
	//Offset 0x7C0,	 size 64
	char activeNotificationSlot[64]; //idHud_NotificationSlot* [8] activeNotificationSlot;
	//Offset 0x800,	 size 8
	void* latestNotification; //idHud_NotificationSlot* latestNotification;
	//Offset 0x808,	 size 224
	char watchItems[224]; //idGrowableList < idVec3, 16, TAG_IDLIST > watchItems;
	//Offset 0x8E8,	 size 72
	char infoLog[72]; // idHudInfo::infoLog_t infoLog;
	//Offset 0x930,	 size 112
	idHudReticleInfo reticle;
	//Offset 0x9A0,	 size 44
	idHudHealthIndicatorInfo healthIndicator;
	//Offset 0x9D0,	 size 216
	char quickItems[216]; //idArray < idHudQuickItem, 9 > quickItems;
	//Offset 0xAA8,	 size 40
	char damageIndicator[40];//  damageIndicator_t damageIndicator;
	//Offset 0xAD0,	 size 48
	idHudInfo_Cinematic fullscreenCinematic;
	//Offset 0xB00,	 size 32
	char scriptHUDImageList[32];//< scriptHUDElement_t, TAG_IDLIST, false > scriptHUDImageList;
	//Offset 0xB20,	 size 40
	char interaction[40];
	//Offset 0xB48,	 size 112
	char commanderInfo[112]; //idHudInfo::commanderInfo_t commanderInfo;
	//Offset 0xBB8,	 size 16
	char radioVoice[16]; //idHudInfo::radioVoice_t radioVoice;
	//Offset 0xBC8,	 size 8
	char pickupLog[8]; //idHudInfo::pickupLog_t* pickupLog;
		//Offset 0xBD0,	 size 8
	char followerManager[8]; //idHudInfo::followerMgr* followerManager;
	//Offset 0xBD8,	 size 1208
	char weaponSelection[1208]; // weaponSelection_t weaponSelection;
	//Offset 0x1090,	 size 40
	char challengeElement[40]; //idHudInfo::challengeElement_t challengeElement;
	//Offset 0x10B8,	 size 4
	int activeTimer;//idTimeMs activeTimer;
	//Offset 0x10BC,	 size 4
	int hudFlags;
	//Offset 0x10C0,	 size 4
	int playerNum;
};



//class idHudInfo {
//public:
//	char pad_0[1449]; // offset: 0h (0d) size: 1449
//	bool inScope; // offset: 5A9h (1449d)  size: 1
//	bool isZooming; // offset: 5AAh (1450d)  size: 1
//	char pad_1451[61]; // offset: 5ABh (1451d) size: 61
//	idHudWeaponAmmoStatusInfo weaponAmmoStatus; // offset: 5E8h (1512d)  size: 408
//	char pad_1920[432]; // offset: 780h (1920d) size: 432
//	idHudReticleInfo reticle; // offset: 930h (2352d)  size: 112
//	idHudHealthIndicatorInfo healthIndicator; // offset: 9A0h (2464d)  size: 44
//	char pad_2508[1776]; // offset: 9CCh (2508d) size: 1776
//	int hudFlags; // offset: 10BCh (4284d)  size: 4
//	char pad_End[8]; // offset: 10C0h (4288d) size: 8
//}; // size: 4296





//? This is the version we had from reclass and it's wrong once again look at the size, 0x0480, this is not right, but we got lucky cause we used nothing in the containing class after this struct, but this is just wrong so let's do it with the other idCrosshairInfo def you can see below this one:
//class idCrosshairInfoTest
//{
//public:
//	int32_t infoFlags; //0x0000
//	int32_t entityNum; //0x0004
//	int32_t activeIcon; //0x0008
//	float hitBeepPercentage; //0x000C
//	int32_t iconSet; //0x0010
//	char pad_0014[60]; //0x0014
//	idMaterial* material; //0x0050
//	int32_t count; //0x0058
//	crosshairInfoIconState_t flags; //0x005C
//	const char* useText; //0x0060
//	const char* help; //0x0068
//	char pad_0070[1040]; //0x0070
//}; //Size: 0x0480


//! this is my own approach use the data from reclass or our generator. but use the size of the class to make sure there is a padding at the end that is correcto make the class the size it should be even if you have to calculate it manually.
class idCrosshairInfo
{
public:
	int32_t infoFlags; //0x0000
	int32_t entityNum; //0x0004
	int32_t activeIcon; //0x0008
	float hitBeepPercentage; //0x000C
	int32_t iconSet; //0x0010
	char pad_0014[60]; //0x0014
	idMaterial* material; //0x0050
	int32_t count; //0x0058
	crosshairInfoIconState_t flags; //0x005C
	const char* useText; //0x0060
	const char* help; //0x0068
	char pad_end[40]; //0x0070
}; //! from our generator size of the cls is: 152 dec (98h)

//class idCrosshairInfo
//{
//public:
//
//	// be sure to put all the offsets you pad this way in a union
//	union
//	{
//		//              Type     Name    Offset
//		DEFINE_MEMBER_N(idMaterial*, material, 0x50);
//	};
//
//};



//class idCrosshairInfo {
//public:
//	//int infoFlags; // offset: 0h (0d)  size: 4
//	char pad_Size[152]; 
//
//	idMaterial* getMaterial() {
//		return *(idMaterial**)((char*)this + 0x50);
//	}
//
//	int getCount() {
//		return *(int*)((char*)this + 0x58);
//	}
//
//	const char* getUseText() {
//		return (const char*)((char*)this + 0x60);
//	}
//
//	crosshairInfoIconState_t getIconInfo() {
//		return *(crosshairInfoIconState_t*)((char*)this + 0x5C);
//	}
//
//}; // size: 152



//! the class name in lib is idFocusTracker
class idFocusTracker_Player {
public:
	char pad_0[192]; // offset: 0h (0d) size: 192
	__int64 focusUsableEntityPtr; // offset: C0h (192d)  size: 32
	char pad_224[128]; // offset: E0h (224d) size: 128
	int focusedEntityFlags; // offset: 160h (352d)  size: 4
	char pad_356[580]; // offset: 164h (356d) size: 580
	idCrosshairInfo crosshairInfo; // offset: 3A8h (936d)  size: 152
	char pad_End[16]; // offset: 440h (1088d) size: 16
}; // size: 1104




class idPlayerHud_Render {
public:
	void* idMenuManager_Hud_MercuryHud_mercMgr; // offset: 0h (0d)  size: 8
	void* idFont_playerHUDFont; // offset: 8h (8d)  size: 8
	char pad_16[4552]; // offset: 10h (16d) size: 4552
	void* idFloatingNumberOverlay_floatingNumberOverlay; // offset: 11D8h (4568d)  size: 8
}; // size: 4576


class localView_t {
public:
	idPlayerHud_Render hudRender; // offset: 0h (0d)  size: 4576
	char pad_End[24]; // offset: 11E0h (4576d) size: 24
}; // size: 4600



class idActor_idActorVolatile {
public:
	char pad_0[1424]; // offset: 0h (0d) size: 1424
	char equipped[480]; // offset: 590h(1424d)  size : 480  idManagedClassPtr < idInventoryItem >[15] equipped;  
	char pad_End[10464]; // offset: 770h (1904d) size: 10464
}; // size: 12368


// idActor : idAnimatedEntity : idEntity : idEventReceiver : idManagedClass : idClass
class idActor {
public:
	char pad_0[5224]; // offset: 0h (0d) size: 5224
	idActor_idActorVolatile actorVolatile; // offset: 1468h (5224d)  size: 12368
}; // size: 17592


class idEnvironmentAnalyzer {
public:
	char pad_0[4884]; // offset: 0h (0d) size: 4884
	unsigned char forceLeanMode; // offset: 1314h (4884d)  size: 1
	char pad_End[51]; // offset: 1315h (4885d) size: 51
}; // size: 4936




class idPlayer_idPlayerConstant {
public:
    char pad_0[72]; // offset: 0h (0d) size: 72
    // idDeclFX*
    void* screenFXDecl; // offset: 48h (72d)  size: 8
    char pad_End[1656]; // offset: 50h (80d) size: 1656
}; // size: 1736


class idPlayer_idPlayerEditable {
public:
    char pad_0[672]; // offset: 0h (0d) size: 672
    playerType_t playerType; // offset: 2A0h (672d)  size: 4
    char pad_End[188]; // offset: 2A4h (676d) size: 188
}; // size: 864







class idPlayer_idPlayerVolatile {
public:
	char pad_0[30]; // offset: 0h (0d) size: 30
	bool headlightIsActive; // offset: 1Eh (30d)  size: 1
	char pad_31[2145]; // offset: 1Fh (31d) size: 2145
	idPlayer_animSysEvents_t prevMoveEvent; // offset: 880h (2176d)  size: 4
	char pad_2180[96]; // offset: 884h (2180d) size: 96
	movementMode_t currentMovementMode; // offset: 8E4h (2276d)  size: 4
	char pad_2280[8112]; // offset: 8E8h (2280d) size: 8112
	// idTypesafeTime < long long , gameTimeUnique_t , 999960 >
	long long showMarkerHintFadeOutTime; // offset: 2898h (10392d)  size: 8
	char pad_10400[776]; // offset: 28A0h (10400d) size: 776
	// idTypesafeTime < int , millisecondUnique_t , 1000 >
	int playerUseTime; // offset: 2BA8h (11176d)  size: 4
	idPlayer_playerUseState_t playerUseState; // offset: 2BACh (11180d)  size: 4
	char pad_11184[19304]; // offset: 2BB0h (11184d) size: 19304
	idHudInfo hudInfo; // offset: 7718h (30488d)  size: 4296
	localView_t localView; // offset: 87E0h (34784d)  size: 4600
	char pad_39384[5968]; // offset: 99D8h (39384d) size: 5968
	idEnvironmentAnalyzer environmentAnalyzer; // offset: B128h (45352d)  size: 4936
	char pad_End[61488]; // offset: C470h (50288d) size: 61488
}; // size: 111776



class idPlayer_idPlayerVolatileUnsaved {
public:
	idLight* headLightptr; // offset: 0h (0d)  size: 32
	char pad_8[24];
	char pad_32[32]; // offset: 20h (32d) size: 32
	char playerProgress[10312]; // offset: 40h (64d)  size: 10312
	char pad_10376[480]; // offset: 2888h (10376d) size: 480
	idFocusTracker_Player focusTracker; // offset: 2A68h (10856d)  size: 1104
	int pauseScreenIndex; // offset: 2EB8h (11960d)  size: 4
	char pad_11964[644]; // offset: 2EBCh (11964d) size: 644
	char screenFXStruct[992]; // offset: 3140h (12608d)  size: 992
	char pad_End[8]; // offset: 3520h (13600d) size: 8
}; // size: 13608



// idPlayer : idActor : idAnimatedEntity : idEntity : idEventReceiver : idManagedClass : idClass
class idPlayer {
public:
    char pad_0[17592]; // offset: 0h (0d) size: 17592
    idPlayer_idPlayerConstant playerConstants; // offset: 44B8h (17592d)  size: 1736
    idPlayer_idPlayerEditable playerEditable; // offset: 4B80h (19328d)  size: 864
    idPlayer_idPlayerVolatile playerVolatile; // offset: 4EE0h (20192d)  size: 111776
    idPlayer_idPlayerVolatileUnsaved playerVolatileUnsaved; // offset: 20380h (131968d)  size: 13608
    char pad_End[3736]; // offset: 238A8h (145576d) size: 3736
	
}; // size: 149312



class usercmd_t {
public:
	char pad_0[12]; // offset: 0h (0d) size: 12
	int buttons; // offset: Ch (12d)  size: 4
	char pad_End[48]; // offset: 10h (16d) size: 48
}; // size: 64


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




class idUCmdTracker {
public:
	usercmd_t prevcmd; // offset: 0h (0d)  size: 64
	usercmd_t usercmd; // offset: 40h (64d)  size: 64
	usercmd_t prevcmdRaw; // offset: 80h (128d)  size: 64
	usercmd_t usercmdRaw; // offset: C0h (192d)  size: 64
	char pad_End[24]; // offset: 100h (256d) size: 24
}; // size: 280


// idPlayerController : idPlayerControllerBase
class idPlayerController {
public:
	char pad_0[12185]; // offset: 0h (0d) size: 12185
	bool useCmdTracker1; // offset: 2F99h (12185d)  size: 1
	char pad_12186[6]; // offset: 2F9Ah (12186d) size: 6
	idUCmdTracker ucmdTracker1; // offset: 2FA0h (12192d)  size: 280
	idUCmdTracker ucmdTracker2; // offset: 30B8h (12472d)  size: 280
	idUCmdTracker rawUCmdTracker; // offset: 31D0h (12752d)  size: 280
}; // size: 13032


// idEntity : idEventReceiver : idManagedClass : idClass
class idEntity {
public:
	char pad_0[784]; // offset: 0h (0d) size: 784
	// idPlayerControllerBase*
	idPlayerController* playerController; // offset: 310h (784d)  size: 8
	char pad_End[1376]; // offset: 318h (792d) size: 1376
}; // size: 2168



//?  read Types Generation section to understand how all this work



//? this makes no sens to me: replacing data by int
//struct idStatBase_statValue_t {
//	//Offset 0x0,	 size 4
//	int i;
//	//Offset 0x0,	 size 4
//	float f;
//};


class idStatBase {
public:
	//idDeclMetric* decl; // offset: 0h (0d)  size: 8
	void* decl;
	//idStatBase_statValue_t sessionValue; // offset: 8h (8d)  size: 4
	int sessionValue;
	//idStatBase_statValue_t aggregatedValue; // offset: Ch (12d)  size: 4
	int aggregatedValue;
}; // size: 16


// idStat : idStatBase
class idStat : public idStatBase {
public:
	//char pad_0[16]; // offset: 0h (0d) size: 16
	int postSerializedSessionValueInt; // offset: 10h (16d)  size: 4
	char pad_End[4]; // offset: 14h (20d) size: 4
}; // size: 24



class idLevelStats {
public:
	int startTime; // offset: 0h (0d)  size: 4
	int endTime; // offset: 4h (4d)  size: 4
	int damageTaken; // offset: 8h (8d)  size: 4
	int itemsTaken; // offset: Ch (12d)  size: 4
	//idStaticList < weaponStats_t, 20, false, TAG_IDLIST > weaponStats; // offset: 10h (16d)  size: 1632
	char weaponStats[1632];
}; // size: 1648


//// idPlayerMetrics : idEventReceiver : idManagedClass : idClass
//class idPlayerMetrics {
//public:
//	char pad_0[40]; // offset: 0h (0d) size: 40
//	//idStaticList < idStat, 420, false, TAG_IDLIST > stats; // offset: 28h (40d)  size: 10112
//	char stats[10112]; 
//	char pad_10152[496]; // offset: 27A8h (10152d) size: 496
//	int killsThisLife; // offset: 2998h (10648d)  size: 4
//	char pad_10652[4]; // offset: 299Ch (10652d) size: 4
//	float kdr; // offset: 29A0h (10656d)  size: 4
//	char pad_10660[4]; // offset: 29A4h (10660d) size: 4
//	bool inGame; // offset: 29A8h (10664d)  size: 1
//	char pad_10665[135]; // offset: 29A9h (10665d) size: 135
//	// idList < weaponQueueEntry_t , TAG_IDLIST , false >
//	idList weaponQueue; // offset: 2A30h (10800d)  size: 32
//	char pad_10832[112]; // offset: 2A50h (10832d) size: 112
//	idLevelStats levelStats; // offset: 2AC0h (10944d)  size: 1648
//	char pad_End[16]; // offset: 3130h (12592d) size: 16
//}; // size: 12608



//// idPlayerMetrics : idEventReceiver : idManagedClass : idClass
class idPlayerMetrics {
public:
	char pad_0[40]; // offset: 0h (0d) size: 40
	char stats[10112];  //idStaticList < idStat, 420, false, TAG_IDLIST > stats; // offset: 28h (40d)  size: 10112
	char pad_10152[496]; // offset: 27A8h (10152d) size: 496
	int killsThisLife; // offset: 2998h (10648d)  size: 4
	char pad_10652[4]; // offset: 299Ch (10652d) size: 4
	float kdr; // offset: 29A0h (10656d)  size: 4
	char pad_10660[4]; // offset: 29A4h (10660d) size: 4
	bool inGame; // offset: 29A8h (10664d)  size: 1
	char pad_10665[135]; // offset: 29A9h (10665d) size: 135
	// idList < weaponQueueEntry_t , TAG_IDLIST , false >
	idList weaponQueue; // offset: 2A30h (10800d)  size: 32
	char pad_10832[112]; // offset: 2A50h (10832d) size: 112
	idLevelStats levelStats; // offset: 2AC0h (10944d)  size: 1648
	char pad_End[16]; // offset: 3130h (12592d) size: 16
}; // size: 12608


// idMetrics : idEventReceiver : idManagedClass : idClass
class idMetrics {
public:
	char pad_0[40]; // offset: 0h (0d) size: 40
	idPlayerMetrics players[12]; // offset: 28h (40d)  size: 151296
	bool gameEnded; // offset: 24F28h (151336d)  size: 1
	char pad_End[7]; // offset: 24F29h (151337d) size: 7
}; // size: 151344



// idGameLocal : idGame
class idGameLocal {
public:
	char pad_0[856064]; // offset: 0h (0d) size: 856064
	void* ImGui; // idImGui* imGUI; offset: D1000h (856064d)  size: 8
	char pad_856072[7432]; // offset: D1008h (856072d) size: 7432
	gameState_t gamestate; // offset: D2D10h (863504d)  size: 4
	char pad_863508[24876]; // offset: D2D14h (863508d) size: 24876
	challengeGameMode_t serializedChallengeMode; // offset: D8E40h (888384d)  size: 4
	char pad_888388[7268]; // offset: D8E44h (888388d) size: 7268
	gameState_t savedStateOnVideo; // offset: DAAA8h (895656d)  size: 4
	char pad_895660[12]; // offset: DAAACh (895660d) size: 12
	idManagedClassPtrBase bindVideo; // idManagedClassPtr < idEventReceiver > binkVideo; // offset: DAAB8h (895672d)  size: 32
	char pad_895704[72480]; // offset: DAAD8h (895704d) size: 72480
	void* itemSelectors[2];//idItemSelector* [2] itemSelectors; // offset: EC5F8h (968184d)  size: 16
	char pad_968200[13096]; // offset: EC608h (968200d) size: 13096
	idMetrics* gameMetrics; // offset: EF930h (981296d)  size: 8
	char pad_981304[475416]; // offset: EF938h (981304d) size: 475416
	bool usingCheatCodes; // offset: 163A50h (1456720d)  size: 1
	char pad_End[79]; // offset: 163A51h (1456721d) size: 79
}; // size: 1456800
