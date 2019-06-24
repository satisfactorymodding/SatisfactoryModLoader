#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_NavigationSystem_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class NavigationSystem.NavArea
// 0x0018 (0x0048 - 0x0030)
class UNavArea : public UNavAreaBase
{
public:
	float                                              DefaultCost;                                              // 0x0030(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              FixedAreaEnteringCost;                                    // 0x0034(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	struct FColor                                      DrawColor;                                                // 0x0038(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	struct FNavAgentSelector                           SupportedAgents;                                          // 0x003C(0x0004) (Edit, Config)
	unsigned char                                      bSupportsAgent0 : 1;                                      // 0x0040(0x0001) (Config)
	unsigned char                                      bSupportsAgent1 : 1;                                      // 0x0040(0x0001) (Config)
	unsigned char                                      bSupportsAgent2 : 1;                                      // 0x0040(0x0001) (Config)
	unsigned char                                      bSupportsAgent3 : 1;                                      // 0x0040(0x0001) (Config)
	unsigned char                                      bSupportsAgent4 : 1;                                      // 0x0040(0x0001) (Config)
	unsigned char                                      bSupportsAgent5 : 1;                                      // 0x0040(0x0001) (Config)
	unsigned char                                      bSupportsAgent6 : 1;                                      // 0x0040(0x0001) (Config)
	unsigned char                                      bSupportsAgent7 : 1;                                      // 0x0040(0x0001) (Config)
	unsigned char                                      bSupportsAgent8 : 1;                                      // 0x0041(0x0001) (Config)
	unsigned char                                      bSupportsAgent9 : 1;                                      // 0x0041(0x0001) (Config)
	unsigned char                                      bSupportsAgent10 : 1;                                     // 0x0041(0x0001) (Config)
	unsigned char                                      bSupportsAgent11 : 1;                                     // 0x0041(0x0001) (Config)
	unsigned char                                      bSupportsAgent12 : 1;                                     // 0x0041(0x0001) (Config)
	unsigned char                                      bSupportsAgent13 : 1;                                     // 0x0041(0x0001) (Config)
	unsigned char                                      bSupportsAgent14 : 1;                                     // 0x0041(0x0001) (Config)
	unsigned char                                      bSupportsAgent15 : 1;                                     // 0x0041(0x0001) (Config)
	unsigned char                                      UnknownData00[0x6];                                       // 0x0042(0x0006) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavArea");
		return ptr;
	}

};


// Class NavigationSystem.NavigationData
// 0x01C0 (0x04E8 - 0x0328)
class ANavigationData : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class UPrimitiveComponent*                         RenderingComp;                                            // 0x0330(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, DuplicateTransient, IsPlainOldData)
	struct FNavDataConfig                              NavDataConfig;                                            // 0x0338(0x0068)
	unsigned char                                      bEnableDrawing : 1;                                       // 0x03A0(0x0001) (Edit, Transient)
	unsigned char                                      bForceRebuildOnLoad : 1;                                  // 0x03A0(0x0001) (Edit, Config)
	unsigned char                                      bCanBeMainNavData : 1;                                    // 0x03A0(0x0001) (Edit, Config)
	unsigned char                                      bCanSpawnOnRebuild : 1;                                   // 0x03A0(0x0001) (Edit, Config, EditConst)
	unsigned char                                      bRebuildAtRuntime : 1;                                    // 0x03A0(0x0001) (Config, Deprecated)
	unsigned char                                      UnknownData01[0x3];                                       // 0x03A1(0x0003) MISSED OFFSET
	ERuntimeGenerationType                             RuntimeGeneration;                                        // 0x03A4(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x03A5(0x0003) MISSED OFFSET
	float                                              ObservedPathsTickInterval;                                // 0x03A8(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	uint32_t                                           DataVersion;                                              // 0x03AC(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0xD0];                                      // 0x03B0(0x00D0) MISSED OFFSET
	TArray<struct FSupportedAreaData>                  SupportedAreas;                                           // 0x0480(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData04[0x58];                                      // 0x0490(0x0058) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationData");
		return ptr;
	}

};


// Class NavigationSystem.AbstractNavData
// 0x0000 (0x04E8 - 0x04E8)
class AAbstractNavData : public ANavigationData
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.AbstractNavData");
		return ptr;
	}

};


