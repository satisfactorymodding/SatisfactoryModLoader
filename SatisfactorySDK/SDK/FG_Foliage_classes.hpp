#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Foliage_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class Foliage.FoliageInstancedStaticMeshComponent
// 0x0020 (0x0790 - 0x0770)
class UFoliageInstancedStaticMeshComponent : public UHierarchicalInstancedStaticMeshComponent
{
public:
	struct FScriptMulticastDelegate                    OnInstanceTakePointDamage;                                // 0x0770(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnInstanceTakeRadialDamage;                               // 0x0780(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.FoliageInstancedStaticMeshComponent");
		return ptr;
	}

};


// Class Foliage.FoliageStatistics
// 0x0000 (0x0028 - 0x0028)
class UFoliageStatistics : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.FoliageStatistics");
		return ptr;
	}


	int FoliageOverlappingSphereCount(class UObject* WorldContextObject, class UStaticMesh* StaticMesh, const struct FVector& CenterPosition, float Radius);
	int FoliageOverlappingBoxCount(class UObject* WorldContextObject, class UStaticMesh* StaticMesh, const struct FBox& Box);
};


// Class Foliage.FoliageType
// 0x0330 (0x0358 - 0x0028)
class UFoliageType : public UObject
{
public:
	struct FGuid                                       UpdateGuid;                                               // 0x0028(0x0010) (ZeroConstructor, IsPlainOldData)
	float                                              Density;                                                  // 0x0038(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              DensityAdjustmentFactor;                                  // 0x003C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              Radius;                                                   // 0x0040(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	EFoliageScaling                                    Scaling;                                                  // 0x0044(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0045(0x0003) MISSED OFFSET
	struct FFloatInterval                              ScaleX;                                                   // 0x0048(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFloatInterval                              ScaleY;                                                   // 0x0050(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFloatInterval                              ScaleZ;                                                   // 0x0058(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFoliageVertexColorChannelMask              VertexColorMaskByChannel[0x4];                            // 0x0060(0x000C) (Edit)
	TEnumAsByte<EFoliageVertexColorMask>               VertexColorMask;                                          // 0x0090(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0091(0x0003) MISSED OFFSET
	float                                              VertexColorMaskThreshold;                                 // 0x0094(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      VertexColorMaskInvert : 1;                                // 0x0098(0x0001) (Deprecated)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0099(0x0003) MISSED OFFSET
	struct FFloatInterval                              ZOffset;                                                  // 0x009C(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      AlignToNormal : 1;                                        // 0x00A4(0x0001) (Edit)
	unsigned char                                      UnknownData03[0x3];                                       // 0x00A5(0x0003) MISSED OFFSET
	float                                              AlignMaxAngle;                                            // 0x00A8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      RandomYaw : 1;                                            // 0x00AC(0x0001) (Edit)
	unsigned char                                      UnknownData04[0x3];                                       // 0x00AD(0x0003) MISSED OFFSET
	float                                              RandomPitchAngle;                                         // 0x00B0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFloatInterval                              GroundSlopeAngle;                                         // 0x00B4(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFloatInterval                              Height;                                                   // 0x00BC(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData05[0x4];                                       // 0x00C4(0x0004) MISSED OFFSET
	TArray<struct FName>                               LandscapeLayers;                                          // 0x00C8(0x0010) (Edit, ZeroConstructor)
	struct FName                                       LandscapeLayer;                                           // 0x00D8(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      CollisionWithWorld : 1;                                   // 0x00E0(0x0001) (Edit)
	unsigned char                                      UnknownData06[0x3];                                       // 0x00E1(0x0003) MISSED OFFSET
	struct FVector                                     CollisionScale;                                           // 0x00E4(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MinimumLayerWeight;                                       // 0x00F0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FBoxSphereBounds                            MeshBounds;                                               // 0x00F4(0x001C) (ZeroConstructor, IsPlainOldData)
	struct FVector                                     LowBoundOriginRadius;                                     // 0x0110(0x000C) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EComponentMobility>                    Mobility;                                                 // 0x011C(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData07[0x3];                                       // 0x011D(0x0003) MISSED OFFSET
	struct FInt32Interval                              CullDistance;                                             // 0x0120(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bOverrideMinVertsToSplitNode;                             // 0x0128(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData08[0x3];                                       // 0x0129(0x0003) MISSED OFFSET
	int                                                OverriddenMinVertsToSplitNode;                            // 0x012C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bEnableStaticLighting : 1;                                // 0x0130(0x0001) (Deprecated)
	unsigned char                                      CastShadow : 1;                                           // 0x0130(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bAffectDynamicIndirectLighting : 1;                       // 0x0130(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bAffectDistanceFieldLighting : 1;                         // 0x0130(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bCastDynamicShadow : 1;                                   // 0x0130(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bCastStaticShadow : 1;                                    // 0x0130(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bCastShadowAsTwoSided : 1;                                // 0x0130(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bReceivesDecals : 1;                                      // 0x0130(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bOverrideLightMapRes : 1;                                 // 0x0131(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData09[0x2];                                       // 0x0132(0x0002) MISSED OFFSET
	int                                                OverriddenLightMapRes;                                    // 0x0134(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	ELightmapType                                      LightmapType;                                             // 0x0138(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData10[0x3];                                       // 0x0139(0x0003) MISSED OFFSET
	unsigned char                                      bUseAsOccluder : 1;                                       // 0x013C(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData11[0x3];                                       // 0x013D(0x0003) MISSED OFFSET
	struct FBodyInstance                               BodyInstance;                                             // 0x0140(0x0150) (Edit)
	TEnumAsByte<EHasCustomNavigableGeometry>           CustomNavigableGeometry;                                  // 0x0290(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	struct FLightingChannels                           LightingChannels;                                         // 0x0291(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData12[0x2];                                       // 0x0292(0x0002) MISSED OFFSET
	unsigned char                                      bRenderCustomDepth : 1;                                   // 0x0294(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData13[0x3];                                       // 0x0295(0x0003) MISSED OFFSET
	int                                                CustomDepthStencilValue;                                  // 0x0298(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              CollisionRadius;                                          // 0x029C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ShadeRadius;                                              // 0x02A0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                NumSteps;                                                 // 0x02A4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              InitialSeedDensity;                                       // 0x02A8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              AverageSpreadDistance;                                    // 0x02AC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SpreadVariance;                                           // 0x02B0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                SeedsPerStep;                                             // 0x02B4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                DistributionSeed;                                         // 0x02B8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MaxInitialSeedOffset;                                     // 0x02BC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bCanGrowInShade;                                          // 0x02C0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bSpawnsInShade;                                           // 0x02C1(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData14[0x2];                                       // 0x02C2(0x0002) MISSED OFFSET
	float                                              MaxInitialAge;                                            // 0x02C4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MaxAge;                                                   // 0x02C8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              OverlapPriority;                                          // 0x02CC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFloatInterval                              ProceduralScale;                                          // 0x02D0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FRuntimeFloatCurve                          ScaleCurve;                                               // 0x02D8(0x0078) (Edit)
	int                                                ChangeCount;                                              // 0x0350(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      ReapplyDensity : 1;                                       // 0x0354(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyRadius : 1;                                        // 0x0354(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyAlignToNormal : 1;                                 // 0x0354(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyRandomYaw : 1;                                     // 0x0354(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyScaling : 1;                                       // 0x0354(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyScaleX : 1;                                        // 0x0354(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyScaleY : 1;                                        // 0x0354(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyScaleZ : 1;                                        // 0x0354(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyRandomPitchAngle : 1;                              // 0x0355(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyGroundSlope : 1;                                   // 0x0355(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyHeight : 1;                                        // 0x0355(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyLandscapeLayers : 1;                               // 0x0355(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyZOffset : 1;                                       // 0x0355(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyCollisionWithWorld : 1;                            // 0x0355(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      ReapplyVertexColorMask : 1;                               // 0x0355(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      bEnableDensityScaling : 1;                                // 0x0355(0x0001) (Edit)
	unsigned char                                      UnknownData15[0x2];                                       // 0x0356(0x0002) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.FoliageType");
		return ptr;
	}

};


