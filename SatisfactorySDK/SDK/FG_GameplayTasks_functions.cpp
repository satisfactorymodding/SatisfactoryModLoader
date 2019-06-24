// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_GameplayTasks_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function GameplayTasks.GameplayTask.ReadyForActivation
// ()

void UGameplayTask::ReadyForActivation()
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTask.ReadyForActivation");

	UGameplayTask_ReadyForActivation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction GameplayTasks.GameplayTask.GenericGameplayTaskDelegate__DelegateSignature
// ()

void UGameplayTask::GenericGameplayTaskDelegate__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction GameplayTasks.GameplayTask.GenericGameplayTaskDelegate__DelegateSignature");

	UGameplayTask_GenericGameplayTaskDelegate__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GameplayTasks.GameplayTask.EndTask
// ()

void UGameplayTask::EndTask()
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTask.EndTask");

	UGameplayTask_EndTask_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GameplayTasks.GameplayTask_ClaimResource.ClaimResources
// ()
// Parameters:
// TScriptInterface<class UGameplayTaskOwnerInterface> InTaskOwner                    (Parm, ZeroConstructor, IsPlainOldData)
// TArray<class UClass*>          ResourceClasses                (Parm, ZeroConstructor)
// unsigned char                  Priority                       (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   TaskInstanceName               (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// class UGameplayTask_ClaimResource* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UGameplayTask_ClaimResource* UGameplayTask_ClaimResource::ClaimResources(const TScriptInterface<class UGameplayTaskOwnerInterface>& InTaskOwner, TArray<class UClass*> ResourceClasses, unsigned char Priority, const struct FName& TaskInstanceName)
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTask_ClaimResource.ClaimResources");

	UGameplayTask_ClaimResource_ClaimResources_Params params;
	params.InTaskOwner = InTaskOwner;
	params.ResourceClasses = ResourceClasses;
	params.Priority = Priority;
	params.TaskInstanceName = TaskInstanceName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GameplayTasks.GameplayTask_ClaimResource.ClaimResource
// ()
// Parameters:
// TScriptInterface<class UGameplayTaskOwnerInterface> InTaskOwner                    (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  ResourceClass                  (Parm, ZeroConstructor, IsPlainOldData)
// unsigned char                  Priority                       (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   TaskInstanceName               (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// class UGameplayTask_ClaimResource* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UGameplayTask_ClaimResource* UGameplayTask_ClaimResource::ClaimResource(const TScriptInterface<class UGameplayTaskOwnerInterface>& InTaskOwner, class UClass* ResourceClass, unsigned char Priority, const struct FName& TaskInstanceName)
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTask_ClaimResource.ClaimResource");

	UGameplayTask_ClaimResource_ClaimResource_Params params;
	params.InTaskOwner = InTaskOwner;
	params.ResourceClass = ResourceClass;
	params.Priority = Priority;
	params.TaskInstanceName = TaskInstanceName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GameplayTasks.GameplayTask_SpawnActor.SpawnActor
// ()
// Parameters:
// TScriptInterface<class UGameplayTaskOwnerInterface> TaskOwner                      (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 SpawnLocation                  (Parm, ZeroConstructor, IsPlainOldData)
// struct FRotator                spawnRotation                  (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  Class                          (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bSpawnOnlyOnAuthority          (Parm, ZeroConstructor, IsPlainOldData)
// class UGameplayTask_SpawnActor* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UGameplayTask_SpawnActor* UGameplayTask_SpawnActor::SpawnActor(const TScriptInterface<class UGameplayTaskOwnerInterface>& TaskOwner, const struct FVector& SpawnLocation, const struct FRotator& spawnRotation, class UClass* Class, bool bSpawnOnlyOnAuthority)
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTask_SpawnActor.SpawnActor");

	UGameplayTask_SpawnActor_SpawnActor_Params params;
	params.TaskOwner = TaskOwner;
	params.SpawnLocation = SpawnLocation;
	params.spawnRotation = spawnRotation;
	params.Class = Class;
	params.bSpawnOnlyOnAuthority = bSpawnOnlyOnAuthority;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GameplayTasks.GameplayTask_SpawnActor.FinishSpawningActor
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  SpawnedActor                   (Parm, ZeroConstructor, IsPlainOldData)