// Class NavigationSystem.CrowdManagerBase
// 0x0000 (0x0028 - 0x0028)
class UCrowdManagerBase : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.CrowdManagerBase");
		return ptr;
	}

};


// Class NavigationSystem.NavArea_Default
// 0x0000 (0x0048 - 0x0048)
class UNavArea_Default : public UNavArea
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavArea_Default");
		return ptr;
	}

};


// Class NavigationSystem.NavArea_LowHeight
// 0x0000 (0x0048 - 0x0048)
class UNavArea_LowHeight : public UNavArea
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavArea_LowHeight");
		return ptr;
	}

};


// Class NavigationSystem.NavArea_Null
// 0x0000 (0x0048 - 0x0048)
class UNavArea_Null : public UNavArea
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavArea_Null");
		return ptr;
	}

};


// Class NavigationSystem.NavArea_Obstacle
// 0x0000 (0x0048 - 0x0048)
class UNavArea_Obstacle : public UNavArea
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavArea_Obstacle");
		return ptr;
	}

};


// Class NavigationSystem.NavAreaMeta
// 0x0000 (0x0048 - 0x0048)
class UNavAreaMeta : public UNavArea
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavAreaMeta");
		return ptr;
	}

};


// Class NavigationSystem.NavAreaMeta_SwitchByAgent
// 0x0080 (0x00C8 - 0x0048)
class UNavAreaMeta_SwitchByAgent : public UNavAreaMeta
{
public:
	class UClass*                                      Agent0Area;                                               // 0x0048(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent1Area;                                               // 0x0050(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent2Area;                                               // 0x0058(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent3Area;                                               // 0x0060(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent4Area;                                               // 0x0068(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent5Area;                                               // 0x0070(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent6Area;                                               // 0x0078(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent7Area;                                               // 0x0080(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent8Area;                                               // 0x0088(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent9Area;                                               // 0x0090(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent10Area;                                              // 0x0098(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent11Area;                                              // 0x00A0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent12Area;                                              // 0x00A8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent13Area;                                              // 0x00B0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent14Area;                                              // 0x00B8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Agent15Area;                                              // 0x00C0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavAreaMeta_SwitchByAgent");
		return ptr;
	}

};


// Class NavigationSystem.NavCollision
// 0x0068 (0x00D8 - 0x0070)
class UNavCollision : public UNavCollisionBase
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0070(0x0010) MISSED OFFSET
	TArray<struct FNavCollisionCylinder>               CylinderCollision;                                        // 0x0080(0x0010) (Edit, ZeroConstructor)
	TArray<struct FNavCollisionBox>                    BoxCollision;                                             // 0x0090(0x0010) (Edit, ZeroConstructor)
	class UClass*                                      AreaClass;                                                // 0x00A0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bGatherConvexGeometry : 1;                                // 0x00A8(0x0001) (Edit, Config)
	unsigned char                                      UnknownData01[0x2F];                                      // 0x00A9(0x002F) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavCollision");
		return ptr;
	}

};


// Class NavigationSystem.NavigationGraph
// 0x0000 (0x04E8 - 0x04E8)
class ANavigationGraph : public ANavigationData
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationGraph");
		return ptr;
	}

};


// Class NavigationSystem.NavigationGraphNode
// 0x0000 (0x0328 - 0x0328)
class ANavigationGraphNode : public AActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationGraphNode");
		return ptr;
	}

};


// Class NavigationSystem.NavigationGraphNodeComponent
// 0x0020 (0x0260 - 0x0240)
class UNavigationGraphNodeComponent : public USceneComponent
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0240(0x0010) MISSED OFFSET
	class UNavigationGraphNodeComponent*               NextNodeComponent;                                        // 0x0250(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UNavigationGraphNodeComponent*               PrevNodeComponent;                                        // 0x0258(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationGraphNodeComponent");
		return ptr;
	}

};


// Class NavigationSystem.NavigationInvokerComponent
// 0x0008 (0x00F8 - 0x00F0)
class UNavigationInvokerComponent : public UActorComponent
{
public:
	float                                              TileGenerationRadius;                                     // 0x00F0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              TileRemovalRadius;                                        // 0x00F4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationInvokerComponent");
		return ptr;
	}

};