// Class Foliage.FoliageType_InstancedStaticMesh
// 0x0020 (0x0378 - 0x0358)
class UFoliageType_InstancedStaticMesh : public UFoliageType
{
public:
	class UStaticMesh*                                 Mesh;                                                     // 0x0358(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<class UMaterialInterface*>                  OverrideMaterials;                                        // 0x0360(0x0010) (Edit, ZeroConstructor)
	class UClass*                                      ComponentClass;                                           // 0x0370(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.FoliageType_InstancedStaticMesh");
		return ptr;
	}

};


// Class Foliage.InstancedFoliageActor
// 0x0050 (0x0378 - 0x0328)
class AInstancedFoliageActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x50];                                      // 0x0328(0x0050) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.InstancedFoliageActor");
		return ptr;
	}

};


// Class Foliage.InteractiveFoliageActor
// 0x0060 (0x0398 - 0x0338)
class AInteractiveFoliageActor : public AStaticMeshActor
{
public:
	class UCapsuleComponent*                           CapsuleComponent;                                         // 0x0338(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector                                     TouchingActorEntryPosition;                               // 0x0340(0x000C) (ZeroConstructor, Transient, IsPlainOldData)
	struct FVector                                     FoliageVelocity;                                          // 0x034C(0x000C) (ZeroConstructor, Transient, IsPlainOldData)
	struct FVector                                     FoliageForce;                                             // 0x0358(0x000C) (ZeroConstructor, Transient, IsPlainOldData)
	struct FVector                                     FoliagePosition;                                          // 0x0364(0x000C) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              FoliageDamageImpulseScale;                                // 0x0370(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FoliageTouchImpulseScale;                                 // 0x0374(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FoliageStiffness;                                         // 0x0378(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FoliageStiffnessQuadratic;                                // 0x037C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FoliageDamping;                                           // 0x0380(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              MaxDamageImpulse;                                         // 0x0384(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              MaxTouchImpulse;                                          // 0x0388(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              MaxForce;                                                 // 0x038C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Mass;                                                     // 0x0390(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0394(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.InteractiveFoliageActor");
		return ptr;
	}


	void CapsuleTouched(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& OverlapInfo);
};


