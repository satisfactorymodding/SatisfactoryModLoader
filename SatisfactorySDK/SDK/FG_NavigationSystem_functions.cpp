// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_NavigationSystem_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function NavigationSystem.NavigationPath.IsValid
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationPath::IsValid()
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationPath.IsValid");

	UNavigationPath_IsValid_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationPath.IsStringPulled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationPath::IsStringPulled()
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationPath.IsStringPulled");

	UNavigationPath_IsStringPulled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationPath.IsPartial
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationPath::IsPartial()
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationPath.IsPartial");

	UNavigationPath_IsPartial_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationPath.GetPathLength
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UNavigationPath::GetPathLength()
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationPath.GetPathLength");

	UNavigationPath_GetPathLength_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationPath.GetPathCost
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UNavigationPath::GetPathCost()
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationPath.GetPathCost");

	UNavigationPath_GetPathCost_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationPath.GetDebugString
// ()
// Parameters:
// class FString                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

class FString UNavigationPath::GetDebugString()
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationPath.GetDebugString");

	UNavigationPath_GetDebugString_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationPath.EnableRecalculationOnInvalidation
// ()
// Parameters:
// TEnumAsByte<ENavigationOptionFlag> DoRecalculation                (Parm, ZeroConstructor, IsPlainOldData)

void UNavigationPath::EnableRecalculationOnInvalidation(TEnumAsByte<ENavigationOptionFlag> DoRecalculation)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationPath.EnableRecalculationOnInvalidation");

	UNavigationPath_EnableRecalculationOnInvalidation_Params params;
	params.DoRecalculation = DoRecalculation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationPath.EnableDebugDrawing
// ()
// Parameters:
// bool                           bShouldDrawDebugData           (Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            PathColor                      (Parm, ZeroConstructor, IsPlainOldData)