// Class NavigationSystem.NavigationPath
// 0x0060 (0x0088 - 0x0028)
class UNavigationPath : public UObject
{
public:
	struct FScriptMulticastDelegate                    PathUpdatedNotifier;                                      // 0x0028(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<struct FVector>                             PathPoints;                                               // 0x0038(0x0010) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
	TEnumAsByte<ENavigationOptionFlag>                 RecalculateOnInvalidation;                                // 0x0048(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3F];                                      // 0x0049(0x003F) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationPath");
		return ptr;
	}


	bool IsValid();
	bool IsStringPulled();
	bool IsPartial();
	float GetPathLength();
	float GetPathCost();
	class FString GetDebugString();
	void EnableRecalculationOnInvalidation(TEnumAsByte<ENavigationOptionFlag> DoRecalculation);
	void EnableDebugDrawing(bool bShouldDrawDebugData, const struct FLinearColor& PathColor);
};


// Class NavigationSystem.NavigationPathGenerator
// 0x0000 (0x0028 - 0x0028)
class UNavigationPathGenerator : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationPathGenerator");
		return ptr;
	}

};


// Class NavigationSystem.NavigationQueryFilter
// 0x0020 (0x0048 - 0x0028)
class UNavigationQueryFilter : public UObject
{
public:
	TArray<struct FNavigationFilterArea>               Areas;                                                    // 0x0028(0x0010) (Edit, ZeroConstructor)
	struct FNavigationFilterFlags                      IncludeFlags;                                             // 0x0038(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FNavigationFilterFlags                      ExcludeFlags;                                             // 0x003C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0040(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationQueryFilter");
		return ptr;
	}

};


