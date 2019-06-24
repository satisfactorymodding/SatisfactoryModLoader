#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Landscape_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class Landscape.ControlPointMeshComponent
// 0x0000 (0x05F0 - 0x05F0)
class UControlPointMeshComponent : public UStaticMeshComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.ControlPointMeshComponent");
		return ptr;
	}

};


// Class Landscape.LandscapeProxy
// 0x0318 (0x0640 - 0x0328)
class ALandscapeProxy : public AActor
{
public:
	class ULandscapeSplinesComponent*                  SplineComponent;                                          // 0x0328(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FGuid                                       LandscapeGuid;                                            // 0x0330(0x0010) (ZeroConstructor, IsPlainOldData)
	struct FIntPoint                                   LandscapeSectionOffset;                                   // 0x0340(0x0008) (ZeroConstructor, IsPlainOldData)
	int                                                MaxLODLevel;                                              // 0x0348(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              LODDistanceFactor;                                        // 0x034C(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	TEnumAsByte<ELandscapeLODFalloff>                  LODFalloff;                                               // 0x0350(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0351(0x0003) MISSED OFFSET
	float                                              ComponentScreenSizeToUseSubSections;                      // 0x0354(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              LOD0DistributionSetting;                                  // 0x0358(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              LODDistributionSetting;                                   // 0x035C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              TessellationComponentScreenSize;                          // 0x0360(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               UseTessellationComponentScreenSizeFalloff;                // 0x0364(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0365(0x0003) MISSED OFFSET
	float                                              TessellationComponentScreenSizeFalloff;                   // 0x0368(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                OccluderGeometryLOD;                                      // 0x036C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                StaticLightingLOD;                                        // 0x0370(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0374(0x0004) MISSED OFFSET
	class UPhysicalMaterial*                           DefaultPhysMaterial;                                      // 0x0378(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              StreamingDistanceMultiplier;                              // 0x0380(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x0384(0x0004) MISSED OFFSET
	class UMaterialInterface*                          LandscapeMaterial;                                        // 0x0388(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          LandscapeHoleMaterial;                                    // 0x0390(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<struct FLandscapeProxyMaterialOverride>     LandscapeMaterialsOverride;                               // 0x0398(0x0010) (Edit, ZeroConstructor)
	float                                              NegativeZBoundsExtension;                                 // 0x03A8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PositiveZBoundsExtension;                                 // 0x03AC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<class ULandscapeComponent*>                 LandscapeComponents;                                      // 0x03B0(0x0010) (ExportObject, ZeroConstructor)
	TArray<class ULandscapeHeightfieldCollisionComponent*> CollisionComponents;                                      // 0x03C0(0x0010) (ExportObject, ZeroConstructor)
	TArray<class UHierarchicalInstancedStaticMeshComponent*> FoliageComponents;                                        // 0x03D0(0x0010) (ExportObject, ZeroConstructor, Transient, DuplicateTransient)
	unsigned char                                      UnknownData04[0x64];                                      // 0x03E0(0x0064) MISSED OFFSET
	bool                                               bHasLandscapeGrass;                                       // 0x0444(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData05[0x3];                                       // 0x0445(0x0003) MISSED OFFSET
	float                                              StaticLightingResolution;                                 // 0x0448(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bCastStaticShadow : 1;                                    // 0x044C(0x0001) (Edit)
	unsigned char                                      bCastShadowAsTwoSided : 1;                                // 0x044C(0x0001) (Edit)
	unsigned char                                      bCastFarShadow : 1;                                       // 0x044C(0x0001) (Edit)
	unsigned char                                      UnknownData06[0x3];                                       // 0x044D(0x0003) MISSED OFFSET
	unsigned char                                      bAffectDistanceFieldLighting : 1;                         // 0x0450(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FLightingChannels                           LightingChannels;                                         // 0x0451(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData07[0x2];                                       // 0x0452(0x0002) MISSED OFFSET
	unsigned char                                      bUseMaterialPositionOffsetInStaticLighting : 1;           // 0x0454(0x0001) (Edit)
	unsigned char                                      bRenderCustomDepth : 1;                                   // 0x0454(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData08[0x3];                                       // 0x0455(0x0003) MISSED OFFSET
	int                                                CustomDepthStencilValue;                                  // 0x0458(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              LDMaxDrawDistance;                                        // 0x045C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FLightmassPrimitiveSettings                 LightmassSettings;                                        // 0x0460(0x0018) (Edit)
	int                                                CollisionMipLevel;                                        // 0x0478(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                SimpleCollisionMipLevel;                                  // 0x047C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              CollisionThickness;                                       // 0x0480(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData09[0x4];                                       // 0x0484(0x0004) MISSED OFFSET
	struct FBodyInstance                               BodyInstance;                                             // 0x0488(0x0150) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bGenerateOverlapEvents : 1;                               // 0x05D8(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bBakeMaterialPositionOffsetIntoCollision : 1;             // 0x05D8(0x0001) (Edit)
	unsigned char                                      UnknownData10[0x3];                                       // 0x05D9(0x0003) MISSED OFFSET
	int                                                ComponentSizeQuads;                                       // 0x05DC(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                SubsectionSizeQuads;                                      // 0x05E0(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                NumSubsections;                                           // 0x05E4(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      bUsedForNavigation : 1;                                   // 0x05E8(0x0001) (Edit)
	unsigned char                                      UnknownData11[0x3];                                       // 0x05E9(0x0003) MISSED OFFSET
	bool                                               bUseDynamicMaterialInstance;                              // 0x05EC(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	ENavDataGatheringMode                              NavigationGeometryGatheringMode;                          // 0x05ED(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bUseLandscapeForCullingInvisibleHLODVertices;             // 0x05EE(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData12[0x51];                                      // 0x05EF(0x0051) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeProxy");
		return ptr;
	}


	void SetLandscapeMaterialVectorParameterValue(const struct FName& ParameterName, const struct FLinearColor& Value);
	void SetLandscapeMaterialTextureParameterValue(const struct FName& ParameterName, class UTexture* Value);
	void SetLandscapeMaterialScalarParameterValue(const struct FName& ParameterName, float Value);
	void EditorSetLandscapeMaterial(class UMaterialInterface* NewLandscapeMaterial);
	void EditorApplySpline(class USplineComponent* InSplineComponent, float StartWidth, float EndWidth, float StartSideFalloff, float EndSideFalloff, float StartRoll, float EndRoll, int NumSubdivisions, bool bRaiseHeights, bool bLowerHeights, class ULandscapeLayerInfoObject* PaintLayer);
	void ChangeUseTessellationComponentScreenSizeFalloff(bool InComponentScreenSizeToUseSubSections);
	void ChangeTessellationComponentScreenSizeFalloff(float InUseTessellationComponentScreenSizeFalloff);
	void ChangeTessellationComponentScreenSize(float InTessellationComponentScreenSize);
	void ChangeLODDistanceFactor(float InLODDistanceFactor);
	void ChangeComponentScreenSizeToUseSubSections(float InComponentScreenSizeToUseSubSections);
};


