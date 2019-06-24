#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_NavigationSystem_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function NavigationSystem.NavigationPath.IsValid
struct UNavigationPath_IsValid_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationPath.IsStringPulled
struct UNavigationPath_IsStringPulled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationPath.IsPartial
struct UNavigationPath_IsPartial_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationPath.GetPathLength
struct UNavigationPath_GetPathLength_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationPath.GetPathCost
struct UNavigationPath_GetPathCost_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationPath.GetDebugString
struct UNavigationPath_GetDebugString_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function NavigationSystem.NavigationPath.EnableRecalculationOnInvalidation
struct UNavigationPath_EnableRecalculationOnInvalidation_Params
{
	TEnumAsByte<ENavigationOptionFlag>                 DoRecalculation;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavigationPath.EnableDebugDrawing
struct UNavigationPath_EnableDebugDrawing_Params
{
	bool                                               bShouldDrawDebugData;                                     // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                PathColor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.UnregisterNavigationInvoker
struct UNavigationSystemV1_UnregisterNavigationInvoker_Params
{
	class AActor*                                      Invoker;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.SimpleMoveToLocation
struct UNavigationSystemV1_SimpleMoveToLocation_Params
{
	class AController*                                 Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Goal;                                                     // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.SimpleMoveToActor
struct UNavigationSystemV1_SimpleMoveToActor_Params
{
	class AController*                                 Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Goal;                                                     // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.SetMaxSimultaneousTileGenerationJobsCount
struct UNavigationSystemV1_SetMaxSimultaneousTileGenerationJobsCount_Params
{
	int                                                MaxNumberOfJobs;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.SetGeometryGatheringMode
struct UNavigationSystemV1_SetGeometryGatheringMode_Params
{
	ENavDataGatheringModeConfig                        NewMode;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.ResetMaxSimultaneousTileGenerationJobsCount
struct UNavigationSystemV1_ResetMaxSimultaneousTileGenerationJobsCount_Params
{
};

// Function NavigationSystem.NavigationSystemV1.RegisterNavigationInvoker
struct UNavigationSystemV1_RegisterNavigationInvoker_Params
{
	class AActor*                                      Invoker;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              TileGenerationRadius;                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              TileRemovalRadius;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.ProjectPointToNavigation
struct UNavigationSystemV1_ProjectPointToNavigation_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Point;                                                    // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     QueryExtent;                                              // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.OnNavigationBoundsUpdated
struct UNavigationSystemV1_OnNavigationBoundsUpdated_Params
{
	class ANavMeshBoundsVolume*                        NavVolume;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.NavigationRaycast
struct UNavigationSystemV1_NavigationRaycast_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     RayStart;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     RayEnd;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 querier;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.K2_ProjectPointToNavigation
struct UNavigationSystemV1_K2_ProjectPointToNavigation_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Point;                                                    // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     ProjectedLocation;                                        // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     QueryExtent;                                              // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.K2_GetRandomReachablePointInRadius
struct UNavigationSystemV1_K2_GetRandomReachablePointInRadius_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Origin;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     RandomLocation;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	float                                              Radius;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.K2_GetRandomPointInNavigableRadius
struct UNavigationSystemV1_K2_GetRandomPointInNavigableRadius_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Origin;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     RandomLocation;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	float                                              Radius;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.IsNavigationBeingBuiltOrLocked
struct UNavigationSystemV1_IsNavigationBeingBuiltOrLocked_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.IsNavigationBeingBuilt
struct UNavigationSystemV1_IsNavigationBeingBuilt_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.GetRandomReachablePointInRadius
struct UNavigationSystemV1_GetRandomReachablePointInRadius_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Origin;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              Radius;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.GetRandomPointInNavigableRadius
struct UNavigationSystemV1_GetRandomPointInNavigableRadius_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Origin;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              Radius;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.GetPathLength
struct UNavigationSystemV1_GetPathLength_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     PathStart;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     PathEnd;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              PathLength;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ENavigationQueryResult>                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.GetPathCost
struct UNavigationSystemV1_GetPathCost_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     PathStart;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     PathEnd;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              PathCost;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ENavigationQueryResult>                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.GetNavigationSystem
struct UNavigationSystemV1_GetNavigationSystem_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UNavigationSystemV1*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.FindPathToLocationSynchronously
struct UNavigationSystemV1_FindPathToLocationSynchronously_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     PathStart;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     PathEnd;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class AActor*                                      PathfindingContext;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UNavigationPath*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavigationSystemV1.FindPathToActorSynchronously
struct UNavigationSystemV1_FindPathToActorSynchronously_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     PathStart;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class AActor*                                      GoalActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              TetherDistance;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      PathfindingContext;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UNavigationPath*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function NavigationSystem.NavRelevantComponent.SetNavigationRelevancy
struct UNavRelevantComponent_SetNavigationRelevancy_Params
{
	bool                                               bRelevant;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavModifierComponent.SetAreaClass
struct UNavModifierComponent_SetAreaClass_Params
{
	class UClass*                                      NewAreaClass;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function NavigationSystem.NavModifierVolume.SetAreaClass
struct ANavModifierVolume_SetAreaClass_Params
{
	class UClass*                                      NewAreaClass;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