// Class NavigationSystem.NavigationSystemV1
// 0x03E8 (0x0410 - 0x0028)
class UNavigationSystemV1 : public UNavigationSystemBase
{
public:
	class ANavigationData*                             MainNavData;                                              // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData)
	class ANavigationData*                             AbstractNavData;                                          // 0x0030(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UClass*                                      CrowdManagerClass;                                        // 0x0038(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      bAutoCreateNavigationData : 1;                            // 0x0040(0x0001) (Edit, Config)
	unsigned char                                      bSpawnNavDataInNavBoundsLevel : 1;                        // 0x0040(0x0001) (Edit, Config)
	unsigned char                                      bAllowClientSideNavigation : 1;                           // 0x0040(0x0001) (Edit, Config)
	unsigned char                                      bShouldDiscardSubLevelNavData : 1;                        // 0x0040(0x0001) (Edit, Config)
	unsigned char                                      bTickWhilePaused : 1;                                     // 0x0040(0x0001) (Edit, Config)
	unsigned char                                      bSupportRebuilding : 1;                                   // 0x0040(0x0001)
	unsigned char                                      bInitialBuildingLocked : 1;                               // 0x0040(0x0001) (Edit, Config)
	unsigned char                                      UnknownData00 : 1;                                        // 0x0040(0x0001)
	unsigned char                                      bSkipAgentHeightCheckWhenPickingNavData : 1;              // 0x0041(0x0001) (Edit, Config)
	unsigned char                                      UnknownData01[0x2];                                       // 0x0042(0x0002) MISSED OFFSET
	ENavDataGatheringModeConfig                        DataGatheringMode;                                        // 0x0044(0x0001) (Edit, ZeroConstructor, Config, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0045(0x0003) MISSED OFFSET
	unsigned char                                      bGenerateNavigationOnlyAroundNavigationInvokers : 1;      // 0x0048(0x0001) (Edit, Config, DisableEditOnInstance)
	unsigned char                                      UnknownData03[0x3];                                       // 0x0049(0x0003) MISSED OFFSET
	float                                              ActiveTilesUpdateInterval;                                // 0x004C(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	TArray<struct FNavDataConfig>                      SupportedAgents;                                          // 0x0050(0x0010) (Edit, ZeroConstructor, Config)
	float                                              DirtyAreasUpdateFreq;                                     // 0x0060(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData04[0x4];                                       // 0x0064(0x0004) MISSED OFFSET
	TArray<class ANavigationData*>                     NavDataSet;                                               // 0x0068(0x0010) (ZeroConstructor)
	TArray<class ANavigationData*>                     NavDataRegistrationQueue;                                 // 0x0078(0x0010) (ZeroConstructor, Transient)
	unsigned char                                      UnknownData05[0x60];                                      // 0x0088(0x0060) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnNavDataRegisteredEvent;                                 // 0x00E8(0x0010) (ZeroConstructor, Transient, InstancedReference)
	struct FScriptMulticastDelegate                    OnNavigationGenerationFinishedDelegate;                   // 0x00F8(0x0010) (ZeroConstructor, Transient, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData06[0xCC];                                      // 0x0108(0x00CC) MISSED OFFSET
	EFNavigationSystemRunMode                          OperationMode;                                            // 0x01D4(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData07[0x23B];                                     // 0x01D5(0x023B) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationSystemV1");
		return ptr;
	}


	void UnregisterNavigationInvoker(class AActor* Invoker);
	void SimpleMoveToLocation(class AController* Controller, const struct FVector& Goal);
	void SimpleMoveToActor(class AController* Controller, class AActor* Goal);
	void SetMaxSimultaneousTileGenerationJobsCount(int MaxNumberOfJobs);
	void SetGeometryGatheringMode(ENavDataGatheringModeConfig NewMode);
	void ResetMaxSimultaneousTileGenerationJobsCount();
	void RegisterNavigationInvoker(class AActor* Invoker, float TileGenerationRadius, float TileRemovalRadius);
	struct FVector ProjectPointToNavigation(class UObject* WorldContextObject, const struct FVector& Point, class ANavigationData* NavData, class UClass* FilterClass, const struct FVector& QueryExtent);
	void OnNavigationBoundsUpdated(class ANavMeshBoundsVolume* NavVolume);
	bool NavigationRaycast(class UObject* WorldContextObject, const struct FVector& RayStart, const struct FVector& RayEnd, class UClass* FilterClass, class AController* querier, struct FVector* HitLocation);
	bool K2_ProjectPointToNavigation(class UObject* WorldContextObject, const struct FVector& Point, class ANavigationData* NavData, class UClass* FilterClass, const struct FVector& QueryExtent, struct FVector* ProjectedLocation);
	bool K2_GetRandomReachablePointInRadius(class UObject* WorldContextObject, const struct FVector& Origin, float Radius, class ANavigationData* NavData, class UClass* FilterClass, struct FVector* RandomLocation);
	bool K2_GetRandomPointInNavigableRadius(class UObject* WorldContextObject, const struct FVector& Origin, float Radius, class ANavigationData* NavData, class UClass* FilterClass, struct FVector* RandomLocation);
	bool IsNavigationBeingBuiltOrLocked(class UObject* WorldContextObject);
	bool IsNavigationBeingBuilt(class UObject* WorldContextObject);
	struct FVector GetRandomReachablePointInRadius(class UObject* WorldContextObject, const struct FVector& Origin, float Radius, class ANavigationData* NavData, class UClass* FilterClass);
	struct FVector GetRandomPointInNavigableRadius(class UObject* WorldContextObject, const struct FVector& Origin, float Radius, class ANavigationData* NavData, class UClass* FilterClass);
	TEnumAsByte<ENavigationQueryResult> GetPathLength(class UObject* WorldContextObject, const struct FVector& PathStart, const struct FVector& PathEnd, class ANavigationData* NavData, class UClass* FilterClass, float* PathLength);
	TEnumAsByte<ENavigationQueryResult> GetPathCost(class UObject* WorldContextObject, const struct FVector& PathStart, const struct FVector& PathEnd, class ANavigationData* NavData, class UClass* FilterClass, float* PathCost);
	class UNavigationSystemV1* GetNavigationSystem(class UObject* WorldContextObject);
	class UNavigationPath* FindPathToLocationSynchronously(class UObject* WorldContextObject, const struct FVector& PathStart, const struct FVector& PathEnd, class AActor* PathfindingContext, class UClass* FilterClass);
	class UNavigationPath* FindPathToActorSynchronously(class UObject* WorldContextObject, const struct FVector& PathStart, class AActor* GoalActor, float TetherDistance, class AActor* PathfindingContext, class UClass* FilterClass);
};