// Class Landscape.Landscape
// 0x0000 (0x0640 - 0x0640)
class ALandscape : public ALandscapeProxy
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.Landscape");
		return ptr;
	}

};


// Class Landscape.LandscapeComponent
// 0x01E0 (0x0740 - 0x0560)
class ULandscapeComponent : public UPrimitiveComponent
{
public:
	int                                                ComponentSizeQuads;                                       // 0x0560(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                SubsectionSizeQuads;                                      // 0x0564(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                NumSubsections;                                           // 0x0568(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x056C(0x0004) MISSED OFFSET
	class UMaterialInterface*                          OverrideMaterial;                                         // 0x0570(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          OverrideHoleMaterial;                                     // 0x0578(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TArray<struct FLandscapeComponentMaterialOverride> OverrideMaterials;                                        // 0x0580(0x0010) (Edit, ZeroConstructor)
	TArray<class UMaterialInstanceConstant*>           MaterialInstances;                                        // 0x0590(0x0010) (ZeroConstructor)
	TArray<class UMaterialInstanceDynamic*>            MaterialInstancesDynamic;                                 // 0x05A0(0x0010) (ZeroConstructor, Transient)
	TArray<int8_t>                                     LODIndexToMaterialIndex;                                  // 0x05B0(0x0010) (ZeroConstructor)
	TArray<int8_t>                                     MaterialIndexToDisabledTessellationMaterial;              // 0x05C0(0x0010) (ZeroConstructor)
	TArray<struct FWeightmapLayerAllocationInfo>       WeightmapLayerAllocations;                                // 0x05D0(0x0010) (ZeroConstructor)
	TArray<class UTexture2D*>                          WeightmapTextures;                                        // 0x05E0(0x0010) (ZeroConstructor)
	class UTexture2D*                                  XYOffsetmapTexture;                                       // 0x05F0(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x05F8(0x0008) MISSED OFFSET
	struct FVector4                                    WeightmapScaleBias;                                       // 0x0600(0x0010) (ZeroConstructor, IsPlainOldData)
	float                                              WeightmapSubsectionOffset;                                // 0x0610(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0xC];                                       // 0x0614(0x000C) MISSED OFFSET
	struct FVector4                                    HeightmapScaleBias;                                       // 0x0620(0x0010) (ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  HeightmapTexture;                                         // 0x0630(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FBox                                        CachedLocalBox;                                           // 0x0638(0x001C) (ZeroConstructor, IsPlainOldData)
	TLazyObjectPtr<class ULandscapeHeightfieldCollisionComponent> CollisionComponent;                                       // 0x0654(0x001C) (ExportObject, InstancedReference, IsPlainOldData)
	struct FGuid                                       MapBuildDataId;                                           // 0x0670(0x0010) (ZeroConstructor, IsPlainOldData)
	TArray<struct FGuid>                               IrrelevantLights;                                         // 0x0680(0x0010) (ZeroConstructor, Deprecated)
	int                                                CollisionMipLevel;                                        // 0x0690(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                SimpleCollisionMipLevel;                                  // 0x0694(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              NegativeZBoundsExtension;                                 // 0x0698(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PositiveZBoundsExtension;                                 // 0x069C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              StaticLightingResolution;                                 // 0x06A0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                ForcedLOD;                                                // 0x06A4(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                LODBias;                                                  // 0x06A8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FGuid                                       StateId;                                                  // 0x06AC(0x0010) (ZeroConstructor, IsPlainOldData)
	struct FGuid                                       BakedTextureMaterialGuid;                                 // 0x06BC(0x0010) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x06CC(0x0004) MISSED OFFSET
	class UTexture2D*                                  GIBakedBaseColorTexture;                                  // 0x06D0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData)
	unsigned char                                      MobileBlendableLayerMask;                                 // 0x06D8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x7];                                       // 0x06D9(0x0007) MISSED OFFSET
	class UMaterialInterface*                          MobileMaterialInterface;                                  // 0x06E0(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	TArray<class UMaterialInterface*>                  MobileMaterialInterfaces;                                 // 0x06E8(0x0010) (ZeroConstructor)
	TArray<class UTexture2D*>                          MobileWeightmapTextures;                                  // 0x06F8(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData05[0x38];                                      // 0x0708(0x0038) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeComponent");
		return ptr;
	}


	class UMaterialInstanceDynamic* GetMaterialInstanceDynamic(int InIndex);
};


