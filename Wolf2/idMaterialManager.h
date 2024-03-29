#pragma once
#include <string>
#include "../MemHelper/MemHelper.h"
#include "idLib.h"
#include "idCvarManager.h"


//? don't forget m_testIndex might not be -1


struct MaterialBitFieldStruct {
    bool materialCastsShadows : 1;
    bool materialIsTwoSided : 1;
    bool materialIsMixedUnique : 1;
    bool materialIsTransparencySorted : 1;
    bool materialUsesTransSortAtlas : 1;
    bool materialUsesDecalAtlas : 1;
    bool materialAllowsDecals : 1;
    bool materialHasMergeableBlendedPass : 1;
    bool skipSurfaceInfo : 1;
    bool materialHasClipSpheres : 1;
    bool materialIsWorldGuiSurface : 1;
    bool materialIsSpecialMissing : 1;
    bool materialMultipass : 1;
    bool materialIsSky : 1;
    bool materialIsFakeSky : 1;
    bool materialUsesVirtualMapping : 1;
    bool materialUsesDeathFade : 1;
    bool materialUsesRefraction : 1;
    bool materialIsGrass : 1;
    bool materialIsFoliage : 1;
    bool materialIsWindAnimated : 1;
    bool materialHasPurgedDecalImages : 1;
    bool materialIsEmissive : 1;
    bool materialHasLayerMask : 1;
    bool materialIsLightMaterial : 1;
    bool materialHas2dLightFalloff : 1;
    bool materialsdMergeable : 1;
    bool materialIsTransient : 1;
    bool materialAllowLOD : 1;
    bool materialIsScreenParticle : 1;
    bool materialIsHair : 1;
    bool materialCanBeFrustumCulled : 1;
};


class idMaterialManager
{
private:
	static const __int64 m_idMaterialResourceListOffset;
	static std::string m_idMaterialResourceListTypeName;
	static int m_testIndex;

    //! priority materials list
    //static std::vector<std::string> m_spotligtShadowCastingFallOffMaterialsStrsVec;


public:

    //static __int64 getCurrentMapHeadLightMaterialPtr(std::string ligthMtrName);

    static std::vector<std::string> getCurrentMapSpotLightMaterialNames();

    static __int64 getCurrentMapSpotLightMaterialPtr();

    static void debugGetLightMaterialVec();

	static idList* getMaterialsIdList();

	static void showMaterial(int index, idList* idListPtr);

	static void testMaterialNext();
	static void testMaterialPrev();


};