// Class NavigationSystem.NavigationSystemModuleConfig
// 0x0008 (0x0050 - 0x0048)
class UNavigationSystemModuleConfig : public UNavigationSystemConfig
{
public:
	unsigned char                                      bStrictlyStatic : 1;                                      // 0x0048(0x0001) (Edit)
	unsigned char                                      bCreateOnClient : 1;                                      // 0x0048(0x0001) (Edit)
	unsigned char                                      bAutoSpawnMissingNavData : 1;                             // 0x0048(0x0001) (Edit)
	unsigned char                                      bSpawnNavDataInNavBoundsLevel : 1;                        // 0x0048(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0049(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationSystemModuleConfig");
		return ptr;
	}

};


// Class NavigationSystem.NavigationTestingActor
// 0x00E8 (0x0410 - 0x0328)
class ANavigationTestingActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0328(0x0010) MISSED OFFSET
	class UCapsuleComponent*                           CapsuleComponent;                                         // 0x0338(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UNavigationInvokerComponent*                 InvokerComponent;                                         // 0x0340(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      bActAsNavigationInvoker : 1;                              // 0x0348(0x0001) (Edit)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0349(0x0007) MISSED OFFSET
	struct FNavAgentProperties                         NavAgentProps;                                            // 0x0350(0x0030) (Edit)
	struct FVector                                     QueryingExtent;                                           // 0x0380(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x038C(0x0004) MISSED OFFSET
	class ANavigationData*                             MyNavData;                                                // 0x0390(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	struct FVector                                     ProjectedLocation;                                        // 0x0398(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData)
	unsigned char                                      bProjectedLocationValid : 1;                              // 0x03A4(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, EditConst)
	unsigned char                                      bSearchStart : 1;                                         // 0x03A4(0x0001) (Edit)
	unsigned char                                      bUseHierarchicalPathfinding : 1;                          // 0x03A4(0x0001) (Edit)
	unsigned char                                      bGatherDetailedInfo : 1;                                  // 0x03A4(0x0001) (Edit)
	unsigned char                                      bDrawDistanceToWall : 1;                                  // 0x03A4(0x0001) (Edit)
	unsigned char                                      bShowNodePool : 1;                                        // 0x03A4(0x0001) (Edit)
	unsigned char                                      bShowBestPath : 1;                                        // 0x03A4(0x0001) (Edit)
	unsigned char                                      bShowDiffWithPreviousStep : 1;                            // 0x03A4(0x0001) (Edit)
	unsigned char                                      bShouldBeVisibleInGame : 1;                               // 0x03A5(0x0001) (Edit)
	unsigned char                                      UnknownData03[0x2];                                       // 0x03A6(0x0002) MISSED OFFSET
	TEnumAsByte<ENavCostDisplay>                       CostDisplayMode;                                          // 0x03A8(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x3];                                       // 0x03A9(0x0003) MISSED OFFSET
	struct FVector2D                                   TextCanvasOffset;                                         // 0x03AC(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bPathExist : 1;                                           // 0x03B4(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, Transient, EditConst)
	unsigned char                                      bPathIsPartial : 1;                                       // 0x03B4(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, Transient, EditConst)
	unsigned char                                      bPathSearchOutOfNodes : 1;                                // 0x03B4(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, Transient, EditConst)
	unsigned char                                      UnknownData05[0x3];                                       // 0x03B5(0x0003) MISSED OFFSET
	float                                              PathfindingTime;                                          // 0x03B8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, EditConst, IsPlainOldData)
	float                                              PathCost;                                                 // 0x03BC(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, EditConst, IsPlainOldData)
	int                                                PathfindingSteps;                                         // 0x03C0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, EditConst, IsPlainOldData)
	unsigned char                                      UnknownData06[0x4];                                       // 0x03C4(0x0004) MISSED OFFSET
	class ANavigationTestingActor*                     OtherActor;                                               // 0x03C8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // 0x03D0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                ShowStepIndex;                                            // 0x03D8(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, Transient, IsPlainOldData)
	float                                              OffsetFromCornersDistance;                                // 0x03DC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData07[0x30];                                      // 0x03E0(0x0030) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavigationTestingActor");
		return ptr;
	}

};