// Class Landscape.LandscapeGizmoActor
// 0x0000 (0x0328 - 0x0328)
class ALandscapeGizmoActor : public AActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeGizmoActor");
		return ptr;
	}

};


// Class Landscape.LandscapeGizmoActiveActor
// 0x0050 (0x0378 - 0x0328)
class ALandscapeGizmoActiveActor : public ALandscapeGizmoActor
{
public:
	unsigned char                                      UnknownData00[0x50];                                      // 0x0328(0x0050) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeGizmoActiveActor");
		return ptr;
	}

};


// Class Landscape.LandscapeGizmoRenderComponent
// 0x0000 (0x0560 - 0x0560)
class ULandscapeGizmoRenderComponent : public UPrimitiveComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeGizmoRenderComponent");
		return ptr;
	}

};


// Class Landscape.LandscapeGrassType
// 0x0038 (0x0060 - 0x0028)
class ULandscapeGrassType : public UObject
{
public:
	TArray<struct FGrassVariety>                       GrassVarieties;                                           // 0x0028(0x0010) (Edit, ZeroConstructor)
	unsigned char                                      bEnableDensityScaling : 1;                                // 0x0038(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0039(0x0007) MISSED OFFSET
	class UStaticMesh*                                 GrassMesh;                                                // 0x0040(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              GrassDensity;                                             // 0x0048(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              PlacementJitter;                                          // 0x004C(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	int                                                StartCullDistance;                                        // 0x0050(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	int                                                EndCullDistance;                                          // 0x0054(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	bool                                               RandomRotation;                                           // 0x0058(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	bool                                               AlignToSurface;                                           // 0x0059(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x005A(0x0006) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeGrassType");
		return ptr;
	}

};