void UNavigationPath::EnableDebugDrawing(bool bShouldDrawDebugData, const struct FLinearColor& PathColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationPath.EnableDebugDrawing");

	UNavigationPath_EnableDebugDrawing_Params params;
	params.bShouldDrawDebugData = bShouldDrawDebugData;
	params.PathColor = PathColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.UnregisterNavigationInvoker
// ()
// Parameters:
// class AActor*                  Invoker                        (Parm, ZeroConstructor, IsPlainOldData)

void UNavigationSystemV1::UnregisterNavigationInvoker(class AActor* Invoker)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.UnregisterNavigationInvoker");

	UNavigationSystemV1_UnregisterNavigationInvoker_Params params;
	params.Invoker = Invoker;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.SimpleMoveToLocation
// ()
// Parameters:
// class AController*             Controller                     (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 Goal                           (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)

void UNavigationSystemV1::SimpleMoveToLocation(class AController* Controller, const struct FVector& Goal)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.SimpleMoveToLocation");

	UNavigationSystemV1_SimpleMoveToLocation_Params params;
	params.Controller = Controller;
	params.Goal = Goal;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.SimpleMoveToActor
// ()
// Parameters:
// class AController*             Controller                     (Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  Goal                           (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UNavigationSystemV1::SimpleMoveToActor(class AController* Controller, class AActor* Goal)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.SimpleMoveToActor");

	UNavigationSystemV1_SimpleMoveToActor_Params params;
	params.Controller = Controller;
	params.Goal = Goal;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.SetMaxSimultaneousTileGenerationJobsCount
// ()
// Parameters:
// int                            MaxNumberOfJobs                (Parm, ZeroConstructor, IsPlainOldData)

void UNavigationSystemV1::SetMaxSimultaneousTileGenerationJobsCount(int MaxNumberOfJobs)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.SetMaxSimultaneousTileGenerationJobsCount");

	UNavigationSystemV1_SetMaxSimultaneousTileGenerationJobsCount_Params params;
	params.MaxNumberOfJobs = MaxNumberOfJobs;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.SetGeometryGatheringMode
// ()
// Parameters:
// ENavDataGatheringModeConfig    NewMode                        (Parm, ZeroConstructor, IsPlainOldData)

void UNavigationSystemV1::SetGeometryGatheringMode(ENavDataGatheringModeConfig NewMode)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.SetGeometryGatheringMode");

	UNavigationSystemV1_SetGeometryGatheringMode_Params params;
	params.NewMode = NewMode;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.ResetMaxSimultaneousTileGenerationJobsCount
// ()

void UNavigationSystemV1::ResetMaxSimultaneousTileGenerationJobsCount()
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.ResetMaxSimultaneousTileGenerationJobsCount");

	UNavigationSystemV1_ResetMaxSimultaneousTileGenerationJobsCount_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.RegisterNavigationInvoker
// ()
// Parameters:
// class AActor*                  Invoker                        (Parm, ZeroConstructor, IsPlainOldData)
// float                          TileGenerationRadius           (Parm, ZeroConstructor, IsPlainOldData)
// float                          TileRemovalRadius              (Parm, ZeroConstructor, IsPlainOldData)

void UNavigationSystemV1::RegisterNavigationInvoker(class AActor* Invoker, float TileGenerationRadius, float TileRemovalRadius)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.RegisterNavigationInvoker");

	UNavigationSystemV1_RegisterNavigationInvoker_Params params;
	params.Invoker = Invoker;
	params.TileGenerationRadius = TileGenerationRadius;
	params.TileRemovalRadius = TileRemovalRadius;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.ProjectPointToNavigation
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 Point                          (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// class ANavigationData*         NavData                        (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 QueryExtent                    (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector UNavigationSystemV1::ProjectPointToNavigation(class UObject* WorldContextObject, const struct FVector& Point, class ANavigationData* NavData, class UClass* FilterClass, const struct FVector& QueryExtent)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.ProjectPointToNavigation");

	UNavigationSystemV1_ProjectPointToNavigation_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Point = Point;
	params.NavData = NavData;
	params.FilterClass = FilterClass;
	params.QueryExtent = QueryExtent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.OnNavigationBoundsUpdated
// ()
// Parameters:
// class ANavMeshBoundsVolume*    NavVolume                      (Parm, ZeroConstructor, IsPlainOldData)

void UNavigationSystemV1::OnNavigationBoundsUpdated(class ANavMeshBoundsVolume* NavVolume)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.OnNavigationBoundsUpdated");

	UNavigationSystemV1_OnNavigationBoundsUpdated_Params params;
	params.NavVolume = NavVolume;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavigationSystemV1.NavigationRaycast
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 RayStart                       (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 RayEnd                         (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 HitLocation                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// class AController*             querier                        (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationSystemV1::NavigationRaycast(class UObject* WorldContextObject, const struct FVector& RayStart, const struct FVector& RayEnd, class UClass* FilterClass, class AController* querier, struct FVector* HitLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.NavigationRaycast");

	UNavigationSystemV1_NavigationRaycast_Params params;
	params.WorldContextObject = WorldContextObject;
	params.RayStart = RayStart;
	params.RayEnd = RayEnd;
	params.FilterClass = FilterClass;
	params.querier = querier;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (HitLocation != nullptr)
		*HitLocation = params.HitLocation;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.K2_ProjectPointToNavigation
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 Point                          (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 ProjectedLocation              (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// class ANavigationData*         NavData                        (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 QueryExtent                    (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationSystemV1::K2_ProjectPointToNavigation(class UObject* WorldContextObject, const struct FVector& Point, class ANavigationData* NavData, class UClass* FilterClass, const struct FVector& QueryExtent, struct FVector* ProjectedLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.K2_ProjectPointToNavigation");

	UNavigationSystemV1_K2_ProjectPointToNavigation_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Point = Point;
	params.NavData = NavData;
	params.FilterClass = FilterClass;
	params.QueryExtent = QueryExtent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ProjectedLocation != nullptr)
		*ProjectedLocation = params.ProjectedLocation;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.K2_GetRandomReachablePointInRadius
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 Origin                         (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 RandomLocation                 (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// float                          Radius                         (Parm, ZeroConstructor, IsPlainOldData)
// class ANavigationData*         NavData                        (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationSystemV1::K2_GetRandomReachablePointInRadius(class UObject* WorldContextObject, const struct FVector& Origin, float Radius, class ANavigationData* NavData, class UClass* FilterClass, struct FVector* RandomLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.K2_GetRandomReachablePointInRadius");

	UNavigationSystemV1_K2_GetRandomReachablePointInRadius_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Origin = Origin;
	params.Radius = Radius;
	params.NavData = NavData;
	params.FilterClass = FilterClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (RandomLocation != nullptr)
		*RandomLocation = params.RandomLocation;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.K2_GetRandomPointInNavigableRadius
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 Origin                         (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 RandomLocation                 (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// float                          Radius                         (Parm, ZeroConstructor, IsPlainOldData)
// class ANavigationData*         NavData                        (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationSystemV1::K2_GetRandomPointInNavigableRadius(class UObject* WorldContextObject, const struct FVector& Origin, float Radius, class ANavigationData* NavData, class UClass* FilterClass, struct FVector* RandomLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.K2_GetRandomPointInNavigableRadius");

	UNavigationSystemV1_K2_GetRandomPointInNavigableRadius_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Origin = Origin;
	params.Radius = Radius;
	params.NavData = NavData;
	params.FilterClass = FilterClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (RandomLocation != nullptr)
		*RandomLocation = params.RandomLocation;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.IsNavigationBeingBuiltOrLocked
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationSystemV1::IsNavigationBeingBuiltOrLocked(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.IsNavigationBeingBuiltOrLocked");

	UNavigationSystemV1_IsNavigationBeingBuiltOrLocked_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.IsNavigationBeingBuilt
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNavigationSystemV1::IsNavigationBeingBuilt(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.IsNavigationBeingBuilt");

	UNavigationSystemV1_IsNavigationBeingBuilt_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.GetRandomReachablePointInRadius
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 Origin                         (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// float                          Radius                         (Parm, ZeroConstructor, IsPlainOldData)
// class ANavigationData*         NavData                        (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector UNavigationSystemV1::GetRandomReachablePointInRadius(class UObject* WorldContextObject, const struct FVector& Origin, float Radius, class ANavigationData* NavData, class UClass* FilterClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.GetRandomReachablePointInRadius");

	UNavigationSystemV1_GetRandomReachablePointInRadius_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Origin = Origin;
	params.Radius = Radius;
	params.NavData = NavData;
	params.FilterClass = FilterClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.GetRandomPointInNavigableRadius
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 Origin                         (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// float                          Radius                         (Parm, ZeroConstructor, IsPlainOldData)
// class ANavigationData*         NavData                        (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector UNavigationSystemV1::GetRandomPointInNavigableRadius(class UObject* WorldContextObject, const struct FVector& Origin, float Radius, class ANavigationData* NavData, class UClass* FilterClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.GetRandomPointInNavigableRadius");

	UNavigationSystemV1_GetRandomPointInNavigableRadius_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Origin = Origin;
	params.Radius = Radius;
	params.NavData = NavData;
	params.FilterClass = FilterClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.GetPathLength
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 PathStart                      (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 PathEnd                        (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// float                          PathLength                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// class ANavigationData*         NavData                        (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ENavigationQueryResult> ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

TEnumAsByte<ENavigationQueryResult> UNavigationSystemV1::GetPathLength(class UObject* WorldContextObject, const struct FVector& PathStart, const struct FVector& PathEnd, class ANavigationData* NavData, class UClass* FilterClass, float* PathLength)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.GetPathLength");

	UNavigationSystemV1_GetPathLength_Params params;
	params.WorldContextObject = WorldContextObject;
	params.PathStart = PathStart;
	params.PathEnd = PathEnd;
	params.NavData = NavData;
	params.FilterClass = FilterClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (PathLength != nullptr)
		*PathLength = params.PathLength;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.GetPathCost
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 PathStart                      (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 PathEnd                        (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// float                          PathCost                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// class ANavigationData*         NavData                        (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ENavigationQueryResult> ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

TEnumAsByte<ENavigationQueryResult> UNavigationSystemV1::GetPathCost(class UObject* WorldContextObject, const struct FVector& PathStart, const struct FVector& PathEnd, class ANavigationData* NavData, class UClass* FilterClass, float* PathCost)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.GetPathCost");

	UNavigationSystemV1_GetPathCost_Params params;
	params.WorldContextObject = WorldContextObject;
	params.PathStart = PathStart;
	params.PathEnd = PathEnd;
	params.NavData = NavData;
	params.FilterClass = FilterClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (PathCost != nullptr)
		*PathCost = params.PathCost;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.GetNavigationSystem
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// class UNavigationSystemV1*     ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UNavigationSystemV1* UNavigationSystemV1::GetNavigationSystem(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.GetNavigationSystem");

	UNavigationSystemV1_GetNavigationSystem_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.FindPathToLocationSynchronously
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 PathStart                      (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 PathEnd                        (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// class AActor*                  PathfindingContext             (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// class UNavigationPath*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UNavigationPath* UNavigationSystemV1::FindPathToLocationSynchronously(class UObject* WorldContextObject, const struct FVector& PathStart, const struct FVector& PathEnd, class AActor* PathfindingContext, class UClass* FilterClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.FindPathToLocationSynchronously");

	UNavigationSystemV1_FindPathToLocationSynchronously_Params params;
	params.WorldContextObject = WorldContextObject;
	params.PathStart = PathStart;
	params.PathEnd = PathEnd;
	params.PathfindingContext = PathfindingContext;
	params.FilterClass = FilterClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavigationSystemV1.FindPathToActorSynchronously
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 PathStart                      (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// class AActor*                  GoalActor                      (Parm, ZeroConstructor, IsPlainOldData)
// float                          TetherDistance                 (Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  PathfindingContext             (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  FilterClass                    (Parm, ZeroConstructor, IsPlainOldData)
// class UNavigationPath*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UNavigationPath* UNavigationSystemV1::FindPathToActorSynchronously(class UObject* WorldContextObject, const struct FVector& PathStart, class AActor* GoalActor, float TetherDistance, class AActor* PathfindingContext, class UClass* FilterClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavigationSystemV1.FindPathToActorSynchronously");

	UNavigationSystemV1_FindPathToActorSynchronously_Params params;
	params.WorldContextObject = WorldContextObject;
	params.PathStart = PathStart;
	params.GoalActor = GoalActor;
	params.TetherDistance = TetherDistance;
	params.PathfindingContext = PathfindingContext;
	params.FilterClass = FilterClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function NavigationSystem.NavRelevantComponent.SetNavigationRelevancy
// ()
// Parameters:
// bool                           bRelevant                      (Parm, ZeroConstructor, IsPlainOldData)

void UNavRelevantComponent::SetNavigationRelevancy(bool bRelevant)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavRelevantComponent.SetNavigationRelevancy");

	UNavRelevantComponent_SetNavigationRelevancy_Params params;
	params.bRelevant = bRelevant;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavModifierComponent.SetAreaClass
// ()
// Parameters:
// class UClass*                  NewAreaClass                   (Parm, ZeroConstructor, IsPlainOldData)

void UNavModifierComponent::SetAreaClass(class UClass* NewAreaClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavModifierComponent.SetAreaClass");

	UNavModifierComponent_SetAreaClass_Params params;
	params.NewAreaClass = NewAreaClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function NavigationSystem.NavModifierVolume.SetAreaClass
// ()
// Parameters:
// class UClass*                  NewAreaClass                   (Parm, ZeroConstructor, IsPlainOldData)

void ANavModifierVolume::SetAreaClass(class UClass* NewAreaClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function NavigationSystem.NavModifierVolume.SetAreaClass");

	ANavModifierVolume_SetAreaClass_Params params;
	params.NewAreaClass = NewAreaClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