// Class NavigationSystem.NavLinkComponent
// 0x0010 (0x0570 - 0x0560)
class UNavLinkComponent : public UPrimitiveComponent
{
public:
	TArray<struct FNavigationLink>                     Links;                                                    // 0x0560(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavLinkComponent");
		return ptr;
	}

};


// Class NavigationSystem.NavRelevantComponent
// 0x0030 (0x0120 - 0x00F0)
class UNavRelevantComponent : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x24];                                      // 0x00F0(0x0024) MISSED OFFSET
	unsigned char                                      bAttachToOwnersRoot : 1;                                  // 0x0114(0x0001)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0115(0x0003) MISSED OFFSET
	class UObject*                                     CachedNavParent;                                          // 0x0118(0x0008) (ZeroConstructor, Transient, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavRelevantComponent");
		return ptr;
	}


	void SetNavigationRelevancy(bool bRelevant);
};


// Class NavigationSystem.NavLinkCustomComponent
// 0x00A8 (0x01C8 - 0x0120)
class UNavLinkCustomComponent : public UNavRelevantComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0120(0x0008) MISSED OFFSET
	uint32_t                                           NavLinkUserId;                                            // 0x0128(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x012C(0x0004) MISSED OFFSET
	class UClass*                                      EnabledAreaClass;                                         // 0x0130(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      DisabledAreaClass;                                        // 0x0138(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     LinkRelativeStart;                                        // 0x0140(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     LinkRelativeEnd;                                          // 0x014C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ENavLinkDirection>                     LinkDirection;                                            // 0x0158(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0159(0x0003) MISSED OFFSET
	unsigned char                                      bLinkEnabled : 1;                                         // 0x015C(0x0001) (Edit)
	unsigned char                                      bNotifyWhenEnabled : 1;                                   // 0x015C(0x0001) (Edit)
	unsigned char                                      bNotifyWhenDisabled : 1;                                  // 0x015C(0x0001) (Edit)
	unsigned char                                      bCreateBoxObstacle : 1;                                   // 0x015C(0x0001) (Edit)
	unsigned char                                      UnknownData03[0x3];                                       // 0x015D(0x0003) MISSED OFFSET
	struct FVector                                     ObstacleOffset;                                           // 0x0160(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ObstacleExtent;                                           // 0x016C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ObstacleAreaClass;                                        // 0x0178(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              BroadcastRadius;                                          // 0x0180(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              BroadcastInterval;                                        // 0x0184(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ECollisionChannel>                     BroadcastChannel;                                         // 0x0188(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x3F];                                      // 0x0189(0x003F) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavLinkCustomComponent");
		return ptr;
	}

};


// Class NavigationSystem.NavLinkCustomInterface
// 0x0000 (0x0028 - 0x0028)
class UNavLinkCustomInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavLinkCustomInterface");
		return ptr;
	}

};


// Class NavigationSystem.NavLinkHostInterface
// 0x0000 (0x0028 - 0x0028)
class UNavLinkHostInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavLinkHostInterface");
		return ptr;
	}

};


// Class NavigationSystem.NavLinkRenderingComponent
// 0x0000 (0x0560 - 0x0560)
class UNavLinkRenderingComponent : public UPrimitiveComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavLinkRenderingComponent");
		return ptr;
	}

};


// Class NavigationSystem.NavLinkTrivial
// 0x0000 (0x0050 - 0x0050)
class UNavLinkTrivial : public UNavLinkDefinition
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavLinkTrivial");
		return ptr;
	}

};


// Class NavigationSystem.NavMeshBoundsVolume
// 0x0008 (0x0368 - 0x0360)
class ANavMeshBoundsVolume : public AVolume
{
public:
	struct FNavAgentSelector                           SupportedAgents;                                          // 0x0360(0x0004) (Edit)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0364(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavMeshBoundsVolume");
		return ptr;
	}

};


// Class NavigationSystem.NavMeshRenderingComponent
// 0x0010 (0x0570 - 0x0560)
class UNavMeshRenderingComponent : public UPrimitiveComponent
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0560(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavMeshRenderingComponent");
		return ptr;
	}

};