// Class Landscape.LandscapeHeightfieldCollisionComponent
// 0x00E0 (0x0640 - 0x0560)
class ULandscapeHeightfieldCollisionComponent : public UPrimitiveComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0560(0x0008) MISSED OFFSET
	int                                                SectionBaseX;                                             // 0x0568(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                SectionBaseY;                                             // 0x056C(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                CollisionSizeQuads;                                       // 0x0570(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              CollisionScale;                                           // 0x0574(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                SimpleCollisionSizeQuads;                                 // 0x0578(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x057C(0x0004) MISSED OFFSET
	TArray<unsigned char>                              CollisionQuadFlags;                                       // 0x0580(0x0010) (ZeroConstructor)
	struct FGuid                                       HeightfieldGuid;                                          // 0x0590(0x0010) (ZeroConstructor, IsPlainOldData)
	struct FBox                                        CachedLocalBox;                                           // 0x05A0(0x001C) (ZeroConstructor, IsPlainOldData)
	TLazyObjectPtr<class ULandscapeComponent>          RenderComponent;                                          // 0x05BC(0x001C) (ExportObject, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData02[0x10];                                      // 0x05D8(0x0010) MISSED OFFSET
	TArray<class UPhysicalMaterial*>                   CookedPhysicalMaterials;                                  // 0x05E8(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData03[0x48];                                      // 0x05F8(0x0048) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeHeightfieldCollisionComponent");
		return ptr;
	}

};


// Class Landscape.LandscapeInfo
// 0x01D8 (0x0200 - 0x0028)
class ULandscapeInfo : public UObject
{
public:
	TLazyObjectPtr<class ALandscape>                   LandscapeActor;                                           // 0x0028(0x001C) (IsPlainOldData)
	struct FGuid                                       LandscapeGuid;                                            // 0x0044(0x0010) (ZeroConstructor, IsPlainOldData)
	int                                                ComponentSizeQuads;                                       // 0x0054(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                SubsectionSizeQuads;                                      // 0x0058(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                ComponentNumSubsections;                                  // 0x005C(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FVector                                     DrawScale;                                                // 0x0060(0x000C) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x54];                                      // 0x006C(0x0054) MISSED OFFSET
	unsigned char                                      UnknownData01[0x50];                                      // 0x006C(0x0050) UNKNOWN PROPERTY: SetProperty Landscape.LandscapeInfo.Proxies
	unsigned char                                      UnknownData02[0xF0];                                      // 0x0110(0x00F0) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeInfo");
		return ptr;
	}

};


// Class Landscape.LandscapeInfoMap
// 0x0058 (0x0080 - 0x0028)
class ULandscapeInfoMap : public UObject
{
public:
	unsigned char                                      UnknownData00[0x58];                                      // 0x0028(0x0058) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeInfoMap");
		return ptr;
	}

};


// Class Landscape.LandscapeLayerInfoObject
// 0x0028 (0x0050 - 0x0028)
class ULandscapeLayerInfoObject : public UObject
{
public:
	struct FName                                       LayerName;                                                // 0x0028(0x0008) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	class UPhysicalMaterial*                           PhysMaterial;                                             // 0x0030(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              Hardness;                                                 // 0x0038(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                LayerUsageDebugColor;                                     // 0x003C(0x0010) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x004C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeLayerInfoObject");
		return ptr;
	}

};


// Class Landscape.LandscapeMaterialInstanceConstant
// 0x0008 (0x01F0 - 0x01E8)
class ULandscapeMaterialInstanceConstant : public UMaterialInstanceConstant
{
public:
	unsigned char                                      bIsLayerThumbnail : 1;                                    // 0x01E8(0x0001)
	unsigned char                                      bDisableTessellation : 1;                                 // 0x01E8(0x0001)
	unsigned char                                      bMobile : 1;                                              // 0x01E8(0x0001)
	unsigned char                                      bEditorToolUsage : 1;                                     // 0x01E8(0x0001)
	unsigned char                                      UnknownData00[0x7];                                       // 0x01E9(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeMaterialInstanceConstant");
		return ptr;
	}

};