void UGameplayTask_SpawnActor::FinishSpawningActor(class UObject* WorldContextObject, class AActor* SpawnedActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTask_SpawnActor.FinishSpawningActor");

	UGameplayTask_SpawnActor_FinishSpawningActor_Params params;
	params.WorldContextObject = WorldContextObject;
	params.SpawnedActor = SpawnedActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GameplayTasks.GameplayTask_SpawnActor.BeginSpawningActor
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  SpawnedActor                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UGameplayTask_SpawnActor::BeginSpawningActor(class UObject* WorldContextObject, class AActor** SpawnedActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTask_SpawnActor.BeginSpawningActor");

	UGameplayTask_SpawnActor_BeginSpawningActor_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (SpawnedActor != nullptr)
		*SpawnedActor = params.SpawnedActor;

	return params.ReturnValue;
}


// Function GameplayTasks.GameplayTask_WaitDelay.TaskWaitDelay
// ()
// Parameters:
// TScriptInterface<class UGameplayTaskOwnerInterface> TaskOwner                      (Parm, ZeroConstructor, IsPlainOldData)
// float                          Time                           (Parm, ZeroConstructor, IsPlainOldData)
// unsigned char                  Priority                       (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// class UGameplayTask_WaitDelay* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UGameplayTask_WaitDelay* UGameplayTask_WaitDelay::TaskWaitDelay(const TScriptInterface<class UGameplayTaskOwnerInterface>& TaskOwner, float Time, unsigned char Priority)
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTask_WaitDelay.TaskWaitDelay");

	UGameplayTask_WaitDelay_TaskWaitDelay_Params params;
	params.TaskOwner = TaskOwner;
	params.Time = Time;
	params.Priority = Priority;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction GameplayTasks.GameplayTask_WaitDelay.TaskDelayDelegate__DelegateSignature
// ()

void UGameplayTask_WaitDelay::TaskDelayDelegate__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction GameplayTasks.GameplayTask_WaitDelay.TaskDelayDelegate__DelegateSignature");

	UGameplayTask_WaitDelay_TaskDelayDelegate__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GameplayTasks.GameplayTasksComponent.OnRep_SimulatedTasks
// ()

void UGameplayTasksComponent::OnRep_SimulatedTasks()
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTasksComponent.OnRep_SimulatedTasks");

	UGameplayTasksComponent_OnRep_SimulatedTasks_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GameplayTasks.GameplayTasksComponent.K2_RunGameplayTask
// ()
// Parameters:
// TScriptInterface<class UGameplayTaskOwnerInterface> TaskOwner                      (Parm, ZeroConstructor, IsPlainOldData)
// class UGameplayTask*           Task                           (Parm, ZeroConstructor, IsPlainOldData)
// unsigned char                  Priority                       (Parm, ZeroConstructor, IsPlainOldData)
// TArray<class UClass*>          AdditionalRequiredResources    (Parm, ZeroConstructor)
// TArray<class UClass*>          AdditionalClaimedResources     (Parm, ZeroConstructor)
// EGameplayTaskRunResult         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

EGameplayTaskRunResult UGameplayTasksComponent::K2_RunGameplayTask(const TScriptInterface<class UGameplayTaskOwnerInterface>& TaskOwner, class UGameplayTask* Task, unsigned char Priority, TArray<class UClass*> AdditionalRequiredResources, TArray<class UClass*> AdditionalClaimedResources)
{
	static auto fn = UObject::FindObject<UFunction>("Function GameplayTasks.GameplayTasksComponent.K2_RunGameplayTask");

	UGameplayTasksComponent_K2_RunGameplayTask_Params params;
	params.TaskOwner = TaskOwner;
	params.Task = Task;
	params.Priority = Priority;
	params.AdditionalRequiredResources = AdditionalRequiredResources;
	params.AdditionalClaimedResources = AdditionalClaimedResources;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