// Class NavigationSystem.NavModifierComponent
// 0x0028 (0x0148 - 0x0120)
class UNavModifierComponent : public UNavRelevantComponent
{
public:
	class UClass*                                      AreaClass;                                                // 0x0120(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FVector                                     FailsafeExtent;                                           // 0x0128(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bIncludeAgentHeight : 1;                                  // 0x0134(0x0001) (Edit, Config)
	unsigned char                                      UnknownData00[0x13];                                      // 0x0135(0x0013) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavModifierComponent");
		return ptr;
	}


	void SetAreaClass(class UClass* NewAreaClass);
};


// Class NavigationSystem.NavModifierVolume
// 0x0010 (0x0370 - 0x0360)
class ANavModifierVolume : public AVolume
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0360(0x0008) MISSED OFFSET
	class UClass*                                      AreaClass;                                                // 0x0368(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavModifierVolume");
		return ptr;
	}


	void SetAreaClass(class UClass* NewAreaClass);
};


// Class NavigationSystem.NavNodeInterface
// 0x0000 (0x0028 - 0x0028)
class UNavNodeInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavNodeInterface");
		return ptr;
	}

};


// Class NavigationSystem.NavSystemConfigOverride
// 0x0010 (0x0338 - 0x0328)
class ANavSystemConfigOverride : public AActor
{
public:
	class UNavigationSystemConfig*                     NavigationSystemConfig;                                   // 0x0328(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      bLoadOnClient : 1;                                        // 0x0330(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0331(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavSystemConfigOverride");
		return ptr;
	}

};


// Class NavigationSystem.NavTestRenderingComponent
// 0x0000 (0x0560 - 0x0560)
class UNavTestRenderingComponent : public UPrimitiveComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.NavTestRenderingComponent");
		return ptr;
	}

};


// Class NavigationSystem.RecastFilter_UseDefaultArea
// 0x0000 (0x0048 - 0x0048)
class URecastFilter_UseDefaultArea : public UNavigationQueryFilter
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.RecastFilter_UseDefaultArea");
		return ptr;
	}

};