// Class Landscape.LandscapeMeshCollisionComponent
// 0x0010 (0x0650 - 0x0640)
class ULandscapeMeshCollisionComponent : public ULandscapeHeightfieldCollisionComponent
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0640(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeMeshCollisionComponent");
		return ptr;
	}

};


// Class Landscape.LandscapeMeshProxyActor
// 0x0008 (0x0330 - 0x0328)
class ALandscapeMeshProxyActor : public AActor
{
public:
	class ULandscapeMeshProxyComponent*                LandscapeMeshProxyComponent;                              // 0x0328(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeMeshProxyActor");
		return ptr;
	}

};


// Class Landscape.LandscapeMeshProxyComponent
// 0x0020 (0x0610 - 0x05F0)
class ULandscapeMeshProxyComponent : public UStaticMeshComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x05F0(0x0008) MISSED OFFSET
	TArray<struct FIntPoint>                           ProxyComponentBases;                                      // 0x05F8(0x0010) (ZeroConstructor)
	int8_t                                             ProxyLOD;                                                 // 0x0608(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0609(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeMeshProxyComponent");
		return ptr;
	}

};


// Class Landscape.LandscapeSplinesComponent
// 0x0030 (0x0590 - 0x0560)
class ULandscapeSplinesComponent : public UPrimitiveComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0560(0x0008) MISSED OFFSET
	TArray<class ULandscapeSplineSegment*>             Segments;                                                 // 0x0568(0x0010) (ZeroConstructor)
	TArray<class UMeshComponent*>                      CookedForeignMeshComponents;                              // 0x0578(0x0010) (ExportObject, ZeroConstructor)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0588(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeSplinesComponent");
		return ptr;
	}


	TArray<class USplineMeshComponent*> GetSplineMeshComponents();
};


// Class Landscape.LandscapeSplineControlPoint
// 0x0070 (0x0098 - 0x0028)
class ULandscapeSplineControlPoint : public UObject
{
public:
	struct FVector                                     Location;                                                 // 0x0028(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    Rotation;                                                 // 0x0034(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              Width;                                                    // 0x0040(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SideFalloff;                                              // 0x0044(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              EndFalloff;                                               // 0x0048(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x004C(0x0004) MISSED OFFSET
	TArray<struct FLandscapeSplineConnection>          ConnectedSegments;                                        // 0x0050(0x0010) (ZeroConstructor)
	TArray<struct FLandscapeSplineInterpPoint>         Points;                                                   // 0x0060(0x0010) (ZeroConstructor)
	struct FBox                                        Bounds;                                                   // 0x0070(0x001C) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x008C(0x0004) MISSED OFFSET
	class UControlPointMeshComponent*                  LocalMeshComponent;                                       // 0x0090(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeSplineControlPoint");
		return ptr;
	}

};


// Class Landscape.LandscapeSplineSegment
// 0x0088 (0x00B0 - 0x0028)
class ULandscapeSplineSegment : public UObject
{
public:
	struct FLandscapeSplineSegmentConnection           Connections[0x2];                                         // 0x0028(0x0018) (Edit, EditFixedSize)
	struct FInterpCurveVector                          SplineInfo;                                               // 0x0058(0x0018) (ZeroConstructor)
	TArray<struct FLandscapeSplineInterpPoint>         Points;                                                   // 0x0070(0x0010) (ZeroConstructor)
	struct FBox                                        Bounds;                                                   // 0x0080(0x001C) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x009C(0x0004) MISSED OFFSET
	TArray<class USplineMeshComponent*>                LocalMeshComponents;                                      // 0x00A0(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeSplineSegment");
		return ptr;
	}

};


// Class Landscape.LandscapeStreamingProxy
// 0x0020 (0x0660 - 0x0640)
class ALandscapeStreamingProxy : public ALandscapeProxy
{
public:
	TLazyObjectPtr<class ALandscape>                   LandscapeActor;                                           // 0x0640(0x001C) (Edit, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x065C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.LandscapeStreamingProxy");
		return ptr;
	}

};