// Class Foliage.InteractiveFoliageComponent
// 0x0000 (0x05F0 - 0x05F0)
class UInteractiveFoliageComponent : public UStaticMeshComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.InteractiveFoliageComponent");
		return ptr;
	}

};


// Class Foliage.ProceduralFoliageBlockingVolume
// 0x0008 (0x0368 - 0x0360)
class AProceduralFoliageBlockingVolume : public AVolume
{
public:
	class AProceduralFoliageVolume*                    ProceduralFoliageVolume;                                  // 0x0360(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.ProceduralFoliageBlockingVolume");
		return ptr;
	}

};


// Class Foliage.ProceduralFoliageComponent
// 0x0028 (0x0118 - 0x00F0)
class UProceduralFoliageComponent : public UActorComponent
{
public:
	class UProceduralFoliageSpawner*                   FoliageSpawner;                                           // 0x00F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              TileOverlap;                                              // 0x00F8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x00FC(0x0004) MISSED OFFSET
	class AVolume*                                     SpawningVolume;                                           // 0x0100(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FGuid                                       ProceduralGuid;                                           // 0x0108(0x0010) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.ProceduralFoliageComponent");
		return ptr;
	}

};


// Class Foliage.ProceduralFoliageSpawner
// 0x0048 (0x0070 - 0x0028)
class UProceduralFoliageSpawner : public UObject
{
public:
	int                                                RandomSeed;                                               // 0x0028(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              TileSize;                                                 // 0x002C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                NumUniqueTiles;                                           // 0x0030(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              MinimumQuadTreeSize;                                      // 0x0034(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
	TArray<struct FFoliageTypeObject>                  FoliageTypes;                                             // 0x0040(0x0010) (Edit, ZeroConstructor)
	bool                                               bNeedsSimulation;                                         // 0x0050(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x1F];                                      // 0x0051(0x001F) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.ProceduralFoliageSpawner");
		return ptr;
	}


	void Simulate(int NumSteps);
};


// Class Foliage.ProceduralFoliageTile
// 0x0130 (0x0158 - 0x0028)
class UProceduralFoliageTile : public UObject
{
public:
	class UProceduralFoliageSpawner*                   FoliageSpawner;                                           // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0xA0];                                      // 0x0030(0x00A0) MISSED OFFSET
	TArray<struct FProceduralFoliageInstance>          InstancesArray;                                           // 0x00D0(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x78];                                      // 0x00E0(0x0078) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.ProceduralFoliageTile");
		return ptr;
	}

};


// Class Foliage.ProceduralFoliageVolume
// 0x0008 (0x0368 - 0x0360)
class AProceduralFoliageVolume : public AVolume
{
public:
	class UProceduralFoliageComponent*                 ProceduralComponent;                                      // 0x0360(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Foliage.ProceduralFoliageVolume");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