// Class NavigationSystem.RecastNavMesh
// 0x00B8 (0x05A0 - 0x04E8)
class ARecastNavMesh : public ANavigationData
{
public:
	unsigned char                                      bDrawTriangleEdges : 1;                                   // 0x04E8(0x0001) (Edit)
	unsigned char                                      bDrawPolyEdges : 1;                                       // 0x04E8(0x0001) (Edit, Config)
	unsigned char                                      bDrawFilledPolys : 1;                                     // 0x04E8(0x0001) (Edit)
	unsigned char                                      bDrawNavMeshEdges : 1;                                    // 0x04E8(0x0001) (Edit)
	unsigned char                                      bDrawTileBounds : 1;                                      // 0x04E8(0x0001) (Edit)
	unsigned char                                      bDrawPathCollidingGeometry : 1;                           // 0x04E8(0x0001) (Edit)
	unsigned char                                      bDrawTileLabels : 1;                                      // 0x04E8(0x0001) (Edit)
	unsigned char                                      bDrawPolygonLabels : 1;                                   // 0x04E8(0x0001) (Edit)
	unsigned char                                      bDrawDefaultPolygonCost : 1;                              // 0x04E9(0x0001) (Edit)
	unsigned char                                      bDrawLabelsOnPathNodes : 1;                               // 0x04E9(0x0001) (Edit)
	unsigned char                                      bDrawNavLinks : 1;                                        // 0x04E9(0x0001) (Edit)
	unsigned char                                      bDrawFailedNavLinks : 1;                                  // 0x04E9(0x0001) (Edit)
	unsigned char                                      bDrawClusters : 1;                                        // 0x04E9(0x0001) (Edit)
	unsigned char                                      bDrawOctree : 1;                                          // 0x04E9(0x0001) (Edit)
	unsigned char                                      bDrawOctreeDetails : 1;                                   // 0x04E9(0x0001) (Edit)
	unsigned char                                      bDistinctlyDrawTilesBeingBuilt : 1;                       // 0x04E9(0x0001) (Config)
	unsigned char                                      bDrawNavMesh : 1;                                         // 0x04EA(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x1];                                       // 0x04EB(0x0001) MISSED OFFSET
	float                                              DrawOffset;                                               // 0x04EC(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      bFixedTilePoolSize : 1;                                   // 0x04F0(0x0001) (Edit, Config)
	unsigned char                                      UnknownData01[0x3];                                       // 0x04F1(0x0003) MISSED OFFSET
	int                                                TilePoolSize;                                             // 0x04F4(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              TileSizeUU;                                               // 0x04F8(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              CellSize;                                                 // 0x04FC(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              CellHeight;                                               // 0x0500(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              AgentRadius;                                              // 0x0504(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              AgentHeight;                                              // 0x0508(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              AgentMaxHeight;                                           // 0x050C(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              AgentMaxSlope;                                            // 0x0510(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              AgentMaxStepHeight;                                       // 0x0514(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              MinRegionArea;                                            // 0x0518(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              MergeRegionSize;                                          // 0x051C(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              MaxSimplificationError;                                   // 0x0520(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	int                                                MaxSimultaneousTileGenerationJobsCount;                   // 0x0524(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	int                                                TileNumberHardLimit;                                      // 0x0528(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	int                                                PolyRefTileBits;                                          // 0x052C(0x0004) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	int                                                PolyRefNavPolyBits;                                       // 0x0530(0x0004) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	int                                                PolyRefSaltBits;                                          // 0x0534(0x0004) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	struct FVector                                     NavMeshOriginOffset;                                      // 0x0538(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              DefaultDrawDistance;                                      // 0x0544(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float                                              DefaultMaxSearchNodes;                                    // 0x0548(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float                                              DefaultMaxHierarchicalSearchNodes;                        // 0x054C(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	TEnumAsByte<ERecastPartitioning>                   RegionPartitioning;                                       // 0x0550(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	TEnumAsByte<ERecastPartitioning>                   LayerPartitioning;                                        // 0x0551(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData02[0x2];                                       // 0x0552(0x0002) MISSED OFFSET
	int                                                RegionChunkSplits;                                        // 0x0554(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	int                                                LayerChunkSplits;                                         // 0x0558(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      bSortNavigationAreasByCost : 1;                           // 0x055C(0x0001) (Edit, Config)
	unsigned char                                      bPerformVoxelFiltering : 1;                               // 0x055C(0x0001) (Edit, Config)
	unsigned char                                      bMarkLowHeightAreas : 1;                                  // 0x055C(0x0001) (Edit, Config)
	unsigned char                                      bFilterLowSpanSequences : 1;                              // 0x055C(0x0001) (Edit, Config)
	unsigned char                                      bFilterLowSpanFromTileCache : 1;                          // 0x055C(0x0001) (Edit, Config)
	unsigned char                                      bDoFullyAsyncNavDataGathering : 1;                        // 0x055C(0x0001) (Edit, Config)
	unsigned char                                      bUseBetterOffsetsFromCorners : 1;                         // 0x055C(0x0001) (Config)
	unsigned char                                      bStoreEmptyTileLayers : 1;                                // 0x055C(0x0001) (Config)
	unsigned char                                      bUseVirtualFilters : 1;                                   // 0x055D(0x0001) (Config)
	unsigned char                                      bAllowNavLinkAsPathEnd : 1;                               // 0x055D(0x0001) (Config)
	unsigned char                                      bUseVoxelCache : 1;                                       // 0x055D(0x0001) (Config)
	unsigned char                                      UnknownData03[0x2];                                       // 0x055E(0x0002) MISSED OFFSET
	float                                              TileSetUpdateInterval;                                    // 0x0560(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float                                              HeuristicScale;                                           // 0x0564(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              VerticalDeviationFromGroundCompensation;                  // 0x0568(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData04[0x34];                                      // 0x056C(0x0034) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.RecastNavMesh");
		return ptr;
	}

};


// Class NavigationSystem.RecastNavMeshDataChunk
// 0x0010 (0x0040 - 0x0030)
class URecastNavMeshDataChunk : public UNavigationDataChunk
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0030(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class NavigationSystem.RecastNavMeshDataChunk");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