// Class Landscape.MaterialExpressionLandscapeGrassOutput
// 0x0010 (0x0050 - 0x0040)
class UMaterialExpressionLandscapeGrassOutput : public UMaterialExpressionCustomOutput
{
public:
	TArray<struct FGrassInput>                         GrassTypes;                                               // 0x0040(0x0010) (Edit, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.MaterialExpressionLandscapeGrassOutput");
		return ptr;
	}

};


// Class Landscape.MaterialExpressionLandscapeLayerBlend
// 0x0020 (0x0060 - 0x0040)
class UMaterialExpressionLandscapeLayerBlend : public UMaterialExpression
{
public:
	TArray<struct FLayerBlendInput>                    Layers;                                                   // 0x0040(0x0010) (Edit, ZeroConstructor)
	struct FGuid                                       ExpressionGUID;                                           // 0x0050(0x0010) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.MaterialExpressionLandscapeLayerBlend");
		return ptr;
	}

};


// Class Landscape.MaterialExpressionLandscapeLayerCoords
// 0x0018 (0x0058 - 0x0040)
class UMaterialExpressionLandscapeLayerCoords : public UMaterialExpression
{
public:
	TEnumAsByte<ETerrainCoordMappingType>              MappingType;                                              // 0x0040(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ELandscapeCustomizedCoordType>         CustomUVType;                                             // 0x0041(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0042(0x0002) MISSED OFFSET
	float                                              MappingScale;                                             // 0x0044(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MappingRotation;                                          // 0x0048(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MappingPanU;                                              // 0x004C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MappingPanV;                                              // 0x0050(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0054(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.MaterialExpressionLandscapeLayerCoords");
		return ptr;
	}

};


// Class Landscape.MaterialExpressionLandscapeLayerSample
// 0x0020 (0x0060 - 0x0040)
class UMaterialExpressionLandscapeLayerSample : public UMaterialExpression
{
public:
	struct FName                                       ParameterName;                                            // 0x0040(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PreviewWeight;                                            // 0x0048(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FGuid                                       ExpressionGUID;                                           // 0x004C(0x0010) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x005C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.MaterialExpressionLandscapeLayerSample");
		return ptr;
	}

};


// Class Landscape.MaterialExpressionLandscapeLayerSwitch
// 0x0050 (0x0090 - 0x0040)
class UMaterialExpressionLandscapeLayerSwitch : public UMaterialExpression
{
public:
	struct FExpressionInput                            LayerUsed;                                                // 0x0040(0x0010)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0050(0x0008) MISSED OFFSET
	struct FExpressionInput                            LayerNotUsed;                                             // 0x0058(0x0010)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0068(0x0008) MISSED OFFSET
	struct FName                                       ParameterName;                                            // 0x0070(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      PreviewUsed : 1;                                          // 0x0078(0x0001) (Edit)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0079(0x0003) MISSED OFFSET
	struct FGuid                                       ExpressionGUID;                                           // 0x007C(0x0010) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x008C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.MaterialExpressionLandscapeLayerSwitch");
		return ptr;
	}

};


// Class Landscape.MaterialExpressionLandscapeLayerWeight
// 0x0058 (0x0098 - 0x0040)
class UMaterialExpressionLandscapeLayerWeight : public UMaterialExpression
{
public:
	struct FExpressionInput                            Base;                                                     // 0x0040(0x0010)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0050(0x0008) MISSED OFFSET
	struct FExpressionInput                            Layer;                                                    // 0x0058(0x0010)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0068(0x0008) MISSED OFFSET
	struct FName                                       ParameterName;                                            // 0x0070(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PreviewWeight;                                            // 0x0078(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ConstBase;                                                // 0x007C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FGuid                                       ExpressionGUID;                                           // 0x0088(0x0010) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.MaterialExpressionLandscapeLayerWeight");
		return ptr;
	}

};


// Class Landscape.MaterialExpressionLandscapeVisibilityMask
// 0x0010 (0x0050 - 0x0040)
class UMaterialExpressionLandscapeVisibilityMask : public UMaterialExpression
{
public:
	struct FGuid                                       ExpressionGUID;                                           // 0x0040(0x0010) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Landscape.MaterialExpressionLandscapeVisibilityMask");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
